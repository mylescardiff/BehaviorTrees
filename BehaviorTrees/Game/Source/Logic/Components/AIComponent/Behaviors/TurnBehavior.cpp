#include "TurnBehavior.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/AIComponent/AIComponent.h>


TurnBehavior::TurnBehavior(float angle, AIComponent* pOwner)
	: ActionNode(pOwner)
	, m_angle(angle)
{
	//
}


TurnBehavior::TurnBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: ActionNode(pOwner)
{
	m_angle = pXmlElement->FloatAttribute("angle");
}


void TurnBehavior::OnEnter()
{
	m_pTransform->Stop();
}

BehaviorNode::Status TurnBehavior::Run(float deltaTime)
{
	float targetRotation = m_pTransform->GetRotation();
	m_pTransform->RotateTowards(m_angle, deltaTime);
	if (std::abs(m_angle - targetRotation) < 2.f)
	{
		return Status::kSucceeded;
	}
	
	return Status::kRunning;
}
