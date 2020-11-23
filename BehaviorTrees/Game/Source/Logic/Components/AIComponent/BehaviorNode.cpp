#include "BehaviorNode.h"
#include <Logic/Components/AIComponent/AIComponent.h>
#include "BehaviorTree.h"

BehaviorNode::BehaviorNode(AIComponent* pOwner)
	: m_pOwner(pOwner)
	, m_pTree(nullptr)
	, m_status(Status::kFailed)
{
	m_pBlackboard = Blackboard::GetInstance();
	m_pTransform = pOwner->GetOwner()->GetComponent<slth::TransformComponent>();
}


BehaviorNode::~BehaviorNode()
{
	//
}



BehaviorNode::Status BehaviorNode::Update(float deltaTime)
{
	if (m_status != Status::kRunning)
		OnEnter();

	m_status = Run(deltaTime);

	if (m_status != Status::kRunning)
		OnExit();

	return m_status;
}



void BehaviorNode::SetTarget(slth::Actor* pTarget)
{
	m_pOwner->SetTarget(pTarget);
}

slth::Actor* BehaviorNode::GetTarget() const
{
	return m_pOwner->GetTarget();
}

void BehaviorNode::SetTree(BehaviorTree* pTree)
{
	m_pTree = pTree;
}

