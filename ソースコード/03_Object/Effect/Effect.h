/*********************************************************************
 * @file   Effect.h
 * @brief  �G�t�F�N�g��ėp�I�ɐ�������
 *********************************************************************/
#ifndef __EFFECT_H__
#define __EFFECT_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"
#include "../../01_System/Texture/CreateTexture.h"

class Effect : public Object
{
public:
	/**
	 * @brief �t�@�C���ǂݍ���
	 * @param filename
	 */
	void Load(const char* filename);

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

	/*
	==================================================

	�Z�b�^�[

	==================================================
	*/
	/**
	 * @birief �A�j���[�V�����̕�������ݒ肷��
	 */
	void Set_UvDivision(int x, int y) { m_uvX = x; m_uvY = y; };

	/**
	 * @brief �A�j���[�V�����̍Đ����Ԃ�ݒ肷��
	 */
	void Set_PlayTime(float time)	  { m_animeTime = time; };

private:
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_pTexture = nullptr;

	int		m_animeCnt = 0;
	float	m_animeTime = -1.0f;
	int		m_uvX = 1;
	int		m_uvY = 1;
	float   m_curTime = 1.0f;
};

#endif // !__EFFECT_H__


