#ifndef __OCTREE_NODE_H__
#define __OCTREE_NODE_H__
#include "CollisionController.h"
class OctreeNode
{
public:
	struct INSERT_DATA
	{
		class Collider* collider;
		class Object*   object;
	};

	inline static void Init(const CollisionController::AABB bound) 
	{
		CollisionController::AABB worldBounds;
		worldBounds.min = DirectX::XMFLOAT3(-200.0f, -10.0f, -200.0f);
		worldBounds.max = DirectX::XMFLOAT3(200.0f, 400.0f, 200.0f);
		
		//m_bound = bound;
		m_bound = worldBounds;
		for (int i = 0; i < 8; i++){m_Children[i] = nullptr;}
	};

	inline static void Uninit() {
		for (int i = 0; i < 8; i++) {
			Delete_and_Null<>(m_Children[i], "child");
		}
	}

	static void Update(float deltatime);

	/**
	 * @brief �I�u�W�F�N�g�����E�Ɋ܂܂�Ă��邩
	 * @param data �I�u�W�F�N�g�ƃR���C�_�[
	 */
	template<typename T>
	void Insert(T* object, class Collider* collider) 
	{
		CollisionController::AABB coll = CollisionController::ChangeAABB(collider);
		bool bInside = CheckInSide(coll, m_bound);
		if (!bInside) { return; }

		for (int i = 0; i++; i < 8)
		{
			if (m_Children[i])
			{
				CollisionController::AABB child = m_Children[i]->m_bound;
				bool bInChild = CheckInSide(coll, child);
				if (!bInChild) { return; }
			}
			else { return; }
		}

		T* baseObj = dynamic_cast<T*>(object);
		if (baseObj != nullptr) 
		{
			INSERT_DATA data;
			data.collider = collider;
			data.object = object;
			m_Colliders.push_back(data);
		}
	}

	/**
	 * @brief ������ɑ��݂��Ă��邩���`�F�b�N����
	 * @param in �R���C�_�[�y�ы��E��AABB
	 * @param out ���E��AABB 
	 * @return 
	 */
	inline bool CheckInSide(const CollisionController::AABB& in, const CollisionController::AABB out)
	{
		//�O����AABB�̒��ɓ�����AABB���܂܂�Ă��邩
		if (in.min.x > out.max.x || in.max.x < out.min.x ||
			in.min.y > out.max.y || in.max.y < out.min.y ||
			in.min.z > out.max.z || in.max.z < out.min.z)
		{	return false;	}
		return true;
	}


private	:
	static CollisionController::AABB m_bound;//���E
	static OctreeNode* m_Children[8];		  //�q�m�[�h
	static std::vector<INSERT_DATA> m_Colliders;//�I�u�W�F�N�g�ƃR���C�_�[

};

#endif // !__OCTREE_NODE_H__


