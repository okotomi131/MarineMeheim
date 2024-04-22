/*********************************************************************
 * @file   Sprite.h
 * @brief  スプライト描画
 *********************************************************************/
#ifndef __SPRITE_H__
#define __SPRITE_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */

#include "../Component.h"

/*
==================================================

マクロ・定数定義

==================================================
*/ 
const static int MAX_FILENAME(128);


class Sprite : public Component
{
public:
	using Component::Component;
	
	/**
	 * @brief 初期化処理
	 * @param pos 生成座標
	 * @param size 生成サイズ
	 * @param fileName ファイル名
	 */
	void Init(DirectX::XMFLOAT2 pos, DirectX::XMFLOAT2 size, const char* fileName);

	/**
	 * @brief 終了処理
	 */
	void Uninit() override;

	/**
	 * @brief 更新処理
	 * @param deltaTime
	 */
	void Update(float deltaTime) override;

	/**
	 * @brief 描画処理
	 */
	void Draw()   override;


	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief 座標設定
	 * @param pos
	 */
	inline void Set_Pos(const DirectX::XMFLOAT2& pos)	{ m_pos  = pos; }

	/**
	 * @brief サイズ設定
	 * @param size
	 */
	inline void Set_Size(const DirectX::XMFLOAT2& size) { m_size = size; }

	/**
	 * @brief 回転設定
	 * @param rot
	 */
	inline void Set_Rot(const float& rot) { m_rot  = rot; };

	/**
	 * @brief UV分割数設定
	 * @param x 横の分割数
	 * @param y 縦の分割数
	 */
	inline void Set_UvDivision(const int& x, int& y) { m_uvX  = x;  m_uvY = y; };

	/**
	 * @brief アニメーション時間設定
	 * @param
	 */
	inline void Set_Time(const float& time)	{ m_animeTime = time; };

	/**
	 * @brief　カラーの設定
	 * @param
	 */
	inline void Set_Color(const DirectX::XMFLOAT4& color) { m_material.diffuse = color; };

	/**
	 * @brief マテリアルの設定
	 * @param 
	 */
	inline void Set_Material(const MATERIAL& material)	{ m_material = material; };

	/**
	 * @brief マテリアルの設定
	 * @param
	 */
	inline void Set_bufferObject(const CONSTANT_BUFFE_OBJECT& object)	{m_bufferObject = object; };
	

	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief 座標取得
	 * @return 
	 */
	DirectX::XMFLOAT2 Get_Pos()  const { return m_pos; }

	/**
	 * @brief サイズ取得
	 * @return 
	 */
	DirectX::XMFLOAT2 Get_Size() const { return m_size; }

	/**
	 * @brief ファイル名取得
	 * @return 
	 */
	const char* Get_FileName() const { return m_fileName; }
private:

	/**
	* @brief 頂点回転
	* @param vtxNum 頂点数
	* @param pos 頂点座標
	* @param vtx 頂点データ
	*/
	void VertexRot(const int& vtxNum, DirectX::XMFLOAT2 pos[4],VERTEX3D vtx[4]);

	ID3D11Buffer*				m_pVertexBuffer = {};
	ID3D11ShaderResourceView*	m_pTexture = {};
	MATERIAL m_material = {};
	CONSTANT_BUFFE_OBJECT m_bufferObject = {};

	DirectX::XMFLOAT2 m_pos;
	DirectX::XMFLOAT2 m_size;
	float m_rot = 0.0f;

	int		m_animeCnt = 0;
	float	m_animeTime = -1.0f;
	int		m_uvX = 1;
	int		m_uvY = 1;
	float   m_curTime = 1.0f;
	const char* m_fileName = nullptr;

};


#endif // !__SPRITE_H__

