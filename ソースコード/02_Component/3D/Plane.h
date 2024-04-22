/*********************************************************************
 * @file   Plane.h
 * @brief  �|���S����`�悷��R���|�[�l���g
 *********************************************************************/
#ifndef __PLANE_H__
#define __PLANE_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Component.h"

class Plane : public Component
{
public:
	using Component::Component;
	/**
	 * @brief ����������
	 * @param fileName �t�@�C����
	 */
	void Init(const char* fileName);

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

private:
	ID3D11Buffer*			  m_pVertexBuffer = {};
	ID3D11ShaderResourceView* m_pTexture = {};
	ID3D11ShaderResourceView* m_pCellTexture = {};
};

#endif // !__PLANE_H__

