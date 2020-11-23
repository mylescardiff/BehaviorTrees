#pragma once
/** \file CompositeNode.h */
// Created by Myles Cardiff

#include ".\BehaviorNode.h"

class AIComponent;

/// <summary>
/// Base class for all nodes that have children (Sequence and 
/// </summary>
class CompositeNode
	: public BehaviorNode
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	CompositeNode(AIComponent* pOwner);

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~CompositeNode();

protected:

	std::vector<BehaviorNode*> m_children;

public:
	
	void AddChild(BehaviorNode* pChildNode) { m_children.emplace_back(pChildNode); };

};
