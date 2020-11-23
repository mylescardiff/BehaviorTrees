#pragma once
/** \file SelectorNode.h */
// Created by Myles Cardiff

#include ".\CompositeNode.h"

/// <summary>
/// A selector node will attempt to run child nodes one at a time
/// and return the first one that does not fail. This can be thought
/// of this as an "OR" method for behaviors. 
/// </summary>
class SelectorNode
	: public CompositeNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	SelectorNode(AIComponent* pOwner);

	/// <summary>
	/// Update (tick) function for the selector node
	/// </summary>
	/// <param name="deltaTime">Time since last frame</param>
	/// <returns>Status of the behavior (Succeeded, Failed, or Running)</returns>
	virtual BehaviorNode::Status Run(float deltaTime) override;


};
