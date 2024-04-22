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
//	//- マネージャー
//	m_offokseerMng = Effekseer::Manager::Create(CREATE_EFFECT_NUM);
//	
//	
//
//	//- レンダラー
//	auto graphicsDevice =
//		EffekseerRendererDX11::CreateGraphicsDevice(
//			DirectXRenderer::Get_Device(), DirectXRenderer::Get_DeviceContext());
//	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(
//		graphicsDevice, CREATE_EFFECT_NUM);
//
//	//- エフェクシアの各機能の設定
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
//	//- デフォルトエフェクトの読み込み
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
//	//- Nullチェック
//	if(!m_pCamera) return;
//
//	//- ビュワー位置設定
//	auto viewerPos = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);
//		//m_pCamera->Get_Pos().x,
//		//m_pCamera->Get_Pos().y,
//		//m_pCamera->Get_Pos().z);
//
//	//- プロジェクション行列設定
//	Effekseer::Matrix44 projectionMatrix;
//	projectionMatrix.PerspectiveFovRH(
//		DirectX::XMConvertToRadians(VIEW_ANGLE),//視野角
//		(float)SCREEN_WIDTH / SCREEN_HEIGHT,	//アスペクト比
//		1.0f,	//ニアクリップ(近すぎるものは描画しない)
//		500.0f);//ファークリップ(遠すぎるものは描画しない)
//
//	//- カメラ行列設定
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
//	//- レイヤー設定
//	Effekseer::Manager::LayerParameter layerParameter;
//	layerParameter.ViewerPosition = viewerPos;
//	m_offokseerMng->SetLayerParameter(0, layerParameter);
//
//	//- 更新
//	Effekseer::Manager::UpdateParameter updateParameter;
//	m_offokseerMng->Update(updateParameter);
//	static float time = 0.0f;
//
//	m_efkRenderer->SetTime(time);
//	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
//	m_efkRenderer->SetCameraMatrix(cameraMatrix);
//	m_efkRenderer->BeginRendering();
//
//	//- エフェクト描画
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
