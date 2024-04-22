/*********************************************************************
 * @file   Collider.h
 * @brief  �R���C�_�[
 *********************************************************************/
#ifndef __COLLIDER_H__
#define __COLLIDER_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"

class Collider: public Object
{
public:
	/*
	==================================================

	�Q�b�^�[

	==================================================
	*/

	/**
	 * @brief �ŏ����W���擾
	 * @return 
	 */
	DirectX::XMFLOAT3 const Get_wMinPoint() const;

	/**
	 * @brief �ő���W���擾
	 * @return 
	 */
	DirectX::XMFLOAT3 const Get_wMaxPoint() const;

	/**
	 * @brief �^�O���擾
	 * @return 
	 */
	inline std::string const Get_Tag() const { return m_tag; }

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/

	/**
	 * @brief �^�O����ݒ�
	 * @param tag
	 */
	inline void Set_Tag(std::string tag) { m_tag = tag; }

	/**
	 * @brief ���[���h���W��ŃT�C�Y��ݒ�
	 * @param size
	 */
	void Set_wSize(const DirectX::XMFLOAT3& size);

	/**
	 * @brief ���[���h���W��ݒ�
	 * @param matrix 
	 */
	inline void Set_WorldMatrix(const DirectX::XMMATRIX& matrix) { m_mWorld = matrix; }
private:

	std::string m_tag = "None";	//�^�O
	DirectX::XMMATRIX m_mWorld;

	ID3D11Buffer* m_pVertexBuffer = {};
	ID3D11Buffer* m_pIndexBuffer = {};

};

#endif // !__COLLIDER_H__

