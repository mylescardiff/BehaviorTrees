#include "IdleBehavior.h"
#include <Logic/Components/AIComponent/AIComponent.h>



IdleBehavior::IdleBehavior(float idleTime, AIComponent* pOwner)
	: ActionNode(pOwner)
	, m_duration(idleTime)
{
	//
}


IdleBehavior::IdleBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: ActionNode(pOwner)
{
	m_duration = pXmlElement->FloatAttribute("duration");
	m_timer = m_duration;

}


BehaviorNode::Status IdleBehavior::Run(float deltaTime)
{
	m_timer -= deltaTime;
	if (m_timer <= 0.f)
	{
		m_timer = m_duration;
		return Status::kSucceeded;

	}

	return Status::kRunning;

}
