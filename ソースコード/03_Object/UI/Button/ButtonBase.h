/*********************************************************************
 * @file   ButtonBase.h
 * @brief  �{�^�����쐬����
 *********************************************************************/
#ifndef __BUTTON_BASE_H__
#define __BUTTON_BASE_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../../Object.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Sound/Sound.h"
class ButtonBase :public Object
{
public:
	void Load(const char* path);
	void Init()override;
	void Update(float deltatime)override;

	/**
	 * @brief �X�v���C�g�ɒ��ڍ��W���Z�b�g����
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)
	{
		m_pSprite->Set_Pos(pos);
	}

	/**
	 * @brief �X�v���C�g�ɒ��ڃT�C�Y���Z�b�g����
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size)
	{	m_pSprite->Set_Size(size);	}

	/**
	 * @brief �{�^���������ꂽ��
	 * @return ������Ă�����true
	 */
	bool IsOverlap(bool force = false);

	/**
	 * @brief �T�E���h�̒ǉ�
	 * @param fileName �T�E���h�̃p�X
	 * @param keyname �T�E���h�̃L�[��
	 */
	inline void Add_Sound(const char* fileName, const std::string keyname)
	{
		m_pSoundList.insert(std::make_pair(keyname, Add_Component<Sound>()));
		m_pSoundList[keyname]->Load(fileName);
	}

	/**
	 * @brief �T�E���h�̍Đ�
	 * @param keyname �T�E���h�̃L�[��
	 * @param loop ���[�v�Đ����邩�ǂ���
	 */
	inline void Play_Sound(const std::string keyname, const bool loop = false)
	{
		m_pSoundList[keyname]->Play(loop);
	}

	/**
	 * @brief �T�E���h����񂾂��炷��
	 * @param bOnceSound
	 */
	inline void Set_OnceSound(bool bOnceSound) { m_bOnceSound = bOnceSound; }

	/**
	 * @brief ��񂾂��炷�T�E���h���ǂ���
	 * @param bOnceSound ��񂾂��炷�T�E���h�Ȃ�true
	 */
	inline bool Get_OnceSound() { return m_bOnceSound; }

	/**
	 * @brief ��ʊO�ɔz�u
	 */
	inline void OutScreen() {	m_pSprite->Set_Pos({9999.9f,9999.9f}); }
private:
	Sprite* m_pSprite = nullptr;
	std::unordered_map<std::string,Sprite*> m_pButtonList = {};
	std::unordered_map<std::string, Sound*> m_pSoundList = {};
	bool m_bOverlap = false;
	bool m_bOnceSound = false;
};

#endif // !__BUTTON_BASE_H__


