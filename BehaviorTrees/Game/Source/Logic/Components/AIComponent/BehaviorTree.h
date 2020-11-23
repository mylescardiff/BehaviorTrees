#pragma once
/** \file BehaviorTree.h */
// Created by Myles Cardiff
#include <Logic/Components/AIComponent/CompositeNode.h>

class SequenceNode;

/// <summary>
/// BehaviorTree class
/// </summary>
class BehaviorTree
{
public:
		
	/// <summary>
	/// Default Constructor
	/// </summary>
	BehaviorTree();

	/// <summary>
	/// Default Destructor
	/// </summary>
	virtual ~BehaviorTree();

	/// <summary>
	/// Build the tree from XML
	/// </summary>
	/// <param name="pRootNode">The root XML node</param>
	/// <returns></returns>
	bool Init(XmlData* pRootNode, AIComponent* pOwner);

	/// <summary>
	/// Update (tick) function run once per frame
	/// </summary>
	/// <param name="deltaTime">Frame Time</param>
	virtual void Update(float deltaTime);

private:
	
	CompositeNode* m_pRootNode;
	BehaviorNode* m_pActiveNode;
	size_t m_activeSequenceIndex;
	void ProcessXmlNode(XmlData* pNode, CompositeNode* pParentTreeNode, AIComponent* pOwner);

public:

	void SetActiveNode(SequenceNode* pNode, size_t activeIndex);
	size_t GetActiveIndex() const { return m_activeSequenceIndex; }
};
