/*********************************************************************
 * @file   CameraTitle.h
 * @brief  �^�C�g����ʂł̃J����
 *********************************************************************/
#ifndef __CAMERA_TITLE_H__
#define __CAMERA_TITLE_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "CameraBase.h"

class CameraTitle : public CameraBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �X�V����
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

