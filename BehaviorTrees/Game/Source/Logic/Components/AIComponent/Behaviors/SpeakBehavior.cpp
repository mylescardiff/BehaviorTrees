#include "SpeakBehavior.h"
#include <Logic/Actor.h>
#include <Logic/Components/TextComponent.h>
#include <Logic/Components/AIComponent/AIComponent.h>

SpeakBehavior::SpeakBehavior(const char* text, float duration, AIComponent* pOwner)
	: ActionNode(pOwner)
	, m_text(text)
	, m_duration(duration)
	, m_timer(duration)
{
	//
}

SpeakBehavior::SpeakBehavior(XmlData* pXmlElement, AIComponent* pOwner)
	: ActionNode(pOwner)
{
	m_text = pXmlElement->Attribute("text");
	m_duration = pXmlElement->FloatAttribute("duration");
	m_timer = m_duration;
}

void SpeakBehavior::OnEnter()
{
	m_pOwner->GetOwner()->GetComponent<slth::TextComponent>()->SetText(m_text);
	_LOGW(m_pOwner->GetOwner()->GetTag() + ": Started Speaking");
}


BehaviorNode::Status SpeakBehavior::Run(float deltaTime)
{

	m_timer -= deltaTime;
	if (m_timer <= 0.f)
	{
		m_pOwner->GetOwner()->GetComponent<slth::TextComponent>()->SetText("");
		_LOGW(m_pOwner->GetOwner()->GetTag() + ": Finished Speaking");
		return Status::kSucceeded;
	}

	return Status::kRunning;
}

void SpeakBehavior::OnExit()
{
	BehaviorNode::OnExit();

	m_timer = m_duration;
	m_pOwner->GetOwner()->GetComponent<slth::TextComponent>()->SetText("");
	_LOGW(m_pOwner->GetOwner()->GetTag() + ": Done Speaking");
}
