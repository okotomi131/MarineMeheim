/*********************************************************************
 * @file   DirectXRenderer.h
 * @brief  DirectXの制御クラス
 * 定数バッファ宣言、シェーダーの読み込みを行う
 *********************************************************************/

#ifndef __DIRECTX_RENDERER_H__
#define __DIRECTX_RENDERER_H__

/*
==================================================

インクルード

==================================================
*/
#include "../main.h"
#include <typeindex>

/*
==================================================

マクロ・定数定義

==================================================
*/
static const int WAVE_MAX = 40;


/*
==================================================

構造体
 
==================================================
*/

//- 3D頂点用
struct VERTEX3D
{
	DirectX::XMFLOAT3 pos;		//頂点座標
	DirectX::XMFLOAT3 normal;	//法線ベクトル
	DirectX::XMFLOAT4 diffuse;	//ディフューズカラー
	DirectX::XMFLOAT2 uv;		//テクスチャ座標
};

/*
==================================================

構造体(定数バッファ用)

==================================================
*/

//- マテリアル用
struct MATERIAL
{
	DirectX::XMFLOAT4	ambient;		//アンビエント
	DirectX::XMFLOAT4	diffuse;		//ディフューズカラー
	DirectX::XMFLOAT4	specular;		//スペキュラカラー
	DirectX::XMFLOAT4	emission;		//エミッションカラー
	float				shininess;		//スネーク値(光沢の強度
	float 				dummy[3];		//ダミー
};

//- ライト用
struct LIGHT
{
	BOOL enable;				//ライト有効フラグ
	BOOL dummy[3];				
	DirectX::XMFLOAT4 direction;//方向
	DirectX::XMFLOAT4 diffuse;  //色
	DirectX::XMFLOAT4 ambient;  //環境光
};

//- 時間用
struct TIME
{
	float time;		//時間
	float dummy[3];	//ダミー
};

//- オブジェクト用
struct CONSTANT_BUFFE_OBJECT
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 scale;
	float dummy[2];
};

//- 波用
struct WAVE
{
	DirectX::XMFLOAT2 direction;	// 波の進行方向
	float amplitude;				// 振幅
	float lenght;					// 波長
};

struct WAVE_BUFFER
{
	WAVE wave[WAVE_MAX];
};

/*
==================================================

列挙型

==================================================
*/

//マトリックス用
enum class E_MATRIX_TYPE
{
	World,
	View,
	Proj,

	Max
};

//定数バッファ用
enum class E_CONSTANT_BUFFER_TYPE
{
	Material,
	Light,
	Time,
	Object,

	Max
};

class DirectXRenderer
{
public:
	/**
	 * @brief 初期化処理
	 * DirectXの初期化を行う
	 */
	static void Init();

	/**
	 * @brief 終了処理
	 * DirectXの終了処理を行う
	 */
	static void Uninit();

	/**
	 * @brief 描画開始処理
	 */
	static void BeginDraw();

	/**
	 * @brief 描画終了処理
	 */
	static void EndDraw();


	/*
	==================================================

	セッター

	==================================================
	*/
	

	/**
	 * @brief 深度バッファ有効設定
	 * @param enable 有効フラグ
	 */
	inline static void Set_DepthEnable(bool enable) 
	{
		if (enable) 
		{ m_pDeviceContext->OMSetDepthStencilState(m_pDepthStateEnable, 0); }
		else
		{ m_pDeviceContext->OMSetDepthStencilState(m_pDepthStateDisable, 0); }
	};


	/**
	 * @brief ブレンドステートの有効設定
	 * @param enable 有効フラグ
	 */
	static void Set_ATCEnable(bool enable);
	
	/**
	 * @brief カリングモード設定
	 * @param mode カリングモード
	 */
	static void Set_CullingMode(D3D11_CULL_MODE mode);


	/*
	==================================================

	ゲッター

	==================================================
	*/

	/**
	 * @brief デバイス取得
	 * @return デバイスのポインタ
	 */
	inline static ID3D11Device* Get_Device()
	{return m_pDevice;};

	/**
	 * @brief デバイスコンテキスト取得
	 * @return デバイスコンテキストのポインタ
	 */
	inline static ID3D11DeviceContext* Get_DeviceContext()
	{	return m_pDeviceContext;};

	/**
	 * @brief スワップチェイン取得
	 * @return スワップチェインのポインタ
	 */
	inline static IDXGISwapChain* Get_SwapChain()
	{	return m_pSwapChain;};


	/*
	==================================================

	定数バッファ書き込み

	==================================================
	*/


	/**
	 * @brief ワールド行列設定
	 * @param world ワールド行列
	 */
	static void Write_World(DirectX::XMFLOAT4X4* world);

	/**
	 * @brief ビュー行列設定
	 * @param view ビュー行列
	 */
	static void Write_View(DirectX::XMFLOAT4X4* view);

	/**
	 * @brief プロジェクション行列設定
	 * @param proj プロジェクション行列
	 */
	static void write_Projection(DirectX::XMFLOAT4X4* proj);

	/**
	 * @brief 2D用のWVP設定を行う
	 */
	static void Write_WorldViewProjection2D();

	/**
	 * @brief 定数バッファの作成を行う
	 * @param BufferName バッファ名
	 * @param OnlySetVS 頂点シェーダーのみに登録を行うか
	 */
	template<typename T>
	static void CreateConstantBuffer(std::string BufferName, bool OnlySetVS = false)
	{
		//- 定数バッファの作成
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(T);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = sizeof(float);

		ID3D11Buffer* buffer = nullptr;
		HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, nullptr, &buffer);
		if (FAILED(hr)) { Message::DebugLog("定数バッファの作成に失敗"); return; }
		//- バッファの更新
		m_pDeviceContext->VSSetConstantBuffers(static_cast<UINT>(m_bufferTypeMap.size()), 1, &buffer);
		if (!OnlySetVS) { m_pDeviceContext->PSSetConstantBuffers(static_cast<UINT>(m_bufferTypeMap.size()), 1, &buffer); }

		//- 型とバッファと名前を登録
		m_bufferTypeMap.insert(std::make_pair(BufferName,			//バッファ名の登録
			std::make_pair(std::type_index(typeid(T)), buffer)));	//型とバッファの登録
	}

	/**
	 * @brief 定数バッファの書き込みを行う
	 * @param BufferName バッファ名
	 * @param data 書き込むデータ
	 */
	template<typename T>
	static void Write_Buffer(std::string BufferName,T data)
	{
		//- バッファの取得
		auto moldbuffer = m_bufferTypeMap.find(BufferName);
		ID3D11Buffer* buffer = moldbuffer->second.second;
		if(buffer == nullptr) { Message::DebugLog("バッファが見つかりません"); return; }
		//- 型が一致しているか確認
		if (moldbuffer->second.first != std::type_index(typeid(data)))
		{ Message::DebugLog("型が一致しません"); return; }

		m_pDeviceContext->UpdateSubresource(buffer, 0, nullptr, &data, 0, 0);
	}

	/*
	==================================================

	シェーダー

	==================================================
	*/

	/**
	 * @brief 頂点シェーダーの作成を行う
	 * 
	 * @param vs 頂点シェーダー
	 * @param VertexLayout 頂点レイアウト
	 * @param FileName シェーダファイル名
	 */
	static void CreateVertexShader(ID3D11VertexShader** vs, ID3D11InputLayout** VertexLayout, const char* FileName);

	/**
	 * @brief ピクセルシェーダーの作成を行う
	 * 
	 * @param ps ピクセルシェーダー
	 * @param FileName シェーダファイル名
	 */
	static void CreatePixelShader(ID3D11PixelShader** ps, const char* FileName);


private:

	static D3D_FEATURE_LEVEL        m_pFeatureLevel;
	static ID3D11Device*            m_pDevice;
	static ID3D11DeviceContext*     m_pDeviceContext;
	static IDXGISwapChain*          m_pSwapChain;
	static ID3D11RenderTargetView*  m_pRenderTargetView;
	static ID3D11DepthStencilView*  m_pDepthStencilView;
	static ID3D11DepthStencilState* m_pDepthStateEnable;
	static ID3D11DepthStencilState* m_pDepthStateDisable;
	static ID3D11BlendState*		m_pBlendState;
	static ID3D11BlendState*		m_pBlendStateATC;
	static std::unordered_map<std::string, std::pair<std::type_index, ID3D11Buffer*>> m_bufferTypeMap;
};

#endif // !__DIRECTX_RENDERER_H__