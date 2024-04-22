//#include "EffectManager.h"
//#include "../01_System/Window/WinStartUp.h"
//#include "../03_Object/Camera/CameraPlayer.h"
//
//CameraPlayer* EffectManager::m_pCamera;
//DirectX::XMFLOAT3 EffectManager::m_pos;
//
//Effekseer::ManagerRef				EffectManager::m_offokseerMng;
//EffekseerRendererDX11::RendererRef  EffectManager::m_efkRenderer;
//Effekseer::Handle					EffectManager::m_efkHndle;
//Effekseer::EffectRef				EffectManager::m_effect;
//
//void EffectManager::Init()
//{
//	//- �}�l�[�W���[
//	m_offokseerMng = Effekseer::Manager::Create(CREATE_EFFECT_NUM);
//	
//	
//
//	//- �����_���[
//	auto graphicsDevice =
//		EffekseerRendererDX11::CreateGraphicsDevice(
//			DirectXRenderer::Get_Device(), DirectXRenderer::Get_DeviceContext());
//	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(
//		graphicsDevice, CREATE_EFFECT_NUM);
//
//	//- �G�t�F�N�V�A�̊e�@�\�̐ݒ�
//	m_offokseerMng->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
//	m_offokseerMng->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
//	m_offokseerMng->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
//	m_offokseerMng->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
//	m_offokseerMng->SetModelRenderer(m_efkRenderer->CreateModelRenderer());
//
//	m_offokseerMng->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
//	m_offokseerMng->SetModelLoader(m_efkRenderer->CreateModelLoader());
//	m_offokseerMng->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
//	m_offokseerMng->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
//	
//	//- �f�t�H���g�G�t�F�N�g�̓ǂݍ���
//	m_effect  = Effekseer::Effect::Create(m_offokseerMng, u"Assets/Effect/Effect_Hit.efkefc");
//}
//
//void EffectManager::Uninit()
//{
//	m_effect.Reset();
//	m_efkRenderer.Reset();
//	m_offokseerMng.Reset();
//}
//
//void EffectManager::Draw(float deltatime)
//{
//	//- Null�`�F�b�N
//	if(!m_pCamera) return;
//
//	//- �r�����[�ʒu�ݒ�
//	auto viewerPos = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);
//		//m_pCamera->Get_Pos().x,
//		//m_pCamera->Get_Pos().y,
//		//m_pCamera->Get_Pos().z);
//
//	//- �v���W�F�N�V�����s��ݒ�
//	Effekseer::Matrix44 projectionMatrix;
//	projectionMatrix.PerspectiveFovRH(
//		DirectX::XMConvertToRadians(VIEW_ANGLE),//����p
//		(float)SCREEN_WIDTH / SCREEN_HEIGHT,	//�A�X�y�N�g��
//		1.0f,	//�j�A�N���b�v(�߂�������͕̂`�悵�Ȃ�)
//		500.0f);//�t�@�[�N���b�v(����������͕̂`�悵�Ȃ�)
//
//	//- �J�����s��ݒ�
//	Effekseer::Matrix44 cameraMatrix;
//	DirectX::XMFLOAT3 lookPos = m_pCamera->Get_LookPoint();
//	DirectX::XMFLOAT3 uv;
//	DirectX::XMStoreFloat3(&uv, m_pCamera->Get_vUp());
//	cameraMatrix.LookAtRH(viewerPos,
//		Effekseer::Vector3D(
//			m_pos.x,
//			m_pos.y,
//			m_pos.z),
//		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
//		//Effekseer::Vector3D(lo
//		// okPos.x,lookPos.y,lookPos.z),
//		//Effekseer::Vector3D(uv.x,uv.y,uv.z));
//
//	//- ���C���[�ݒ�
//	Effekseer::Manager::LayerParameter layerParameter;
//	layerParameter.ViewerPosition = viewerPos;
//	m_offokseerMng->SetLayerParameter(0, layerParameter);
//
//	//- �X�V
//	Effekseer::Manager::UpdateParameter updateParameter;
//	m_offokseerMng->Update(updateParameter);
//	static float time = 0.0f;
//
//	m_efkRenderer->SetTime(time);
//	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
//	m_efkRenderer->SetCameraMatrix(cameraMatrix);
//	m_efkRenderer->BeginRendering();
//
//	//- �G�t�F�N�g�`��
//	Effekseer::Manager::DrawParameter drawParameter;
//	drawParameter.ZNear = 0.0f;
//	drawParameter.ZFar = 1.0f;
//	drawParameter.ViewProjectionMatrix =
//		m_efkRenderer->GetCameraProjectionMatrix();
//	m_offokseerMng->Draw(drawParameter);
//	m_efkRenderer->EndRendering();
//
//	time++;
//
//	m_efkHndle = m_offokseerMng->Play(m_effect,
//		m_pos.x,
//		m_pos.y,
//		m_pos.z);
//	m_offokseerMng->AddLocation(m_efkHndle, Effekseer::Vector3D(m_pos.x,
//		m_pos.y,
//		m_pos.z));
//
//}
//
