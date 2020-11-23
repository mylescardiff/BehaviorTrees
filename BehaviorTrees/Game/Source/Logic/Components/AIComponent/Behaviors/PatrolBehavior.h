#pragma once
/** \file PatrolBehavior.h */
// Created by Myles Cardiff
#include <Logic/Grid/GridSystem.h>
#include <Logic/Components/AIComponent/Behaviors/PathedBehavior.h>



/// <summary>
/// Agent will walk from waypoint to waypoint
/// </summary>
class PatrolBehavior
	: public PathedBehavior
{
public:
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	PatrolBehavior(AIComponent* pOwner);

	/// <summary>
	/// Explicit Constructor for following a path
	/// </summary>
	/// <param name="path">GridPath object (vector of Vector2fs)</param>
	PatrolBehavior(std::vector<size_t>& rawPath, AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	PatrolBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Update (Tick) function for the component
	/// </summary>
	/// <param name="deltaTime">Delta (frame) time</param>
	virtual Status Run(float deltaTime) override;


private:
	
	bool m_loop;

	// target aquisition data
	float m_radius;
	float m_visionArc;
	std::string m_tag;

	// constants

public:
	void SetLoop(bool loop) { m_loop = loop; }
};
