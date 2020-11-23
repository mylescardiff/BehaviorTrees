#pragma once
#include <Logic/Grid/GridSystem.h>
#include <Logic/Actor.h>
#include <Utilities/Rng.h>

/** \file Blackboard.h */
// Created by Myles Cardiff


/// <summary>
/// Blackboard holds common data that the AI behaviors need to 
/// function. This is a singleton class. It should be instatiated 
/// and populated with data in your GameLogic class (probably in Init).  
/// </summary>
class Blackboard
{
	/// <summary>
	/// Private Constructor
	/// </summary>
	Blackboard()
		: m_pGrid(nullptr)
	{
		m_rng.Seed(time(NULL));
	}

	static Blackboard* m_pInstance;
	slth::GridSystem* m_pGrid;
	slth::Vector2f m_tileOffset;
	slth::Rng m_rng;
	std::map<Id32, slth::Actor*> m_postedActors;

public:
	
	/// <summary>
	/// Get the static instance of the blackboard.
	/// </summary>
	/// <returns></returns>
	static Blackboard* GetInstance();

	// accessors & mutators
	void SetGrid(slth::GridSystem* pGrid) { m_pGrid = pGrid; }
	slth::GridSystem* GetGrid() const { return m_pGrid; }
	slth::Rng& GetRng() { return m_rng; }
	void PostActor(slth::Actor* pActor);
	slth::Actor* GetActor(const char* tag);

};
