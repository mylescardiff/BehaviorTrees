#include "PathedBehavior.h"
#include <Logic/Components/AIComponent/AIComponent.h>



PathedBehavior::PathedBehavior(AIComponent* pOwner)
	:ActionNode(pOwner)
	, m_currentWaypointTarget(0)
	, m_lastPathedIndex(0)
	, m_arriveThreshold(kDefaultArriveThreshold)
	, m_pathInProgress(false)
{
	//
}

void PathedBehavior::SetRawPath(std::vector<size_t>& rawPath, bool loop)
{
	if (rawPath.empty())
		return;

	m_tempRawPath = rawPath;

	m_pathInProgress = true;
	m_lastPathedIndex = 0;
	m_waypoints.clear();
	m_currentWaypointTarget = 0;

	StepPathFind(loop);
}

Waypoint PathedBehavior::NextWaypoint()
{
	++m_currentWaypointTarget;
	if (m_currentWaypointTarget == m_waypoints.size())
		m_currentWaypointTarget = 0;

	return m_waypoints[m_currentWaypointTarget];
}


void PathedBehavior::StepPathFind(bool loop)
{
	slth::GridSystem* pGrid = m_pBlackboard->GetGrid();
	for (size_t i = m_lastPathedIndex; i < m_tempRawPath.size(); ++i)
	{
		if (!loop && i == m_tempRawPath.size() - 1)
		{
			// don't loop back to start if it's not setup that way
			m_pathInProgress = false;
			m_lastPathedIndex = 0;
			return;
		}

		size_t destPath = i + 1;
		if (i + 1 == m_tempRawPath.size())
		{
			// make sure we path back to the origin, becuase otherwise
			// agent will ignore level and b-line back to the start
			destPath = 0;
		}

		bool pathFinished = false;
		Id32 agentId = m_pOwner->GetOwner()->GetId();
		if (!pGrid->IsPathInProgress())
		{
			pathFinished = pGrid->FindPathAStar(m_tempRawPath[i], m_tempRawPath[destPath], m_tempProcessedPath, kPathTimeAllowed, agentId);
		}
		else if (pGrid->GetPathingAgentId() == agentId)
		{
			pathFinished = pGrid->Resume(m_tempProcessedPath, kPathTimeAllowed, agentId);
		}
		else
		{
			return;
		}
		if (pathFinished)
		{
			// check if there was a valid path found, if not, cut off this operation
			if (m_tempProcessedPath.empty())
			{
				m_pathInProgress = false;
				m_lastPathedIndex = 0;
				return;
			}

			// this leg of the path completed, add it to the waypoints and move on
			for (slth::Vector2f point : m_tempProcessedPath)
			{
				Waypoint wp = { point + m_pBlackboard->GetGrid()->GetTileOffset() , false };
				m_waypoints.emplace_back(wp);
			}

			// setup the final endpoint to slow down
			m_waypoints.back().m_slowDown = true;
			m_tempProcessedPath.clear();

			if (i == m_tempRawPath.size() - 1)
			{
				m_pathInProgress = false;
				m_lastPathedIndex = 0;
			}
		}
		else
		{
			// bail and continue next frame
			m_lastPathedIndex = i;
			break;
		}
	}
}

BehaviorNode::Status PathedBehavior::MoveAlongPath(float deltaTime, bool loop)
{
	// if no target, continue patrolling 
	if (m_tempRawPath.size() == 1 && !loop)
	{
		// edge case: this is a straight go-to single point, check that we're not already there
		slth::GridTile& startTile = m_pBlackboard->GetGrid()->GetTileAtScreenPosition(m_pTransform->GetPosition());

		if (startTile.GetIndex() == m_tempRawPath.back())
		{
			return Status::kSucceeded;
		}
		else
		{
			std::vector<size_t> newPath = { startTile.GetIndex(), m_tempRawPath.back() };
			SetRawPath(newPath, loop);
			return Status::kRunning;
		}
	}

	// update time sliced path here 
	if (m_pathInProgress)
	{
		StepPathFind(loop);
		return Status::kRunning;
	}

	if (m_waypoints.empty())
	{
		return Status::kFailed;
	}

	// check if we've reached the waypoint
	if (m_pTransform->GetPosition().IsApproximatleyEqualTo(m_waypoints[m_currentWaypointTarget].m_point, m_arriveThreshold))
	{
		if (m_currentWaypointTarget == m_waypoints.size() - 1 && !loop)
		{
			m_pTransform->Stop();
			return Status::kSucceeded;
		}

		m_waypoints[m_currentWaypointTarget] = NextWaypoint();

	}
	float slowRadius = 0.f;
	if (m_waypoints[m_currentWaypointTarget].m_slowDown)
	{
		slowRadius = kSlowRadius;
	}
	m_pTransform->MoveTowards(m_waypoints[m_currentWaypointTarget].m_point, deltaTime, slowRadius);
	m_pTransform->RotateTowards(m_waypoints[m_currentWaypointTarget].m_point, deltaTime);

	return Status::kRunning;
}

void PathedBehavior::Repath(bool loop)
{
	SetRawPath(m_tempRawPath, loop);
}
