#include "ItemBase.h"

void ItemBase::Update(float deltatime)
{
	float rotYspeed = 0.025f;
	m_rot.y += rotYspeed;
	m_pos.y = std::abs(sinf(m_rot.y)); //�n�ʂɂ߂荞�܂Ȃ��悤�ɐ�Βl�Ōv�Z
}
