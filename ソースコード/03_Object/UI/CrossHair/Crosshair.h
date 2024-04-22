/*********************************************************************
 * @file   Crosshair.h
 * @brief  クロスヘア
 *********************************************************************/
#ifndef __CROSSHAIR_H__
#define __CROSSHAIR_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../../Object.h"

class Crosshair : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init()override;
};

#endif // !__CROSSHAIR_H__

