#ifndef __BGM_H__
#define __BGM_H__
#include "../Object.h"
#include "../../02_Component/Sound/Sound.h"
class BGM : public Object
{
public:

	/**
	 * @brief 終了処理
	 */
	void Uninit()
	{
		for (auto& sound : m_soundList)
		{ sound.second->Stop();	}
		m_soundList.clear();
	}

	/**
	 * @brief 登録処理
	 * @param name キーの名前
	 * @param path ファイルのパス
	 */
	inline void Register(const std::string name, const char* path) 
	{ 
		m_soundList[name] = Add_Component<Sound>();
		m_soundList[name]->Load(path); 
	}

	/**
	 * @brief 再生
	 * @param name キーの名前
	 */
	void Play(const std::string name) { m_soundList[name]->Play(true); }
private:
	std::map<std::string, Sound*> m_soundList;
};

#endif // !__BGM_H__

