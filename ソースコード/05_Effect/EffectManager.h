/*********************************************************************
 * @file   EffectManager.h
 * @brief  �G�t�F�N�V�A���g�p�����G�t�F�N�g�̎���
 * �`����W�̕ϊ�����肭�����Ȃ����߁A��U�ۗ�
 *********************************************************************/

//#ifndef __EFFECT_MANAGER_H__
//#define __EFFECT_MANAGER_H__
//
//#include <Effekseer.h>
//#include <EffekseerRendererDX11.h>
//#include "../01_System/DirectX/DirectXRenderer.h"
//
//class EffectManager
//{
//public:
//	static void Init();
//	static void Uninit();
//	static void Draw(float deltatime);
//
//	static inline void Set_Camera(class CameraPlayer* camera) { m_pCamera = camera; };
//	static inline void Set_Pos(DirectX::XMFLOAT3 pos) { m_pos = pos; };
//	static inline void Set_Porj(Effekseer::Matrix44 proj) { m_Proj = proj; };
//	static inline void Set_matCamera(Effekseer::Matrix44 camera) { m_matCamera = camera; };
//private:
//	static inline const int		CREATE_EFFECT_NUM	= 8000;	//�ő吶����
//	static inline const float	VIEW_ANGLE			= 90.0f;//����p
//
//	//- �J�������
//	static class CameraPlayer* m_pCamera;
//	static Effekseer::Matrix44 m_Proj;
//	static Effekseer::Matrix44 m_matCamera;
//
//
//	static DirectX::XMFLOAT3 m_pos;
//
//	//- �G�t�F�N�V�A
//	static Effekseer::ManagerRef				m_offokseerMng;
//	static EffekseerRendererDX11::RendererRef   m_efkRenderer;
//	static Effekseer::EffectRef				m_effect;
//	static Effekseer::Handle				m_efkHndle;
//
//};
//
//#endif // !__EFFECT_H__
