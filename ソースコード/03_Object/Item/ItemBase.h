/*********************************************************************
 * @file   ItemBase.h
 * @brief  アイテムの基底クラス
 *********************************************************************/
#ifndef __ITEM_BASE_H__
#define __ITEM_BASE_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"

class ItemBase : public Object
{
public:
	virtual void Init() override {};
	virtual	void Update(float deltatime) override;
private:
	float m_deleteTime = 0.0f;

};
#endif // !__ITEM_BASE_H__


