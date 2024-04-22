/*********************************************************************
 * @file   ItemBase.h
 * @brief  �A�C�e���̊��N���X
 *********************************************************************/
#ifndef __ITEM_BASE_H__
#define __ITEM_BASE_H__
 /*
 ==================================================

 �C���N���[�h

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


