/*********************************************************************
 * @file   Sound.cpp
 * @brief  �T�E���h�̏���
 *********************************************************************/

/*
==================================================

�C���N���[�h

==================================================
*/
#include "Sound.h"
#include "../../01_System/main.h"

IXAudio2* Sound::m_Xaudio = nullptr;
IXAudio2MasteringVoice* Sound::m_MasteringVoice = nullptr;
float Sound::m_DeltaTime = 0.0f;

void Sound::InitMaster()
{	
	//- COM������ (WinMain�Ŋ������Ă���̂��O��A�����ł͌Ă΂Ȃ�)
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//- XAudio����
	XAudio2Create(&m_Xaudio, 0);

	//- �}�X�^�����O�{�C�X����
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}

void Sound::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	Release_and_Null(m_Xaudio, "m_Xaudio");
	CoUninitialize();
}

void Sound::UpdateMaster(float deltatime)
{
	m_DeltaTime = deltatime;
}

void Sound::Stop()
{
	m_SourceVoice->Stop();
	m_SourceVoice->DestroyVoice();
	delete[] m_SoundData;
}

void Sound::Load(const char* FileName)
{
	//- �T�E���h�f�[�^�Ǎ�
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;

		hmmio = mmioOpenA((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);

		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;

		mmioClose(hmmio, 0);
	}

	//- �T�E���h�\�[�X����
	m_Xaudio->CreateSourceVoice(&m_SourceVoice, &wfx);
	assert(m_SourceVoice);
}

void Sound::Play(bool Loop)
{
	auto now = std::chrono::steady_clock::now();

	//- ��莞�Ԍo�߂��Ă��Ȃ��ꍇ�͍Đ����Ȃ�
	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_LastPlayTime).count() 
		< SE_PLAY_INTERVAL_MILLI_SECOND)
	{	return;	}

	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	//- �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	//- ���[�v�ݒ�
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	//- �Đ�
	m_SourceVoice->Start();

	// �Ō�̍Đ����Ԃ��X�V
	m_LastPlayTime = now;
}
