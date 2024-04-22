/*********************************************************************
 * @file   Collider.h
 * @brief  コライダー
 *********************************************************************/
#ifndef __COLLIDER_H__
#define __COLLIDER_H__
/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"

class Collider: public Object
{
public:
	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief 最小座標を取得
	 * @return 
	 */
	DirectX::XMFLOAT3 const Get_wMinPoint() const;

	/**
	 * @brief 最大座標を取得
	 * @return 
	 */
	DirectX::XMFLOAT3 const Get_wMaxPoint() const;

	/**
	 * @brief タグを取得
	 * @return 
	 */
	inline std::string const Get_Tag() const { return m_tag; }

	/*
	==================================================

	セッター

	==================================================
	*/

	/**
	 * @brief タグ名を設定
	 * @param tag
	 */
	inline void Set_Tag(std::string tag) { m_tag = tag; }

	/**
	 * @brief ワールド座標基準でサイズを設定
	 * @param size
	 */
	void Set_wSize(const DirectX::XMFLOAT3& size);

	/**
	 * @brief ワールド座標を設定
	 * @param matrix 
	 */
	inline void Set_WorldMatrix(const DirectX::XMMATRIX& matrix) { m_mWorld = matrix; }
private:

	std::string m_tag = "None";	//タグ
	DirectX::XMMATRIX m_mWorld;

	ID3D11Buffer* m_pVertexBuffer = {};
	ID3D11Buffer* m_pIndexBuffer = {};

};

#endif // !__COLLIDER_H__

