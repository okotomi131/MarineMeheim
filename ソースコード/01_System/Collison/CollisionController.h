/*********************************************************************
 * @file   CollisionController.h
 * @brief  �����蔻��̊Ǘ����s��
 *********************************************************************/

#ifndef __COLLISON_CONTROLLER_H__
#define __COLLISON_CONTROLLER_H__


/*
===================================================================

�C���N���[�h

===================================================================
*/
#include "../../01_System/DirectX/DirectXRenderer.h"
#include "../../01_System/Window/WinStartUp.h"
#include "../../03_Object/Collider/Collider.h"

/*
===================================================================

�萔�E�}�N����`

===================================================================
*/
#define EPSILON (0.00001f) //�덷

class CollisionController
{
public:
	/*
	===================================================================

	�񋓌^

	===================================================================
	*/
	enum class E_HIT_DIRECTION
	{
		None,
		Up,		//��
		Down,	//��
		Left,	//��
		Right,	//�E
		Front,	//�O
		Back,	//��
	};

	/*
	===================================================================

	�\����

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
	 * @brief ����������
	 */
	static void Init();

	/**
	 * @brief �X�V����
	 * @param deltatime �f���^�^�C��
	 */
	static void Update(float deltatime);

	/**
	 * @brief AABB���m�̓����蔻��
	 * 
	 * @param aabb1 AABB�\����
	 * @param aabb2 AABB�\����
	 * @return �������Ă�����true���ԋp
	 */
	inline static bool AABBWithAABB(const AABB& aabb1, const AABB& aabb2)
	{
		//- �d�Ȃ��Ă��Ȃ��ꍇ
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
	 * @brief AABB�ƃ��C�̓����蔻��
	 * @param aabb AABB�\����
	 * @param ray Ray�\����
	 * @return �������Ă�����true���ԋp
	 */
	static bool AABBwithRay(const AABB& aabb, const Ray& ray);

	/**
	 * @brief AABB�\���̂ɕϊ�����
	 * Object���ɂ���ő�l�ƍŏ��l��AABB�\���̂ɐݒ肷��
	 * @param obj �ϊ�������Object�^
	 * @return AABB�\����
	 */
	inline static AABB ChangeAABB(const Object* obj)
	{
		AABB aabb;
		aabb.min = obj->Get_MinPoint();
		aabb.max = obj->Get_MaxPoint();
		return aabb;
	}

	/**
	 * @brief AABB�\���̂ɕϊ�����
	 * Collider���ɂ���ő�l�ƍŏ��l��AABB�\���̂ɐݒ肷��
	 * @param obj �ϊ�������Collider�^
	 * @return AABB�\����
	 */
	inline static AABB ChangeAABB(const Collider* obj)
	{
		AABB aabb;
		aabb.min = obj->Get_wMinPoint();//�e�̃��[���h���W�ɕϊ��ς̍ŏ����W
		aabb.max = obj->Get_wMaxPoint();//�e�̃��[���h���W�ɕϊ��ς̍ő���W
		return aabb;
	}

	/**
	 * @brief Ray�\���̂ɕϊ�����
	 * Object���ɂ�����W�Ɛ��ʃx�N�g����Ray�\���̂ɐݒ肷��
	 * @param obj �ϊ�������Object�^
	 * @return Ray�\����
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
	 * @brief �J�[�\�����W��3D��ԏ�ɕϊ�����
	 * @param pos �J�[�\�����W
	 * @return 3D��ԏ�̍��W
	 */
	inline static DirectX::XMFLOAT3 CreateCursor3D(DirectX::XMFLOAT2 pos)
	{
		DirectX::XMMATRIX Identity = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX InvMat = DirectX::XMMatrixInverse(nullptr, Identity);
		RECT rect = {};
		GetClientRect(GET_WIN.Get_WinhWnd(), &rect);
		/*
		�N���C�A���g���W�F���オ(0,0)�A�E����(W,H)�̍��W�AY���͐���������
		���[���h���W�@�@�F���オ(-1,1)�A�E����(1,-1)�̍��W�AY���͐���������
		���ׁ̈A0�`1�͈̔͂ɕϊ���A-1�`1�͈̔͂ɕϊ�����
		(pos / RL)�F0�`1�͈̔͂ɕϊ���Y���͐�������3D�ɍ��킹��ׁA-��擪��
		* 2.0f - 1.0f�F-1�`1�͈̔͂ɕϊ�
		*/
		DirectX::XMFLOAT3 wPos = {};
		wPos.x = (pos.x / static_cast<float>(rect.right))   * 2.0f - 1.0f;
		wPos.y = -(pos.y / static_cast<float>(rect.bottom)) * 2.0f + 1.0f;
		wPos.z = 0.0f;
		return wPos;
	}

	/**
	 * @brief AABB�ƃJ�[�\���̓����蔻��
	 * @param aabb AABB�\����
	 * @param pos ���[���h���W�ɕϊ��ς̃J�[�\�����W
	 * @return �������Ă����true
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

	�e�֘A

	===================================================================
	*/

	/**
	 * @brief �e�̎�ނɂ���ď����𕪂���
	 * @param bullet
	 * @param scene
	 * @param player
	 */
	static bool SearchBulletType();

	/**
	 * @brief �G�̃^�O�ɂ���ď����𕪂���
	 * @param enemy
	 * @param bullet
	 * @param scene
	 */
	static void SearchEnemyTag();

	/**
	 * @brief �e�ƓG�̓����蔻��
	 * @param enemy
	 * @param bullet
	 * @param scene
	 * @return ����������true
	 */
	static bool CheckHitEnemytoBullet();

	/**
	 * @brief ��Q���ƒe���������Ă��邩�m�F����
	 * @param obj �V�[�����ɂ����Q���̔z��
	 */
	static void CheckHitObstacletoBullet(std::vector<class Obstacle*>& obj);

	/*
	===================================================================

	�A�C�e���֘A

	===================================================================
	*/

	/**
	 * @brief �A�C�e���ƃv���C���[���������Ă��邩���m�F
	 * @param items �V�[�����ɂ���A�C�e���̔z��
	 */
	static void CheckHitItemtoPlayer(std::vector<class ItemBase*>& items);

	/**
	 * @brief �A�C�e���̃^�O�ɂ���ď����𕪂���
	 */
	static void SearchItemTag();

	/*
	===================================================================

	��Q��

	===================================================================
	*/

	/**
	 * @brief ��Q���ƃv���C���[�̓����蔻��
	 * @param obj
	 * @param player
	 */
	static void CheckHitObstacletoPlayer(std::vector<class Obstacle*>& obj);

	/**
	 * @brief �n�ʂƃv���C���[���������Ă��邩�m�F����
	 */
	static void CheckHitFieldtoPlayer();


	/*
	===================================================================

	�G

	===================================================================
	*/

	/**
	 * @brief �G�̃^�O���X�|�i�[�̏ꍇ�̏���
	 * @param enemy
	 * @param bullet
	 * @param scene
	 */
	static void HitProcessSpawner();

	/*
	===================================================================

	���̑�

	===================================================================
	*/

	/**
	 * @brief �I�u�W�F�N�g�Ԃ̏d�Ȃ����������
	 * @param ObjDynamic ���I�ȃI�u�W�F�N�g
	 * @param ObjStatic�@�ÓI�ȃI�u�W�F�N�g
	 */
	static void ResolveOverlap(Object* ObjDynamic, Object* ObjStatic);

	/**
	 * @brief �G�t�F�N�g�𐶐�����
	 * @param scene
	 * @param bullet
	 * @param size
	 */
	static void SpawnEffect(DirectX::XMFLOAT2 size = { 4.0f,4.0f });



	static float m_groundHeight;	  //�n�ʂ̍���
	static class SceneBase* m_pScene; //�V�[��
	static class Player*	m_pPlayer;//�v���C���[
	static class Bullet*	m_pBullet;//�e
	static class EnemyBase* m_pEnemy; //�G
	static class ItemBase*  m_pItem;  //�A�C�e��
};

#endif // !__COLLISON_CONTROLLER_H__

