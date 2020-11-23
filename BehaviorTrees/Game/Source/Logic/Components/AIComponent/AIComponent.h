#pragma once
/** \file AIComponent.h */
// Created by Myles Cardiff

#include <vector>
#include <Utilities/Vector2f.h>
#include <Utilities/Hasher.h>
#include <Logic/Components/IComponent.h>
#include <Logic/Components/AIComponent/BehaviorTree.h>

/// <summary>
/// The AIComponent adds behavior tree based functionality to an actor. 
/// </summary>
class AIComponent
	: public slth::IComponent
{
public:
	
	// Identity 
	inline static constexpr const char* kStringId = "AI";
	static constexpr Id Identifier = slth::Hasher::Hash32(kStringId);
	SLTH_API virtual const char* GetName() const override { return kStringId; }
	SLTH_API virtual const Id GetIdentifier() const override { return Identifier; }

	/// <summary>
	/// Default Constructor
	/// </summary>
	AIComponent(slth::Actor* pOwner);

	/// <summary>
	/// Creates a copy of the transform component
	/// </summary>
	/// <param name="pNewOwner">The new owning actor of this component</param>
	/// <returns>A pointer to the new copy</returns>
	virtual IComponent* Copy(slth::Actor* pNewOwner) override;

	/// <summary>
	/// Initilizes the transform component from XML node (see /data/actors.xml for syntax)
	/// </summary>
	/// <param name="xmlElement">The tinyxml node pointer contianing the data</param>
	/// <returns></returns>
	virtual bool Init(XmlData* pXmlElement) override;

	/// <summary>
	/// Updates the transform and velocity based on info from the AI's logic
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	void Update(float deltaTime);

	static constexpr float kSlowRadius = 50.f;

private:

	BehaviorTree m_behaviorTree;
	slth::Actor* m_pTarget;
public:

	void SetTarget(slth::Actor* pTarget) { m_pTarget = pTarget; }
	slth::Actor* GetTarget() const { return m_pTarget; }

};
