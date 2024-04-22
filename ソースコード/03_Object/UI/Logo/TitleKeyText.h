/*********************************************************************
 * @file   TitleKeyText.h
 * @brief  
 *********************************************************************/
#ifndef __TITLE_KEY_TEXT_H__
#define __TITLE_KEY_TEXT_H__
#include "../../Object.h"
class TitleKeyText :public Object
{
public:
	void Init()override;
	void Update(float deltatime)override;
};

#endif // !__TITLE_KEY_TEXT_H__


