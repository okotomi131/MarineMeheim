/*********************************************************************
 * @file   Figure.h
 * @brief  モデルのみを表示する
 *********************************************************************/
#ifndef __FIGURE_H__
#define __FIGURE_H__

/*
==================================================

インクルード

==================================================
*/
#include "../Object.h"

class Figure : public Object
{
public:
	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief モデルの読み込み
	 * @param filename
	 */
	void LoadModel(const char* filename);

	/**
	 * @brief 回転フラグの設定
	 * @param flag
	 */
	void Set_Rotate(bool flag) { m_bRotate = flag; }
private:
	bool m_bRotate = false;
};

#endif // !__FIGURE_H__

