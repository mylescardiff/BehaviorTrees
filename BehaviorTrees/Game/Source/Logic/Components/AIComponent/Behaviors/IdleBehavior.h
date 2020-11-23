#pragma once
/** \file IdleBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/ActionNode.h>


/// <summary>
/// Enables the AI to just sit and wait where they are for a specified amount of time. 
/// </summary>
class IdleBehavior
	: public ActionNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	IdleBehavior(float idleTime, AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	IdleBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual BehaviorNode::Status Run(float deltaTime) override;

private:

	float m_duration;
	float m_timer;

};
