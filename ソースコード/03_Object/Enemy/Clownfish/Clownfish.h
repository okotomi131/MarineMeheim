/*********************************************************************
 * @file   Clownfish.h
 * @brief  �G(�N�}�m�~)�̃N���X
 *********************************************************************/
#ifndef __CLOWN_FISH_H__
#define	__CLOWN_FISH_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Scorpionfish/EnemyScorpionFish.h"

class Clownfish : public EnemyScorpionFish
{
public:
	static void Load();
	void Init()override;
};

#endif // !__CLOWN_FISH_H__

