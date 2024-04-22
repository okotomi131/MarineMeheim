/*********************************************************************
 * @file   ImageDrawer.h
 * @brief  2D�摜��ėp�I�ɕ`�悷��N���X
 *********************************************************************/
#ifndef __IMAGE_DRAWER_H__
#define __IMAGE_DRAWER_H__
/*
==================================================

�C���N���[�h

==================================================
*/
#include "../Object.h"
#include "../../02_Component/Sprite/Sprite.h"
#include "../../02_Component/Sound/Sound.h"

class ImageDrawer : public Object
{
public:

	/**
	 * @brief ����������
	 */
	void Init() override;

	/**
	 * @brief �I������
	 */
	void Uninit() override;

	/**
	 * @brief �X�V����
	 * @param deltatime
	 */
	//void Update(float deltatime) override;

	/**
	 * @brief �`�揈��
	 */
	//	void Draw() override;

	
	/**
	 * @brief �p�X����摜��ǂݍ��݁A�`�悷��
	 * @param fileName   �摜�̃p�X
	 * @param backGround �w�i���ǂ���
	 */
	inline void CreateImage(const char* fileName,bool backGround = false)
	{
		Init();
		m_pSprite = Add_Component<Sprite>();

		if (backGround){
			//- �w�i�Ȃ�A��ʃT�C�Y�����ς��ɕ\������
			m_pSprite->Init(
				{ SPRITE_CENTER_POS_X(SCREEN_WIDTH),SPRITE_CENTER_POS_Y(SCREEN_HEIGHT) },
				{ SCREEN_WIDTH,SCREEN_HEIGHT},fileName);
		}
		else {
			m_pSprite->Init(
			{ SPRITE_CENTER_POS_X(1.0f),SPRITE_CENTER_POS_Y(1.0f) },
			{ 1.0f,1.0f }, fileName);	
		}
	}

	/**
	 * @brief �X�v���C�g�ɒ��ڍ��W���Z�b�g����
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)
	{	m_pSprite->Set_Pos(pos);	}

	/**
	 * @brief �X�v���C�g�ɒ��ڃT�C�Y���Z�b�g����
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size)
	{	m_pSprite->Set_Size(size);	}

	/**
	 * @brief �X�v���C�g�ɒ��ډ�]���Z�b�g����
	 * @param rot
	 */
	inline void Set_RotZ(const float& rot)
	{	m_pSprite->Set_Rot(rot);	}
	
	/**
	 * @brief �T�E���h�̒ǉ�
	 * @param fileName �T�E���h�̃p�X
	 * @param keyname �T�E���h�̃L�[��
	 */
	inline void Add_Sound(const char* fileName,const std::string& keyname)
	{
		m_SoundList.insert(std::make_pair(keyname, Add_Component<Sound>()));
		m_SoundList[keyname]->Load(fileName);
	}

	/**
	 * @brief �T�E���h�̍Đ�
	 * @param keyname �T�E���h�̃L�[��
	 * @param loop ���[�v�Đ����邩�ǂ���
	 */
	inline void Play_Sound(const std::string& keyname,const bool& loop = false)
	{	m_SoundList[keyname]->Play(loop);	}

private:
	
	Sprite* m_pSprite = nullptr;
	std::unordered_map<std::string,Sound*> m_SoundList = {};

};

#endif // !__IMAGE_DRAWER_H__


