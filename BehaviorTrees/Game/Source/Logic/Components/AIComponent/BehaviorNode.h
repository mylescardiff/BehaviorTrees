#pragma once
/** \file BehaviorNode.h */
// Created by Myles Cardiff


#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/AIComponent/Blackboard.h>

class AIComponent;
class BehaviorTree;

/// <summary>
/// Base Behavior Node
/// </summary>
class BehaviorNode
{
public:

	enum class Status
	{
		kSucceeded,
		kFailed,
		kRunning
	};

	/// <summary>
	/// Default Constructor
	/// </summary>
	BehaviorNode(AIComponent* pOwner);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~BehaviorNode();

	/// <summary>
	/// Called when the behavior is started
	/// </summary>
	virtual void OnEnter() {};

	/// <summary>
	/// Called when the behavior is finished
	/// </summary>
	virtual void OnExit() {}

	/// <summary>
	/// Update (tick) function run once per frame
	/// </summary>
	///<param name = "deltaTime">Time since last frame< / param>
	/// <returns>Status of the behavior (Succeeded, Failed, or Running)</returns>
	virtual Status Update(float deltaTime);

	/// <summary>
	/// Base Run function (abstract)
	/// </summary>
	/// <param name="deltaTime">Time since last frame</param>
	/// <returns>Stauts of the action (Success, Failure, Running)</returns>
	virtual Status Run(float deltaTime) = 0;

protected:

	Status m_status;

	slth::TransformComponent* m_pTransform;
	AIComponent* m_pOwner;

	Blackboard* m_pBlackboard;
	BehaviorTree* m_pTree;

	
public:
	
	void SetTarget(slth::Actor* pTarget);
	slth::Actor* GetTarget() const;
	void SetTree(BehaviorTree* pTree);
};
