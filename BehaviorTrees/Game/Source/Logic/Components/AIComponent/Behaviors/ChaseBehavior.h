#pragma once
/** \file ChaseBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/Behaviors/PathedBehavior.h>
#include <Logic/Actor.h>

/// <summary>
/// Enables this actor to chase another actor 
/// </summary>
class ChaseBehavior
	: public PathedBehavior
{
public:
	
	/// <summary>
	/// Explicit Constructor
	/// </summary>
	ChaseBehavior(slth::Actor* pActor, float aquireDistance, AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	ChaseBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Run Behavior
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual Status Run(float deltaTime) override;

private:
	
	float m_acquireDistance;
	float m_repathTime; 
	float m_timer;

	// constants
	static constexpr float s_kPredictTurns = 1000;

};
