/*********************************************************************
 * @file   HPBase.cpp
 * @brief  HPˆ—
 *********************************************************************/
#include "HPBase.h"

void HPBase::Heal(float heal)
{
	if (m_MaxHP > m_curHP)
	{
		m_curHP += heal;
		if (m_curHP >= m_MaxHP) { m_curHP = m_MaxHP; }
	}
}
