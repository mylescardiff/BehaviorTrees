#pragma once
/** \file TeleportBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/ActionNode.h>


/// <summary>
/// Enables teleporting the actor from one position & rotation to another instantly
/// </summary>
class TeleportBehavior
	: public ActionNode
{
public:
		
	/// <summary>
	/// Explicit Constructor
	/// </summary>
	TeleportBehavior(slth::Vector2f position, float rotation, AIComponent* pOwner);
	   
	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	TeleportBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual BehaviorNode::Status Run(float deltaTime) override;

private:
	
	slth::Vector2f m_position;
	float m_rotation;

};
