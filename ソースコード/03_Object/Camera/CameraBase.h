/*********************************************************************
 * @file   CameraBase.h
 * @brief  �J�����x�[�X
 *********************************************************************/
#ifndef __CAMERA_BASE_H_
#define __CAMERA_BASE_H_

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"

class CameraBase : public Object
{
public:
	/**
	 * @brief ����������
	 */
	virtual void Init() override;
	
	/**
	 * @brief �`�揈��
	 */
	virtual void Draw() override;

	/*
	==================================================

	�Q�b�^�[�E�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �r���[�s��擾
	 */
	DirectX::XMFLOAT4X4 Get_ViewMatrix() { return m_viewMatrix; };

	/**
	 * @throw �^�[�Q�b�g���W�擾
	 */
	void Set_TargetObj(Object* obj) { m_pTargetObj = obj; };

protected:
	DirectX::XMFLOAT3	m_target = {};
	DirectX::XMFLOAT3	m_up = {};
	Object* m_pTargetObj = {};
private:
	DirectX::XMFLOAT4X4	m_viewMatrix = {};
};


#endif // !__CAMERA_BASE_H_
