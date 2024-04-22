/*********************************************************************
 * @file   Sky.h
 * @brief  スカイドーム
 *********************************************************************/
#ifndef __SKY_H__
#define __SKY_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"
class Sky : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

};
#endif // !__SKY_H__


