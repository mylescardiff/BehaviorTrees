#include "Blackboard.h"
#include <Utilities/Hasher.h>


Blackboard* Blackboard::m_pInstance = nullptr;

Blackboard* Blackboard::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Blackboard();
	}

	return m_pInstance;
}

void Blackboard::PostActor(slth::Actor* pActor)
{
	m_postedActors.emplace(slth::Hasher::Hash32(pActor->GetName().c_str()), pActor);
}

slth::Actor* Blackboard::GetActor(const char* tag)
{
	Id32 hashTag = slth::Hasher::Hash32(tag);
	auto foundActor = m_postedActors.find(hashTag);
	if (foundActor != m_postedActors.end())
		return foundActor->second;

	return nullptr;
}
