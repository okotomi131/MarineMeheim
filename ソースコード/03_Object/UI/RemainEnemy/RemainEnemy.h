/*********************************************************************
 * @file   RemainEnemy.h
 * @brief  �G�̎c����\������UI�N���X
 *********************************************************************/
#ifndef __REMAIN_ENEMY_H__
#define __REMAIN_ENEMY_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../../Object.h"

class RemainEnemy : public Object
{
public:
	/**
	 * @brief ����������
	 */
	void Init()override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	void Update(float deltatime)override;

	/**
	 * @brief �`�揈��
	 */
	void Draw()override;

	/**
	 * @brief �A�j���[�V��������
	 */
	void StartAnime(float deltatime);	//�J�n�A�j���[�V����

	/**
	 * @brief �G�̎c�������炷
	 */
	void Set_EnemyMaxNum(int num) { m_enemyMaxNum = num; }	//�G�̍ő吔��ݒ肷��

	/**
	 * @brief �G�̎c�������炷
	 */
	int Get_CurEnemyNum() { return m_curEnemyNum; }	//���݂̓G�̎c�����擾����
private:


	const float MAX_START_ANIME_TIME = 1.0f;	//�J�n�A�j���[�V�����̍ő厞��
	const float START_ANIME_FINISH_POS_X = 1050.0f;//�J�n�A�j���[�V�����I������X���W
	const float START_ANIME_FINISH_POS_Y = -100.0f;//�J�n�A�j���[�V�����I������Y���W


	int m_curEnemyNum = 999;//�G�̎c��
	int m_enemyMaxNum;	//�G�̍ő吔
	const char* m_backGroundFileName;	//�w�i�̃t�@�C����
	
	float m_curStartAnimeTime = {};	//�J�n�A�j���[�V�����̎���

	DirectX::XMFLOAT2 m_CenterPos = {};	//���S���W
	DirectX::XMFLOAT2 m_initPos = {};	//���W

	class Sprite* m_sp = nullptr;	//�X�v���C�g

	float m_rotSpeed = 0.02f;	//��]���x
};

#endif // !__REMAIN_ENEMY_H__