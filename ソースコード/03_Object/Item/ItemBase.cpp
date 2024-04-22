#include "ItemBase.h"

void ItemBase::Update(float deltatime)
{
	float rotYspeed = 0.025f;
	m_rot.y += rotYspeed;
	m_pos.y = std::abs(sinf(m_rot.y)); //’n–Ê‚É‚ß‚è‚Ü‚È‚¢‚æ‚¤‚Éâ‘Î’l‚ÅŒvZ
}
