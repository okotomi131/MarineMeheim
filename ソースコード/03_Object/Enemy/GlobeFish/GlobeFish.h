/*********************************************************************
 * @file   GlobeFish.h
 * @brief  �G(�t�O)�N���X
 *********************************************************************/
#ifndef __ENEMY_GLOBE_FISH_H__
#define __ENEMY_GLOBE_FISH_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Scorpionfish/EnemyScorpionFish.h"

class GlobeFish : public EnemyScorpionFish
{
public:
	static void Load();
	void Init()override;
};

#endif // !__ENEMY_GLOBE_FISH_H__


