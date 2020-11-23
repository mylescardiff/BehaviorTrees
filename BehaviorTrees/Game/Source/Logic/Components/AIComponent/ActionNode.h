#pragma once
/** \file ActionNode.h */
// Created by Myles Cardiff

#include ".\BehaviorNode.h"

/// <summary>
/// An action node represents an actual behavior that the agent 
/// can perform (rather than a composite node). At the moment this
/// is a complete pass through for BehaviorNode, but future 
/// functionality may require this to be a distinct type. 
/// </summary>
class ActionNode
	: public BehaviorNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	ActionNode(class AIComponent* pOwner);
};
