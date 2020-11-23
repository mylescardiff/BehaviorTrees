#include "AIComponent.h"
#include <Logic/Components/TransformComponent.h>
#include <Logic/Actor.h>
#include <tinyxml2.h> 
#include <Logic/Components/AIComponent/Behaviors/PatrolBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/SpeakBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/IdleBehavior.h>

AIComponent::AIComponent(slth::Actor* pOwner)
{
	m_pOwner = pOwner;
}

slth::IComponent* AIComponent::Copy(slth::Actor* pNewOwner)
{
	AIComponent* pCopy = new AIComponent(pNewOwner);
	return pCopy;
}

bool AIComponent::Init(XmlData* pXmlElement)
{
	// see if a behavior tree is defined
	XmlData* pBehaviorTreeNode = pXmlElement->FirstChildElement("BehaviorTree");
	if (pBehaviorTreeNode)
	{
		m_behaviorTree.Init(pBehaviorTreeNode->FirstChildElement(), this);
	}
	return true;
}


void AIComponent::Update(float deltaTime)
{
	m_behaviorTree.Update(deltaTime);
}





