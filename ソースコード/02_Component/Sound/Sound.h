/*********************************************************************
 * @file   Sound.h
 * @brief  �T�E���h����
 *********************************************************************/

#ifndef __SOUND_H__
#define __SOUND_H__

/*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include <xaudio2.h>
#include "../Component.h"

class Sound : public Component
{
public:
	using Component::Component;
	
	/**
	 * @brief ����������
	 */
	static void InitMaster();

	/**
	 * @brief �I������
	 */
	static void UninitMaster();

	/**
	 * @brief �X�V����
	 */
	static void UpdateMaster(float deltatime);

	/**
	 * @brief �T�E���h�̒�~
	 */
	void Stop();

	/**
	 * @brief �T�E���h�f�[�^�̓ǂݍ��� 
	 * @param FileName
	 */
	void Load(const char* FileName);

	/**
	 * @brief �T�E���h�̍Đ�
	 * @param Loop ���[�v�Đ����邩
	 */
	void Play(bool Loop = false);

	/**
	 * @brief ���ʂ̐ݒ�
	 * @param volume ����(0.0f �` 1.0f)
	 */
	void Set_Volume(float volume = 0.3f)
	{	m_SourceVoice->SetVolume(volume);	}


private:

	const int SE_PLAY_INTERVAL_MILLI_SECOND = 100;

	static IXAudio2* m_Xaudio;
	static IXAudio2MasteringVoice* m_MasteringVoice;
	static float m_DeltaTime;

	std::chrono::steady_clock::time_point m_LastPlayTime;
	IXAudio2SourceVoice* m_SourceVoice = {};
	BYTE* m_SoundData = {};

	int	m_Length = {};
	int	m_PlayLength = {};
};


#endif // !__SOUND_H__


