/*********************************************************************
 * @file   CameraTitle.h
 * @brief  タイトル画面でのカメラ
 *********************************************************************/
#ifndef __CAMERA_TITLE_H__
#define __CAMERA_TITLE_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "CameraBase.h"

class CameraTitle : public CameraBase
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

	/**
	 * @brief 
	 * 
	 */
	void Draw() override;

private:
	DirectX::XMFLOAT3 m_startPos;
	DirectX::XMFLOAT3 m_endPos;
	DirectX::XMFLOAT3 m_startTarget;
	DirectX::XMFLOAT3 m_endTarget;
	
	float m_easingTime;
	float m_curTime;

	bool m_bEndMove;

};

#endif // !__CAMERA_TITLE_H__

