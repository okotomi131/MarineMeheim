/*********************************************************************
 * @file   CollisionController.h
 * @brief  当たり判定の管理を行う
 *********************************************************************/

#ifndef __COLLISON_CONTROLLER_H__
#define __COLLISON_CONTROLLER_H__


/*
===================================================================

インクルード

===================================================================
*/
#include "../../01_System/DirectX/DirectXRenderer.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../03_Object/Collider/Collider.h"

/*
===================================================================

定数・マクロ定義

===================================================================
*/
#define EPSILON (0.00001f) //誤差

class CollisionController
{
public:
	/*
	===================================================================

	列挙型

	===================================================================
	*/
	enum class E_HIT_DIRECTION
	{
		None,
		Up,		//上
		Down,	//下
		Left,	//左
		Right,	//右
		Front,	//前
		Back,	//後
	};

	/*
	===================================================================

	構造体

	===================================================================
	*/

	struct AABB
	{
		DirectX::XMFLOAT3 min;
		DirectX::XMFLOAT3 max;
	};

	struct Ray
	{
		DirectX::XMFLOAT3 origin;
		DirectX::XMFLOAT3 dir;
	};

	/**
	 * @brief 初期化処理
	 */
	static void Init();

	/**
	 * @brief 更新処理
	 * @param deltatime デルタタイム
	 */
	static void Update(float deltatime);

	/**
	 * @brief AABB同士の当たり判定
	 * 
	 * @param aabb1 AABB構造体
	 * @param aabb2 AABB構造体
	 * @return 当たっていたらtrueが返却
	 */
	inline static bool AABBWithAABB(const AABB& aabb1, const AABB& aabb2)
	{
		//- 重なっていない場合
		if (aabb1.min.x > aabb2.max.x ||
			aabb1.max.x < aabb2.min.x ||
			aabb1.min.y > aabb2.max.y ||
			aabb1.max.y < aabb2.min.y ||
			aabb1.min.z > aabb2.max.z ||
			aabb1.max.z < aabb2.min.z)
		{
			return false;
		}
		return true;
	}

	/**
	 * @brief AABBとレイの当たり判定
	 * @param aabb AABB構造体
	 * @param ray Ray構造体
	 * @return 当たっていたらtrueが返却
	 */
	static bool AABBwithRay(const AABB& aabb, const Ray& ray);

	/**
	 * @brief AABB構造体に変換する
	 * Object内にある最大値と最小値をAABB構造体に設定する
	 * @param obj 変換したいObject型
	 * @return AABB構造体
	 */
	inline static AABB ChangeAABB(const Object* obj)
	{
		AABB aabb;
		aabb.min = obj->Get_MinPoint();
		aabb.max = obj->Get_MaxPoint();
		return aabb;
	}

	/**
	 * @brief AABB構造体に変換する
	 * Collider内にある最大値と最小値をAABB構造体に設定する
	 * @param obj 変換したいCollider型
	 * @return AABB構造体
	 */
	inline static AABB ChangeAABB(const Collider* obj)
	{
		AABB aabb;
		aabb.min = obj->Get_wMinPoint();//親のワールド座標に変換済の最小座標
		aabb.max = obj->Get_wMaxPoint();//親のワールド座標に変換済の最大座標
		return aabb;
	}

	/**
	 * @brief Ray構造体に変換する
	 * Object内にある座標と正面ベクトルをRay構造体に設定する
	 * @param obj 変換したいObject型
	 * @return Ray構造体
	 */
	inline static Ray ChangeRay(const Object* obj)
	{
		Ray ray;
		ray.origin = obj->Get_Pos();
		DirectX::XMFLOAT3 forward;
		DirectX::XMStoreFloat3(&forward, obj->Get_vForward());
		forward.y = 0.0f;
		ray.dir = forward;
		return ray;
	}

	/**
	 * @brief カーソル座標を3D空間上に変換する
	 * @param pos カーソル座標
	 * @return 3D空間上の座標
	 */
	inline static DirectX::XMFLOAT3 CreateCursor3D(DirectX::XMFLOAT2 pos)
	{
		DirectX::XMMATRIX Identity = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX InvMat = DirectX::XMMatrixInverse(nullptr, Identity);
		RECT rect = {};
		GetClientRect(GET_WIN.Get_WinhWnd(), &rect);
		/*
		クライアント座標：左上が(0,0)、右下が(W,H)の座標、Y軸は正方向が下
		ワールド座標　　：左上が(-1,1)、右下が(1,-1)の座標、Y軸は正方向が上
		その為、0～1の範囲に変換後、-1～1の範囲に変換する
		(pos / RL)：0～1の範囲に変換※Y軸は正方向を3Dに合わせる為、-を先頭に
		* 2.0f - 1.0f：-1～1の範囲に変換
		*/
		DirectX::XMFLOAT3 wPos = {};
		wPos.x = (pos.x / static_cast<float>(rect.right))   * 2.0f - 1.0f;
		wPos.y = -(pos.y / static_cast<float>(rect.bottom)) * 2.0f + 1.0f;
		wPos.z = 0.0f;
		return wPos;
	}

	/**
	 * @brief AABBとカーソルの当たり判定
	 * @param aabb AABB構造体
	 * @param pos ワールド座標に変換済のカーソル座標
	 * @return 当たっていればtrue
	 */
	inline static bool AABBwithOverlapCursol(const AABB& aabb, const DirectX::XMFLOAT3& pos)
	{
		

		if (0.0f > pos.x ||0.0f > pos.y ||
			SCREEN_WIDTH < pos.x ||SCREEN_HEIGHT < pos.y )
		{	return false;	}

		if (aabb.min.x > pos.x ||
			aabb.max.x < pos.x ||
			aabb.min.y > pos.y ||
			aabb.max.y < pos.y)
		{
			return false;
		}
		return true;
	}

private:

	/*
	===================================================================

	弾関連

	===================================================================
	*/

	/**
	 * @brief 弾の種類によって処理を分ける
	 * @param bullet
	 * @param scene
	 * @param player
	 */
	static bool SearchBulletType();

	/**
	 * @brief 敵のタグによって処理を分ける
	 * @param enemy
	 * @param bullet
	 * @param scene
	 */
	static void SearchEnemyTag();

	/**
	 * @brief 弾と敵の当たり判定
	 * @param enemy
	 * @param bullet
	 * @param scene
	 * @return 当たったらtrue
	 */
	static bool CheckHitEnemytoBullet();

	/**
	 * @brief 障害物と弾が当たっているか確認する
	 * @param obj シーン内にある障害物の配列
	 */
	static void CheckHitObstacletoBullet(std::vector<class Obstacle*>& obj);

	/*
	===================================================================

	アイテム関連

	===================================================================
	*/

	/**
	 * @brief アイテムとプレイヤーが当たっているかを確認
	 * @param items シーン内にあるアイテムの配列
	 */
	static void CheckHitItemtoPlayer(std::vector<class ItemBase*>& items);

	/**
	 * @brief アイテムのタグによって処理を分ける
	 */
	static void SearchItemTag();

	/*
	===================================================================

	障害物

	===================================================================
	*/

	/**
	 * @brief 障害物とプレイヤーの当たり判定
	 * @param obj
	 * @param player
	 */
	static void CheckHitObstacletoPlayer(std::vector<class Obstacle*>& obj);

	/**
	 * @brief 地面とプレイヤーが当たっているか確認する
	 */
	static void CheckHitFieldtoPlayer();


	/*
	===================================================================

	敵

	===================================================================
	*/

	/**
	 * @brief 敵のタグがスポナーの場合の処理
	 * @param enemy
	 * @param bullet
	 * @param scene
	 */
	static void HitProcessSpawner();

	/*
	===================================================================

	その他

	===================================================================
	*/

	/**
	 * @brief オブジェクト間の重なりを解消する
	 * @param ObjDynamic 動的なオブジェクト
	 * @param ObjStatic　静的なオブジェクト
	 */
	static void ResolveOverlap(Object* ObjDynamic, Object* ObjStatic);

	/**
	 * @brief エフェクトを生成する
	 * @param scene
	 * @param bullet
	 * @param size
	 */
	static void SpawnEffect(DirectX::XMFLOAT2 size = { 4.0f,4.0f });



	static float m_groundHeight;	  //地面の高さ
	static class SceneBase* m_pScene; //シーン
	static class Player*	m_pPlayer;//プレイヤー
	static class Bullet*	m_pBullet;//弾
	static class EnemyBase* m_pEnemy; //敵
	static class ItemBase*  m_pItem;  //アイテム
};

#endif // !__COLLISON_CONTROLLER_H__

