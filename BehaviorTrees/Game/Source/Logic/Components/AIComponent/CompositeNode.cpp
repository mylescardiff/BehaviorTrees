#include "CompositeNode.h"
#include <Logic/Components/AIComponent/AIComponent.h>


CompositeNode::CompositeNode(AIComponent* pOwner)
	: BehaviorNode(pOwner)
{
	//
}


CompositeNode::~CompositeNode()
{
	for (BehaviorNode* pChild : m_children)
	{
		delete pChild;
	}
}