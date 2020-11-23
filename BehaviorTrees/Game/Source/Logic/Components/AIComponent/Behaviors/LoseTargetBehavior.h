#pragma once
/** \file LoseTargetBehavior.h */
// Created by Myles Cardiff

#include "..\ActionNode.h"

/// <summary>
/// Causes the agent to forget any target they had previously. 
/// </summary>
class LoseTargetBehavior
	: public ActionNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	LoseTargetBehavior(AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	LoseTargetBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Removes the target
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <returns></returns>
	virtual Status Run(float deltaTime) override;
	
};
