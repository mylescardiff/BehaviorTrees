#pragma once
/** \file SpeakBehavior.h */
// Created by Myles Cardiff

#include <Logic/Components/AIComponent/ActionNode.h>


/// <summary>
/// Enables the actor to print text on the screen for a specified number of seconds. 
/// </summary>
class SpeakBehavior
	: public ActionNode
{
public:
	
	
	/// <summary>
	/// Default Constructor
	/// </summary>
	SpeakBehavior(const char* text, float duration, AIComponent* pOwner);

	/// <summary>
	/// XML Based Initializer
	/// </summary>
	/// <param name="xmlElement"></param>
	SpeakBehavior(XmlData* xmlElement, AIComponent* pOwner);

	/// <summary>
	/// Initiate the speaking
	/// </summary>
	virtual void OnEnter() override;

	/// <summary>
	/// Update (Tick) function
	/// </summary>
	/// <param name="deltaTime">Frame time</param>
	virtual Status Run(float deltaTime) override;

	/// <summary>
	/// Resets the clock so this action can be repeated
	/// </summary>
	virtual void OnExit() override;
	
private:
	
	std::string m_text;
	float m_timer;
	float m_duration;


};
