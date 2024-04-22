/*
	TextDraw.cpp
	�e�L�X�g�`��N���X
*/
#ifndef __TEXT_DRAW_H__
#define __TEXT_DRAW_H__

#include "DirectXWriteFont.h"

class TextDraw 
{
public:
	static void Init();
	static void Uninit();

	static void DrawMessage(
		std::string msg, DirectX::XMFLOAT2 pos);

	//- �Z�b�^�[
	static void Set_FontColor(const D2D1_COLOR_F color);
	static void Set_FontSize(const float size);
	static void Set_FontType(const int type);
	//- �Q�b�^�[
	static const float Get_FontSize() { return m_fontData.size; }
	
private:
	static DirectXWriteFont* m_fontWrite;
	static FontData			 m_fontData;
};


#endif // !__TEXT_DRAW_H__

