#include "ChaseBehavior.h"
#include <Logic/Actor.h>
#include <Logic/Components/AIComponent/AIComponent.h>
#include <Logic/Grid/GridTile.h>
#include <Logic/Grid/GridSystem.h>


ChaseBehavior::ChaseBehavior(slth::Actor* pActor, float acquireDistance, AIComponent* pOwner)
	: PathedBehavior(pOwner)
	, m_repathTime(0.f)
	, m_timer(0.f)

{
	m_arriveThreshold = acquireDistance;
}

ChaseBehavior::ChaseBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: PathedBehavior(pOwner)
{
	m_arriveThreshold = pXmlElement->FloatAttribute("acquire-distance");
	m_repathTime = pXmlElement->FloatAttribute("repath-time");
	m_timer = m_repathTime;
}


BehaviorNode::Status ChaseBehavior::Run(float deltaTime)
{
	if (!GetTarget())
		return Status::kFailed;

	// predict the target's position
	slth::TransformComponent* pTargetTransform = GetTarget()->GetComponent<slth::TransformComponent>();
	slth::Vector2f targetPos = pTargetTransform->GetPosition() + pTargetTransform->GetVelocity() * s_kPredictTurns * deltaTime;

	m_timer -= deltaTime;

	if (m_timer <= 0)
	{
		// timer has expired, repath
		std::vector<size_t> rawPath;
		rawPath.reserve(2);
		slth::GridTile& myTile = m_pBlackboard->GetGrid()->GetTileAtScreenPosition(m_pTransform->GetPosition());
		slth::GridTile& targetTile = m_pBlackboard->GetGrid()->GetTileAtScreenPosition(targetPos);

		rawPath.emplace_back(myTile.GetIndex());
		rawPath.emplace_back(targetTile.GetIndex());

		SetRawPath(rawPath, false);

		m_timer = m_repathTime;
	}

	return MoveAlongPath(deltaTime, false);

	
}

