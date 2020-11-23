#pragma once
/** \file TurnBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/ActionNode.h>


/// <summary>
/// Enables the AI to rotate to a new heading. Note: UP is zero rotation. 
/// </summary>
class TurnBehavior
	: public ActionNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	TurnBehavior(float angle, AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	TurnBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// On Enter behavior for turn. Basically just stops movement. 
	/// </summary>
	virtual void OnEnter() override;

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual Status Run(float deltaTime) override;

private:

	float m_angle;

};
