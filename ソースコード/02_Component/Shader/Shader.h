/*********************************************************************
 * @file   Shader.h
 * @brief  �V�F�[�_�[�̓ǂݍ���
 *********************************************************************/

#ifndef __SHADER_H__
#define __SHADER_H__

/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Component.h"

class Shader : public Component
{
public:
	using Component::Component;

	/**
	 * @brief �V�F�[�_�[�̓ǂݍ���
	 * @param vs ���_�V�F�[�_�[�t�@�C����
	 * @param ps �s�N�Z���V�F�[�_�[�t�@�C����
	 */
	void Load(const char* vs, const char* ps);

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

private:
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;
	ID3D11InputLayout*	m_pVertexLayout;
};


#endif // !__SHADER_H__


