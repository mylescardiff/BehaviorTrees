#include "SelectorNode.h"

SelectorNode::SelectorNode(AIComponent* pOwner)
	: CompositeNode(pOwner)
{
	//
}

BehaviorNode::Status SelectorNode::Run(float deltaTime)
{
	for (BehaviorNode* pChildNode : m_children)
	{
		Status childResult = pChildNode->Update(deltaTime);
		if (childResult != Status::kFailed)
			return childResult;
			
	}
	// if all children have run without a Success or Running status, this node failed.
	return Status::kFailed;
}

