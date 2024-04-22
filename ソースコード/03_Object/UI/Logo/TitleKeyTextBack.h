#ifndef __TITLE_KEY_BACK_TEXT_H__
#define __TITLE_KEY_BACK_TEXT_H__

#include "../../Object.h"
#include "../../../01_System/Window/WinStartUp.h"
#include "../../../02_Component/Sprite/Sprite.h"
#include "../../../02_Component/Shader/Shader.h"

class TitleKeyTextBack : public Object
{
public:
	void Init()override;
	void Update(float deltatime) override;
private:
	float m_time = 0.0f;
};

#endif // !__TITLE_KEY_TEXT_H__


