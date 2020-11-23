#include <Logic/GameLogic.h>
#include <Utilities/Rng.h>
#include <Utilities/Utilities.h>
#include <SFML/Graphics.hpp>
#include <Logic/Components/TransformComponent.h>
#include <Logic/Components/AIComponent/AIComponent.h>
#include <Logic/Components/AIComponent/Behaviors/ChaseBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/IdleBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/SpeakBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/PatrolBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TurnBehavior.h>
#include <Logic/Components/AIComponent/Behaviors/TeleportBehavior.h>
#include <iostream>

GameLogic::GameLogic()
	: m_drawMode(DrawMode::kGrass)
{
	//
}

GameLogic::~GameLogic()
{
	Blackboard* pBlackboard = Blackboard::GetInstance();
	delete pBlackboard;
}

bool GameLogic::Init(slth::ApplicationLayer* pAppLayer)
{
	IGameLayer::Init(pAppLayer);

	pAppLayer->GetWindow()->SetTitle("GAP 321 - Behvaior Trees");

	// register custom components with the engine
	m_pActorFactory->RegisterComponentCreator(HASH("AI"), [](slth::Actor* pOwner) {
		return new AIComponent(pOwner);
	});

	// setup grid
	m_gridSystem.Init("Data\\guard-scene.xml");

	// setup blackboard
	Blackboard* pBlackboard = Blackboard::GetInstance();
	pBlackboard->SetGrid(&m_gridSystem);

	// load starting actors
	m_pActorFactory->CreateActors("Data\\actors.xml", m_actors, m_pGraphics, m_pWorld);

	// find relevant actors
	m_pRedAgent = FindActor("RedAgent");
	m_pGreenAgent = FindActor("GreenAgent");

	// make the AI blackboard aware of these two actors
	pBlackboard->PostActor(m_pRedAgent);
	pBlackboard->PostActor(m_pGreenAgent);

	return PostInit();
	
}


void GameLogic::Update(float deltaTime)
{
	IGameLayer::Update(deltaTime);
		
	slth::IKeyboard* pKeyboard = m_pAppLayer->GetKeyboard();

	if (pKeyboard->IsKeyPressed(slth::IKeyboard::KeyCode::P))
	{
		m_gridSystem.ToggleWeightMode();
		const char* onOff = m_gridSystem.GetWeightOnlyMode() ? "Off" : "On";
		_LOGW(std::string("Smoother Path Mode: ") + onOff );
	}
}

void GameLogic::PreDraw()
{
	m_gridSystem.Draw(m_pGraphics);
}




