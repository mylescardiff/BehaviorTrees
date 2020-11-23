#include "BehaviorTree.h"
#include <Logic/Components/AIComponent/SelectorNode.h>
#include <Logic/Components/AIComponent/SequenceNode.h>
#include <Logic/Components/AIComponent/Behaviors/PatrolBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/SpeakBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/IdleBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TeleportBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TurnBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/LoseTargetBehavior.h>


BehaviorTree::BehaviorTree()
	: m_pActiveNode(nullptr)
	, m_pRootNode(nullptr)
	, m_activeSequenceIndex(0)
{
	//
}

BehaviorTree::~BehaviorTree()
{
	delete m_pRootNode;
}

bool BehaviorTree::Init(XmlData* pXmlRootNode, AIComponent* pOwner)
{
	m_pRootNode = new SelectorNode(pOwner);
	m_pRootNode->SetTree(this);
	ProcessXmlNode(pXmlRootNode, m_pRootNode, pOwner);
	m_pActiveNode = m_pRootNode;
	return true;
}

void BehaviorTree::Update(float deltaTime)
{
	if (m_pActiveNode)
	{
		BehaviorNode::Status result = m_pActiveNode->Update(deltaTime);
		
		if (result != BehaviorNode::Status::kRunning)
		{
			m_pActiveNode = m_pRootNode;
			m_activeSequenceIndex = 0;
		}
	}
}

void BehaviorTree::ProcessXmlNode(XmlData* pXmlNode, CompositeNode* pParentTreeNode, AIComponent* pOwner)
{
	if (!pXmlNode)
		return;

	// first process as a composite node...
	if (strcmp(pXmlNode->Name(), "Selector") == 0 || strcmp(pXmlNode->Name(), "Sequence") == 0)
	{
		CompositeNode* pCompositeNode = nullptr;
		if (strcmp(pXmlNode->Name(), "Selector") == 0)
			pCompositeNode = new SelectorNode(pOwner);

		if (strcmp(pXmlNode->Name(), "Sequence") == 0)
			pCompositeNode = new SequenceNode(pOwner);

		XmlData* pChild = pXmlNode->FirstChildElement();
		while (pChild)
		{
			ProcessXmlNode(pChild, pCompositeNode, pOwner);
			pChild = pChild->NextSiblingElement();
		}

		pParentTreeNode->AddChild(pCompositeNode);
		pCompositeNode->SetTree(this);
	}
	else
	{
		BehaviorNode* pBehaviorNode = nullptr;
		//... then do it as a behavior, with no children
		if (strcmp(pXmlNode->Name(), "Patrol") == 0)
		{
			pBehaviorNode = new PatrolBehavior(pXmlNode, pOwner);
		}
		else if (strcmp(pXmlNode->Name(), "Speak") == 0)
		{
			pBehaviorNode = new SpeakBehavior(pXmlNode, pOwner);
		}
		else if (strcmp(pXmlNode->Name(), "Idle") == 0)
		{
			pBehaviorNode = new IdleBehavior(pXmlNode, pOwner);
		}
		
		else if (strcmp(pXmlNode->Name(), "LoseTarget") == 0)
		{
			pBehaviorNode = new LoseTargetBehavior(pXmlNode, pOwner);
		}
		else if (strcmp(pXmlNode->Name(), "Teleport") == 0)
		{
			pBehaviorNode = new TeleportBehavior(pXmlNode, pOwner);
		}
		else if (strcmp(pXmlNode->Name(), "Chase") == 0)
		{
			pBehaviorNode = new ChaseBehavior(pXmlNode, pOwner);
		}
		else if (strcmp(pXmlNode->Name(), "Turn") == 0)
		{
			pBehaviorNode = new TurnBehavior(pXmlNode, pOwner);
		}
		else
		{
			_LOGE(std::string("Behavior type not implemented: ") + pXmlNode->Name());
		}
		pParentTreeNode->AddChild(pBehaviorNode);
		pBehaviorNode->SetTree(this);
	}

}

void BehaviorTree::SetActiveNode(SequenceNode* pNode, size_t activeIndex)
{
	 m_pActiveNode = pNode; 
	 m_activeSequenceIndex = activeIndex;
}

