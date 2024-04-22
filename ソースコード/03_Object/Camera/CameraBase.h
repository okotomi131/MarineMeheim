/*********************************************************************
 * @file   CameraBase.h
 * @brief  カメラベース
 *********************************************************************/
#ifndef __CAMERA_BASE_H_
#define __CAMERA_BASE_H_

/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"

class CameraBase : public Object
{
public:
	/**
	 * @brief 初期化処理
	 */
	virtual void Init() override;
	
	/**
	 * @brief 描画処理
	 */
	virtual void Draw() override;

	/*
	==================================================

	ゲッター・セッター

	==================================================
	*/

	/**
	 * @brief ビュー行列取得
	 */
	DirectX::XMFLOAT4X4 Get_ViewMatrix() { return m_viewMatrix; };

	/**
	 * @throw ターゲット座標取得
	 */
	void Set_TargetObj(Object* obj) { m_pTargetObj = obj; };

protected:
	DirectX::XMFLOAT3	m_target = {};
	DirectX::XMFLOAT3	m_up = {};
	Object* m_pTargetObj = {};
private:
	DirectX::XMFLOAT4X4	m_viewMatrix = {};
};


#endif // !__CAMERA_BASE_H_
