#pragma once
/** \file SequenceNode.h */
// Created by Myles Cardiff

#include ".\CompositeNode.h"

class AIComponent;

/// <summary>
/// A Sequence node will run children until one fails, then return. This
/// can be thought of as an "AND" method for beahviors. 
/// </summary>
class SequenceNode
	: public CompositeNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	SequenceNode(AIComponent* pOwner);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~SequenceNode();

	/// <summary>
	/// Update (tick) function for the selector node
	/// </summary>
	/// <param name="deltaTime">Time since last frame</param>
	/// <returns>Status of the behavior (Succeeded, Failed, or Running)</returns>
	virtual Status Run(float deltaTime) override;

};
