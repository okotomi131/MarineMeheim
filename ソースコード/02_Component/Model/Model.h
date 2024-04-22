/*********************************************************************
 * @file   Model.h
 * @brief  モデルの読み込みと描画を行う
 *********************************************************************/
#ifndef __MODEL_H__
#define __MODEL_H__

 /*
 ==================================================

 インクルード

 ==================================================
 */
#include <string>
#include <unordered_map>

#include "../Component.h"
#include "../../01_System/DirectX/DirectXRenderer.h"
#include "../../01_System/main.h"

 /*
 ==================================================

 構造体

 ==================================================
 */

//マテリアル
struct MODEL_MATERIAL
{
	char						Name[256];			//マテリアル名
	MATERIAL					Material;			//マテリアルデータ
	char						TextureName[256];	//テクスチャ名
	ID3D11ShaderResourceView*	Texture;			//テクスチャ

};


//描画サブセット
struct SUBSET
{
	unsigned int	StartIndex;	//開始インデックス
	unsigned int	IndexNum;	//インデックス数
	MODEL_MATERIAL	Material;	//マテリアル
};


//モデル
struct MODEL_OBJ
{
	VERTEX3D		*VertexArray; //頂点配列
	unsigned int	VertexNum;	  //頂点数

	unsigned int	*IndexArray;	//インデックス配列
	unsigned int	IndexNum;		//インデックス数

	SUBSET			*SubsetArray;	//サブセット配列
	unsigned int	SubsetNum;		//サブセット数
};

//モデルデータ
struct MODEL_DATA
{
	ID3D11Buffer*	VertexBuffer;	//頂点バッファ
	ID3D11Buffer*	IndexBuffer;	//インデックスバッファ

	SUBSET*			SubsetArray;	//サブセット配列
	unsigned int	SubsetNum;		//サブセット数
};

class Model : public Component
{

public:
	using Component::Component;

	/**
	 * @brief モデルのプリロード
	 * @param FileName 
	 */
	static void Preload(const char* FileName);

	/**
	 * @brief モデルのアンロード
	 * @param FileName
	 */
	static void UnloadAll();

	/**
	 * @brief 指定されたモデルを読み込む
	 * @param FileName
	 */
	void Load(const char* FileName);

	/**
	 * @brief 描画処理
	 */
	void Draw() override;

private:
	/**
	 * @brief モデルの読み込み処理
	 * @param FileName
	 * @param Model モデルデータ構造体
	 */
	static void LoadModel(const char *FileName, MODEL_DATA *Model);

	/**
	 * @brief オブジェクトデータの読み込み処理
	 * @param Model モデルデータ構造体
	 */
	static void LoadObj( const char *FileName, MODEL_OBJ *ModelObj );

	/**
	 * @brief マテリアルの読み込み処理
	 * @param FileName
	 * @param MaterialArray マテリアルデータ構造体
	 * @param MaterialNum マテリアル数
	 */
	static void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

	static std::unordered_map<std::string, MODEL_DATA*> m_ModelPool; //モデルプール
	MODEL_DATA* m_Model = {};	//モデルデータ
};

#endif // !__MODEL_H__