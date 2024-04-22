/*********************************************************************
 * @file   CameraPlayer.h
 * @brief  �v���C���[�ɒǔ�����J����
 *********************************************************************/
#ifndef __CAMERA_PLAEYR_H__
#define __CAMERA_PLAEYR_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../Object.h"
#include "CameraBase.h"

class CameraPlayer : public CameraBase
{
public:
	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/
	DirectX::XMFLOAT3 Get_LookPoint();

private:
	/**
	 * @brief �v���C���[��ǔ�����
	 */
	void TrackTargetBack();

	DirectX::XMVECTOR m_vToTarget = {};
	DirectX::XMVECTOR m_vPos = {};

	float m_moveDelay	 = 0.1f;
	float m_distToTarget = 10.0f;
	float m_targetHeight = 5.0f;
};

#endif // !__CAMERA_PLAEYR_H__

