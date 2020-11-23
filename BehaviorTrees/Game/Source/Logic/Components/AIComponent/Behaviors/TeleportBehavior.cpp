#include "TeleportBehavior.h"



TeleportBehavior::TeleportBehavior(slth::Vector2f position, float rotation, AIComponent* pOwner)
	: ActionNode(pOwner)
	, m_position(position)
	, m_rotation(rotation)
{
	//
}

TeleportBehavior::TeleportBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: ActionNode(pOwner)
{
	m_position = { pXmlElement->FloatAttribute("x"), pXmlElement->FloatAttribute("y") };
	m_rotation = pXmlElement->FloatAttribute("rotation");
}


BehaviorNode::Status TeleportBehavior::Run(float deltaTime)
{
	m_pTransform->Stop();

	m_pTransform->SetPosition(m_position);
	m_pTransform->SetRotation(m_rotation);

	return Status::kSucceeded;
}
