#include "LoseTargetBehavior.h"

LoseTargetBehavior::LoseTargetBehavior(AIComponent* pOwner)
	: ActionNode(pOwner)
{
	//
}

LoseTargetBehavior::LoseTargetBehavior(XmlData* xmlElement, AIComponent* pOwner)
	:ActionNode(pOwner)
{
	//
}



BehaviorNode::Status LoseTargetBehavior::Run(float deltaTime)
{
	SetTarget(nullptr);
	return Status::kSucceeded;
}
