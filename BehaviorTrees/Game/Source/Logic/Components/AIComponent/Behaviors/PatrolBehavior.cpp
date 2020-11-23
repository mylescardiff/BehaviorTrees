#include "PatrolBehavior.h"
#include <Logic/Components/AIComponent/AIComponent.h>
#include <Logic/Actor.h>

PatrolBehavior::PatrolBehavior(AIComponent* pOwner)
	: PathedBehavior(pOwner)
	, m_loop(false)
	, m_visionArc(0.f)
	, m_radius(0.f)
{
	//
}


PatrolBehavior::PatrolBehavior(std::vector<size_t>& rawPath, AIComponent* pOwner)
	: PathedBehavior(pOwner)
	, m_loop(true)
	, m_visionArc(0.f)
	, m_radius(0.f)
{
	SetRawPath(rawPath, m_loop);
}

PatrolBehavior::PatrolBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: PathedBehavior(pOwner)
	, m_loop(true)
{
	m_loop = pXmlElement->BoolAttribute("loop");
	m_arriveThreshold = pXmlElement->BoolAttribute("arrive-distance");
	if (m_arriveThreshold == 0.f)
		m_arriveThreshold = kDefaultArriveThreshold;

	m_radius = pXmlElement->FloatAttribute("radius");
	m_visionArc = pXmlElement->FloatAttribute("vision-arc");
	const char* checkForTag = pXmlElement->Attribute("target");
	if (checkForTag)
		m_tag = std::string(checkForTag);

	// find path
	std::vector<size_t> rawPath;

	// get waypoints for patrol, if any
	for (XmlData* pElement = pXmlElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
	{
		slth::Vector2f wp;
		wp.x = pElement->FloatAttribute("x");
		wp.y = pElement->FloatAttribute("y");

		slth::GridTile& tile = m_pBlackboard->GetGrid()->GetTileAtScreenPosition(wp);
		rawPath.emplace_back(tile.GetIndex());
	}
		
	SetRawPath(rawPath, m_loop);

}


BehaviorNode::Status PatrolBehavior::Run(float deltaTime)
{
	// look for target
	if (!m_tag.empty())
	{
		slth::Actor* pTarget = Blackboard::GetInstance()->GetActor(m_tag.c_str());
		slth::Vector2f targetPosition = pTarget->GetComponent<slth::TransformComponent>()->GetPosition();

		float angleDiff = slth::Vector2f::AngleBetween(m_pTransform->GetPosition(), targetPosition) - m_pTransform->GetRotation();
		float distanceTo = m_pTransform->GetPosition().DistanceTo(targetPosition);
		if (std::abs(angleDiff) < m_visionArc / 2.f && distanceTo <= m_radius)
		{
			m_pTransform->Stop();
			SetTarget(pTarget);
			return Status::kSucceeded;
		}

		else if (GetTarget())
		{
			SetTarget(nullptr);
		}
	}

	return MoveAlongPath(deltaTime, m_loop);
}