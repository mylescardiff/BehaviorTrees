#include "SequenceNode.h"
#include <Logic/Components/AIComponent/Behaviors/SpeakBehavior.h>
#include <Logic/Components/AIComponent/BehaviorTree.h>



SequenceNode::SequenceNode(AIComponent* pOwner)
	: CompositeNode(pOwner)
{
	
}

SequenceNode::~SequenceNode()
{
	
}

BehaviorNode::Status SequenceNode::Run(float deltaTime)
{
	for (size_t i = m_pTree->GetActiveIndex(); i < m_children.size(); ++i)
	{
		BehaviorNode* pChildNode = m_children[i];
		
		Status childResult = pChildNode->Update(deltaTime);
		
		if (childResult == Status::kRunning)
		{
			m_pTree->SetActiveNode(this, i);
		}

		if (childResult != Status::kSucceeded)
		{
			return childResult;
		}
			

	}
	return Status::kSucceeded;
}

