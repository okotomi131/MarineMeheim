/*
	TextDraw.cpp
	テキスト描画クラス
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

	//- セッター
	static void Set_FontColor(const D2D1_COLOR_F color);
	static void Set_FontSize(const float size);
	static void Set_FontType(const int type);
	//- ゲッター
	static const float Get_FontSize() { return m_fontData.size; }
	
private:
	static DirectXWriteFont* m_fontWrite;
	static FontData			 m_fontData;
};


#endif // !__TEXT_DRAW_H__

