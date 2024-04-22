/*
	TextDraw.cpp
	テキスト描画クラス
*/
#include "TextDraw.h"

#include "../main.h"
#include "../DirectX/DirectXRenderer.h"

FontData TextDraw::m_fontData = {};
DirectXWriteFont* TextDraw::m_fontWrite = {};

void TextDraw::Init()
{
	m_fontWrite = new DirectXWriteFont(&m_fontData);
	m_fontWrite->Init(DirectXRenderer::Get_SwapChain());

	m_fontData.size = 60;
	m_fontData.weight = DWRITE_FONT_WEIGHT_ULTRA_BLACK;
	m_fontData.color = D2D1::ColorF(D2D1::ColorF::Red);
	m_fontData.wName = m_fontWrite->Get_FontName(1);
	m_fontWrite->Set_Font(m_fontData);
}

void TextDraw::Uninit()
{
	delete m_fontWrite;
	m_fontWrite = nullptr;
}

void TextDraw::DrawMessage(std::string msg, DirectX::XMFLOAT2 pos)
{
	m_fontWrite->Draw_String(msg, pos, D2D1_DRAW_TEXT_OPTIONS_NONE);
}

void TextDraw::Set_FontColor(D2D1_COLOR_F color)
{
	m_fontData.color = color;
	m_fontWrite->Set_Font(m_fontData);
}

void TextDraw::Set_FontSize(float size)
{
	m_fontData.size = size;
	m_fontWrite->Set_Font(m_fontData);
}

void TextDraw::Set_FontType(const int type)
{
	m_fontData.wName = m_fontWrite->Get_FontName(type);
	m_fontWrite->Set_Font(m_fontData);
}
