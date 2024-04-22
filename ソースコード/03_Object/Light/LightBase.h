/*********************************************************************
 * @file   LightBase.h
 * @brief  ライトの基底クラス
 *********************************************************************/
#ifndef __LIGHT_BASE_H__
#define __LIGHT_BASE_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"

class LightBase : public Object
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
	//void Update(float deltatime) override;

	/**
	 * @brief ライトの方向を設定
	 * @param direction
	 */
	void Set_LightDirection(DirectX::XMFLOAT4 direction) { m_direction = direction; }
private:

	float m_curTime = 0.0f;
	LIGHT m_light = {};

	DirectX::XMFLOAT4 m_direction = {};
	DirectX::XMFLOAT4 m_ambient = { 0.5f,0.5f,0.5f,1.0f};
	DirectX::XMFLOAT4 m_diffuse = { 0.9f,0.9f,1.0f,1.0f };
};

#endif // !__LIGHT_BASE_H__

