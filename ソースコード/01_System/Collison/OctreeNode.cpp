#include "OctreeNode.h" 

CollisionController::AABB OctreeNode::m_bound = CollisionController::AABB();
OctreeNode* OctreeNode::m_Children[8];
std::vector<OctreeNode::INSERT_DATA> OctreeNode::m_Colliders;

void OctreeNode::Update(float deltatime)
{
	//- ノード内のオブジェクト当たり判定
	for (int i = 0; i < m_Colliders.size(); i++)
	{
		for (int j = i + 1; j < m_Colliders.size(); j++)
		{
			CollisionController::AABB aabb1 
				= CollisionController::ChangeAABB(m_Colliders[i].collider);
			CollisionController::AABB aabb2 
				= CollisionController::ChangeAABB(m_Colliders[j].collider);

			if (CollisionController::AABBWithAABB(aabb1, aabb2))
			{
				Message::DebugLog("Hit");
			}
		}
	}

	//- 子ノードの更新
	for (int i = 0; i < 8; i++)
	{
		if (m_Children[i] != nullptr)
		{
			m_Children[i]->Update(deltatime);
		}
	}
}
