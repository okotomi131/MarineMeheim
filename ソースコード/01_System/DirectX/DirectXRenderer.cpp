/*********************************************************************
 * @file   DirectXRenderer.cpp
 * @brief  DirectXの処理
 *********************************************************************/

 /*
 ==================================================

 インクルード

 ==================================================
 */
#define _CRTDBG_MAP_ALLOC

#include "DirectXRenderer.h"
#include "../Window/WinStartUp.h"
#include <io.h>
#include <cstdlib>
#include <crtdbg.h>

D3D_FEATURE_LEVEL        DirectXRenderer::m_pFeatureLevel		= D3D_FEATURE_LEVEL_11_0;
ID3D11Device*            DirectXRenderer::m_pDevice				= {};
ID3D11DeviceContext*     DirectXRenderer::m_pDeviceContext		= {};
IDXGISwapChain*          DirectXRenderer::m_pSwapChain			= {};
ID3D11RenderTargetView*  DirectXRenderer::m_pRenderTargetView	= {};
ID3D11DepthStencilView*  DirectXRenderer::m_pDepthStencilView	= {};
ID3D11DepthStencilState* DirectXRenderer::m_pDepthStateEnable	= {};
ID3D11DepthStencilState* DirectXRenderer::m_pDepthStateDisable	= {};
ID3D11BlendState*		 DirectXRenderer::m_pBlendState			= {};
ID3D11BlendState*		 DirectXRenderer::m_pBlendStateATC		= {};
std::unordered_map<std::string, std::pair<std::type_index, ID3D11Buffer*>> DirectXRenderer::m_bufferTypeMap = {};

/*
===================================================================

DirectXの作成

===================================================================
*/

void DirectXRenderer::Init()
{
	HRESULT hr;

	//- デバイスとスワップチェインの作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width  = (UINT)SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = (UINT)SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GET_WIN.Get_WinhWnd();
	swapChainDesc.SampleDesc.Count	 = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,//0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		&m_pFeatureLevel,
		&m_pDeviceContext);

	if (FAILED(hr)) { Message::ErrorMessage("スワップチェイン作成に失敗"); }


	//- レンダーターゲットビューの作成
	ID3D11Texture2D* renderTarget = {};
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	hr = m_pDevice->CreateRenderTargetView(renderTarget, NULL, &m_pRenderTargetView);
	renderTarget->Release();

	if (FAILED(hr)) { Message::ErrorMessage("レンダーターゲットビュー作成に失敗"); return; }


	//- デプスステンシルビューの作成
	ID3D11Texture2D* depthStencilebuffer = {};
	D3D11_TEXTURE2D_DESC textureDesc	 = {};
	textureDesc.Width  = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format		 = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc	 = swapChainDesc.SampleDesc;
	textureDesc.Usage		 = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags	 = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags  = 0;
	textureDesc.MiscFlags		= 0;
	hr = m_pDevice->CreateTexture2D(&textureDesc, NULL, &depthStencilebuffer);

	if (FAILED(hr)) { Message::ErrorMessage("デプスステンシルバッファ作成に失敗"); return; }


	//- デプスステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	hr = m_pDevice->CreateDepthStencilView(depthStencilebuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	depthStencilebuffer->Release();
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	if (FAILED(hr)) { Message::ErrorMessage("デプスステンシルビュー作成に失敗"); return; }

	
	//- ビューポートの設定
	D3D11_VIEWPORT viewport = {};
	viewport.Width  = (float)SCREEN_WIDTH;
	viewport.Height = (float)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &viewport);
	m_pDeviceContext->RSSetViewports(1, &viewport);


	//- ラスタライザステートの設定
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;	//裏側は描画しない
	rasterizerDesc.DepthClipEnable	 = TRUE;
	//rasterizerDesc.FrontCounterClockwise = FALSE; //表の判定が逆になる...Clockwiseが時計回り(FALSE) - 反時計回り(TRUE)
	rasterizerDesc.MultisampleEnable = FALSE;
	ID3D11RasterizerState* rs = {};
	hr = m_pDevice->CreateRasterizerState(&rasterizerDesc, &rs);
	m_pDeviceContext->RSSetState(rs);
	Release_and_Null<>(rs, "rs");
	if (FAILED(hr)) { Message::ErrorMessage("ラスタライザステート作成に失敗"); }


	//- ブレンドステートの設定
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable		  = FALSE;
	blendDesc.IndependentBlendEnable	  = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend	= D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp	= D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha	 = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha	 = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState);

	blendDesc.AlphaToCoverageEnable = TRUE;
	hr = m_pDevice->CreateBlendState(&blendDesc, &m_pBlendStateATC);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDeviceContext->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff);
	if (FAILED(hr)) { Message::ErrorMessage("ブレンドステート作成に失敗");  return; }


	//- デプスステンシルステートの設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable	= TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc		= D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable  = FALSE;
	hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateEnable);//深度有効ステート
	if (FAILED(hr)) { Message::ErrorMessage("デプスステンシルステート作成に失敗(深度有効"); }

	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateDisable);//深度無効ステート
	if (FAILED(hr)) { Message::ErrorMessage("デプスステンシルステート作成に失敗(深度無効"); }

	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStateEnable, NULL);

	//- サンプラーステートの設定
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter	 = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	ID3D11SamplerState* samplerState = {};
	hr = m_pDevice->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(hr)) { Message::ErrorMessage("サンプラーステート作成に失敗"); }
	m_pDeviceContext->PSSetSamplers(0, 1, &samplerState);
	Release_and_Null<>(samplerState, "samplerState");

	//- 定数バッファの作成
	CreateConstantBuffer<DirectX::XMFLOAT4X4>("world",true);
	CreateConstantBuffer<DirectX::XMFLOAT4X4>("view",true);
	CreateConstantBuffer<DirectX::XMFLOAT4X4>("proj",true);
	CreateConstantBuffer<MATERIAL>("material");
	CreateConstantBuffer<LIGHT>("light");
	CreateConstantBuffer<TIME>("time");
	CreateConstantBuffer<CONSTANT_BUFFE_OBJECT>("object");
	CreateConstantBuffer<WAVE_BUFFER>("wave");

	LIGHT light = {};
	light.enable = true;
	light.direction = DirectX::XMFLOAT4(0.5f, -1.0f, 0.8f, 0.0f);
	DirectX::XMStoreFloat4(&light.direction,
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.5f, -1.0f, 0.8f, 0.0f)));
	light.ambient = DirectX::XMFLOAT4(1.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = DirectX::XMFLOAT4(1.5f, 1.5f, 1.5f, 1.0f);
	Write_Buffer<LIGHT>("light", light);

	MATERIAL material = {};
	material.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.ambient = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	Write_Buffer<MATERIAL>("material", material);

	TIME time = {};
	time.time = 0.0f;
	Write_Buffer<TIME>("time", time);

	CONSTANT_BUFFE_OBJECT object = {};
	object.pos   = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	object.scale = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	Write_Buffer<CONSTANT_BUFFE_OBJECT>("object", object);

	WAVE_BUFFER wave = {};
	Write_Buffer<WAVE_BUFFER>("wave", wave);
}

void DirectXRenderer::Uninit()
{
	//- バッファの解放
	for (auto itr = m_bufferTypeMap.begin(); itr != m_bufferTypeMap.end(); itr++)
	{
		ID3D11Buffer* buffer = itr->second.second;
		Release_and_Null<>(buffer, itr->first.c_str());
	}
	m_bufferTypeMap.clear();

	Release_and_Null<>(m_pDepthStateEnable,	"m_pDepthStateEnable");
	Release_and_Null<>(m_pBlendStateATC,	"m_pBlendStateATC");
	Release_and_Null<>(m_pBlendState,		"m_pBlendState");
	Release_and_Null<>(m_pDepthStencilView,	"m_pDepthStencilView");
	Release_and_Null<>(m_pDepthStateDisable,"m_pDepthStateDisable");
	Release_and_Null<>(m_pRenderTargetView,	"m_pRenderTargetView");
	Release_and_Null<>(m_pSwapChain,		"m_pSwapChain");
	if (m_pDeviceContext) m_pDeviceContext->ClearState();
	Release_and_Null<>(m_pDeviceContext,	"m_pDeviceContext");
	Release_and_Null<>(m_pDevice,			"m_pDevice");
}

void DirectXRenderer::BeginDraw()
{
	float clearColor[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectXRenderer::EndDraw()
{
	m_pSwapChain->Present(1, 0);
}

/*
===================================================================

シェーダー

===================================================================
*/

void DirectXRenderer::CreateVertexShader(ID3D11VertexShader ** vs, ID3D11InputLayout ** vtxlayout, const char * filename)
{

	FILE* file;
	long int fsize;
	errno_t err;

	err = fopen_s(&file,filename, "rb");
	assert(err == 0);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_pDevice->CreateVertexShader(buffer, fsize, NULL, vs);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{

		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};
	UINT numElements = ARRAYSIZE(layout);

	m_pDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		vtxlayout);

	delete[] buffer;
}

void DirectXRenderer::CreatePixelShader(ID3D11PixelShader ** ps, const char * filename)
{
	FILE* file;
	long int fsize;
	errno_t err;

	err = fopen_s(&file, filename, "rb");
	assert(err == 0);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_pDevice->CreatePixelShader(buffer, fsize, NULL, ps);

	delete[] buffer;
}

/*
===================================================================

セッター

===================================================================
*/

void DirectXRenderer::Set_ATCEnable(bool enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (enable){ m_pDeviceContext->OMSetBlendState(m_pBlendStateATC, blendFactor, 0xffffffff); }
	else{ m_pDeviceContext->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff); }
		
}


void DirectXRenderer::Set_CullingMode(D3D11_CULL_MODE mode)
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;

	ID3D11RasterizerState* rs = {};
	switch (mode)
	{
	case D3D11_CULL_NONE : rasterizerDesc.CullMode = D3D11_CULL_NONE ; break;
	case D3D11_CULL_FRONT: rasterizerDesc.CullMode = D3D11_CULL_FRONT; break;
	case D3D11_CULL_BACK : rasterizerDesc.CullMode = D3D11_CULL_BACK ; break;
	}
	m_pDevice->CreateRasterizerState(&rasterizerDesc, &rs);
	m_pDeviceContext->RSSetState(rs);
	Release_and_Null<>(rs, "rs");
}

/*
===================================================================

定数バッファの書き込み

===================================================================
*/

void DirectXRenderer::Write_World(DirectX::XMFLOAT4X4* world)
{
	DirectX::XMFLOAT4X4 worldbuf;
	DirectX::XMStoreFloat4x4(&worldbuf,
		DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(world)));
	Write_Buffer<DirectX::XMFLOAT4X4>("world", worldbuf);
}

void DirectXRenderer::Write_View(DirectX::XMFLOAT4X4* view)
{
	DirectX::XMFLOAT4X4 viewbuf;
	DirectX::XMStoreFloat4x4(&viewbuf,
		DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(view)));
	Write_Buffer<DirectX::XMFLOAT4X4>("view", viewbuf);
}


void DirectXRenderer::write_Projection(DirectX::XMFLOAT4X4* proj)
{
	DirectX::XMFLOAT4X4 projbuf;
	DirectX::XMStoreFloat4x4(&projbuf,
		DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(proj)));
	Write_Buffer<DirectX::XMFLOAT4X4>("proj", projbuf);
}

void DirectXRenderer::Write_WorldViewProjection2D()
{
	DirectX::XMFLOAT4X4 world, view, projection = {};
	DirectX::XMStoreFloat4x4(&world,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()));
	Write_Buffer<DirectX::XMFLOAT4X4>("world", world);

	DirectX::XMStoreFloat4x4(&view,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()));
	Write_Buffer<DirectX::XMFLOAT4X4>("view", view);

	DirectX::XMStoreFloat4x4(&projection,
		DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f)));
	Write_Buffer<DirectX::XMFLOAT4X4>("proj", projection);
}


