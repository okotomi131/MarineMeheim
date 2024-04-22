/*********************************************************************
 * @file   Obstacle.h
 * @brief  障害物を汎用的に作成する
 *********************************************************************/
#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__
 /*
 ==================================================

 インクルード

 ==================================================
 */
#include "../Object.h"

class Obstacle : public Object
{
public:
	enum class E_OBJECT_TYPE
	{
		Rock,
		Coral,

		Max
	};

	/**
	 * @brief ファイル読み込み
	 * @param fileName 読み込むファイル名
	 */
	void Load(const char* fileName);

	/**
	 * @brief 初期化処理
	 */
	void Init() override;

	/**
	 * @brief 更新処理
	 * @param deltatime
	 */
	void Update(float deltatime) override;

	/**
	 * @brief コライダーのサイズを設定する
	 * @param size
	 */
	void Set_CollSize(float size = 2.5f);
private:
};

#endif // !__OBSTACLE_H__


