#include "BGM.h"

void BGM::Uninit()
{
	for (auto& sound : m_soundList)
	{	sound.second->Stop();	}
	m_soundList.clear();
}
