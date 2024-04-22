/*********************************************************************
 * @file   Clownfish.h
 * @brief  敵(クマノミ)のクラス
 *********************************************************************/
#ifndef __CLOWN_FISH_H__
#define	__CLOWN_FISH_H__
/*
==================================================

インクルード

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

