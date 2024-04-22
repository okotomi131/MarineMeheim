/*********************************************************************
 * @file   Sound.h
 * @brief  サウンド処理
 *********************************************************************/

#ifndef __SOUND_H__
#define __SOUND_H__

/*
 ==================================================

 インクルード

 ==================================================
 */
#include <xaudio2.h>
#include "../Component.h"

class Sound : public Component
{
public:
	using Component::Component;
	
	/**
	 * @brief 初期化処理
	 */
	static void InitMaster();

	/**
	 * @brief 終了処理
	 */
	static void UninitMaster();

	/**
	 * @brief 更新処理
	 */
	static void UpdateMaster(float deltatime);

	/**
	 * @brief サウンドの停止
	 */
	void Stop();

	/**
	 * @brief サウンドデータの読み込み 
	 * @param FileName
	 */
	void Load(const char* FileName);

	/**
	 * @brief サウンドの再生
	 * @param Loop ループ再生するか
	 */
	void Play(bool Loop = false);

	/**
	 * @brief 音量の設定
	 * @param volume 音量(0.0f ～ 1.0f)
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


