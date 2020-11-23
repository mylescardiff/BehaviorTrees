#pragma once
/** \file GameApp.h */
// Created by Myles Cardiff

#include <Application/ApplicationLayer.h>
#include <Logic/IGameLayer.h>
#include <Logic/Actor.h>
#include <Logic/ActorFactory.h>
#include <Utilities/Rng.h>
#include <Logic/Components/TextComponent.h>

#undef _DEBUG_DRAW
#define _DEBUG_DRAW 1

/// <summary>
/// Game Logic, inherits from slth::IGameLayer, this is the primary logic file for all gameplay code. 
/// </summary>
class GameLogic
	: public slth::IGameLayer
{

public:

	/// <summary>
	/// Tile draw mode for right-click painting tiles
	/// </summary>
	enum class DrawMode
	{
		kGrass,
		kFlowers,
		kBridge,
		kWater
	};

	/// <summary>
	/// Default Constructor
	/// </summary>
	GameLogic();

	/// <summary>
	/// Default Destructor
	/// </summary>
	~GameLogic();

	/// <summary>
	/// Override for setting the game name / window title 
	/// </summary>
	/// <returns>C-Style string name</returns>
	const char* GetGameName() const override{ return "GAP 321 - Behavior Trees"; }
	
	/// <summary>
	/// Initialize the game logic
	/// </summary>
	/// <param name="pAppLayer"></param>
	/// <returns></returns>
	virtual bool Init(slth::ApplicationLayer* pAppLayer) override;

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual void Update(float deltaTime) override;

	/// <summary>
	/// Called in the middle of IGameLayer::Draw()
	/// </summary>
	virtual void PreDraw() override;

protected:

	slth::Actor* m_pRedAgent;
	slth::Actor* m_pGreenAgent;

	slth::GridSystem m_gridSystem;
	DrawMode m_drawMode;

	static constexpr long long kPathTimeAllowed = 6;

};

