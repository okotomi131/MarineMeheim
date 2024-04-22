/*********************************************************************
 * @file   GlobeFish.h
 * @brief  敵(フグ)クラス
 *********************************************************************/
#ifndef __ENEMY_GLOBE_FISH_H__
#define __ENEMY_GLOBE_FISH_H__
/*
==================================================

インクルード

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


