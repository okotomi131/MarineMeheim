/*********************************************************************
 * @file   CameraPlayer.h
 * @brief  プレイヤーに追尾するカメラ
 *********************************************************************/
#ifndef __CAMERA_PLAEYR_H__
#define __CAMERA_PLAEYR_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"
#include "CameraBase.h"

class CameraPlayer : public CameraBase
{
public:
	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	ゲッター

	==================================================
	*/
	DirectX::XMFLOAT3 Get_LookPoint();

private:
	/**
	 * @brief プレイヤーを追尾する
	 */
	void TrackTargetBack();

	DirectX::XMVECTOR m_vToTarget = {};
	DirectX::XMVECTOR m_vPos = {};

	float m_moveDelay	 = 0.1f;
	float m_distToTarget = 10.0f;
	float m_targetHeight = 5.0f;
};

#endif // !__CAMERA_PLAEYR_H__

