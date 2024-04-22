/*********************************************************************
 * @file   Model.h
 * @brief  ���f���̓ǂݍ��݂ƕ`����s��
 *********************************************************************/
#ifndef __MODEL_H__
#define __MODEL_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include <string>
#include <unordered_map>

#include "../Component.h"
#include "../../01_System/DirectX/DirectXRenderer.h"
#include "../../01_System/main.h"

 /*
 ==================================================

 �\����

 ==================================================
 */

//�}�e���A��
struct MODEL_MATERIAL
{
	char						Name[256];			//�}�e���A����
	MATERIAL					Material;			//�}�e���A���f�[�^
	char						TextureName[256];	//�e�N�X�`����
	ID3D11ShaderResourceView*	Texture;			//�e�N�X�`��

};


//�`��T�u�Z�b�g
struct SUBSET
{
	unsigned int	StartIndex;	//�J�n�C���f�b�N�X
	unsigned int	IndexNum;	//�C���f�b�N�X��
	MODEL_MATERIAL	Material;	//�}�e���A��
};


//���f��
struct MODEL_OBJ
{
	VERTEX3D		*VertexArray; //���_�z��
	unsigned int	VertexNum;	  //���_��

	unsigned int	*IndexArray;	//�C���f�b�N�X�z��
	unsigned int	IndexNum;		//�C���f�b�N�X��

	SUBSET			*SubsetArray;	//�T�u�Z�b�g�z��
	unsigned int	SubsetNum;		//�T�u�Z�b�g��
};

//���f���f�[�^
struct MODEL_DATA
{
	ID3D11Buffer*	VertexBuffer;	//���_�o�b�t�@
	ID3D11Buffer*	IndexBuffer;	//�C���f�b�N�X�o�b�t�@

	SUBSET*			SubsetArray;	//�T�u�Z�b�g�z��
	unsigned int	SubsetNum;		//�T�u�Z�b�g��
};

class Model : public Component
{

public:
	using Component::Component;

	/**
	 * @brief ���f���̃v�����[�h
	 * @param FileName 
	 */
	static void Preload(const char* FileName);

	/**
	 * @brief ���f���̃A�����[�h
	 * @param FileName
	 */
	static void UnloadAll();

	/**
	 * @brief �w�肳�ꂽ���f����ǂݍ���
	 * @param FileName
	 */
	void Load(const char* FileName);

	/**
	 * @brief �`�揈��
	 */
	void Draw() override;

private:
	/**
	 * @brief ���f���̓ǂݍ��ݏ���
	 * @param FileName
	 * @param Model ���f���f�[�^�\����
	 */
	static void LoadModel(const char *FileName, MODEL_DATA *Model);

	/**
	 * @brief �I�u�W�F�N�g�f�[�^�̓ǂݍ��ݏ���
	 * @param Model ���f���f�[�^�\����
	 */
	static void LoadObj( const char *FileName, MODEL_OBJ *ModelObj );

	/**
	 * @brief �}�e���A���̓ǂݍ��ݏ���
	 * @param FileName
	 * @param MaterialArray �}�e���A���f�[�^�\����
	 * @param MaterialNum �}�e���A����
	 */
	static void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

	static std::unordered_map<std::string, MODEL_DATA*> m_ModelPool; //���f���v�[��
	MODEL_DATA* m_Model = {};	//���f���f�[�^
};

#endif // !__MODEL_H__