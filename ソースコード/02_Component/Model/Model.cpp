/*********************************************************************
 * @file   Model.cpp
 * @brief  ���f���̕`��Ɠǂݍ��݂��s��
 *********************************************************************/

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <mbstring.h>
#include "Model.h"
#include "../../01_System/Texture/CreateTexture.h"

std::unordered_map<std::string, MODEL_DATA*> Model::m_ModelPool;

void Model::Draw()
{
	//- ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	DirectXRenderer::Get_DeviceContext()->IASetVertexBuffers(
		0, 1, &m_Model->VertexBuffer, &stride, &offset);

	//- �C���f�b�N�X�o�b�t�@�ݒ�
	DirectXRenderer::Get_DeviceContext()->IASetIndexBuffer(
		m_Model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//- �v���~�e�B�u�g�|���W�ݒ�
	DirectXRenderer::Get_DeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
	�h���[�R�[���̐������炵�č��������邽�߂ɁA
	�����e�N�X�`�����g���T�u�Z�b�g���O���[�v������
	*/
	std::map<ID3D11ShaderResourceView*, std::vector<SUBSET*>> textureBatches;
	for (unsigned int i = 0; i < m_Model->SubsetNum; i++) 
	{
		//- �e�N�X�`�����L�[�Ƃ��A�����e�N�X�`�������T�u�Z�b�g���o�b�`��
		textureBatches[m_Model->SubsetArray[i].Material.Texture].push_back(
			&m_Model->SubsetArray[i]);
	}

	//- �e�e�N�X�`���o�b�`�̕`��
	for (auto& batch : textureBatches) {
		
		//- �e�N�X�`���ݒ�
		DirectXRenderer::Get_DeviceContext()->PSSetShaderResources(0, 1, &batch.first);

		//- �����e�N�X�`�������T�u�Z�b�g��`��
		for (auto subset : batch.second) {
			//- �}�e���A���ݒ�
			//DirectXRenderer::Write_Material(subset->Material.Material);
			DirectXRenderer::Write_Buffer<MATERIAL>("material", subset->Material.Material);
			//- �|���S���`��
			DirectXRenderer::Get_DeviceContext()->DrawIndexed(subset->IndexNum, subset->StartIndex, 0);
		}
	}
}

void Model::Preload(const char *FileName)
{
	if (m_ModelPool.count(FileName) > 0)
	{
		return;
	}

	MODEL_DATA* model = new MODEL_DATA;
	LoadModel(FileName, model);

	m_ModelPool[FileName] = model;
}

void Model::UnloadAll()
{
	for (std::pair<const std::string, MODEL_DATA*> pair : m_ModelPool)
	{
		pair.second->VertexBuffer->Release();
		pair.second->IndexBuffer->Release();

		for (unsigned int i = 0; i < pair.second->SubsetNum; i++)
		{
			if (pair.second->SubsetArray[i].Material.Texture)
				pair.second->SubsetArray[i].Material.Texture->Release();
		}

		delete[] pair.second->SubsetArray;

		delete pair.second;
	}

	m_ModelPool.clear();
}

void Model::Load(const char *FileName)
{
	if (m_ModelPool.count(FileName) > 0)
	{
		m_Model = m_ModelPool[FileName];
		return;
	}

	m_Model = new MODEL_DATA;
	LoadModel(FileName, m_Model);

	m_ModelPool[FileName] = m_Model;
}

void Model::LoadModel( const char *FileName, MODEL_DATA *Model)
{
	MODEL_OBJ modelObj;
	LoadObj( FileName, &modelObj );

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( VERTEX3D ) * modelObj.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = modelObj.VertexArray;

		DirectXRenderer::Get_Device()->CreateBuffer( &bd, &sd, &Model->VertexBuffer );
	}

	// �C���f�b�N�X�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( unsigned int ) * modelObj.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = modelObj.IndexArray;

		DirectXRenderer::Get_Device()->CreateBuffer( &bd, &sd, &Model->IndexBuffer );
	}

	// �T�u�Z�b�g�ݒ�
	{
		Model->SubsetArray = new SUBSET[ modelObj.SubsetNum ];
		Model->SubsetNum = modelObj.SubsetNum;

		for( unsigned int i = 0; i < modelObj.SubsetNum; i++ )
		{
			Model->SubsetArray[i].StartIndex = modelObj.SubsetArray[i].StartIndex;
			Model->SubsetArray[i].IndexNum = modelObj.SubsetArray[i].IndexNum;

			Model->SubsetArray[i].Material.Material = modelObj.SubsetArray[i].Material.Material;

			Model->SubsetArray[i].Material.Texture = nullptr;

			CreateTextureFromFile(DirectXRenderer::Get_Device(),
				modelObj.SubsetArray[i].Material.TextureName,
				&Model->SubsetArray[i].Material.Texture);

			//if (Model->SubsetArray[i].Material.Texture)
				//Model->SubsetArray[i].Material.Material.textureEnable = true;
			//else
			//	Model->SubsetArray[i].Material.Material.textureEnable = false;

		}
	}

	delete[] modelObj.VertexArray;
	delete[] modelObj.IndexArray;
	delete[] modelObj.SubsetArray;

}

/**
 * @brief �����̃t�@�C�����Ɖ~�L�����폜
 * @param pszPath �p�X
 * @return �폜�ł�����true
 */
bool _PathRemoveFileSpecExA(char *pszPath)
{
	unsigned char* pbs = _mbsrchr((unsigned char*)pszPath, '\\');
	unsigned char* psl = _mbsrchr((unsigned char*)pszPath, '/');
	if (pbs) {
		if (psl) {
			if (pbs > psl)
				*pbs = '\0';
			else
				*psl = '\0';
			return true;
		} else {
			*pbs = '\0';
			return true;
		}
	} else {
		if (psl) {
			*psl = '\0';
			return true;
		}
	}
	return false;
}


void Model::LoadObj( const char *FileName, MODEL_OBJ *ModelObj )
{

	char dir[MAX_PATH];
	strcpy(dir, FileName );
	_PathRemoveFileSpecExA(dir);


	DirectX::XMFLOAT3	*positionArray;
	DirectX::XMFLOAT3	*normalArray;
	DirectX::XMFLOAT2	*texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = nullptr;
	unsigned int	materialNum = 0;

	char str[256];
	char *s;
	char c;


	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);



	//�v�f���J�E���g
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "v" ) == 0 )
		{
			positionNum++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			normalNum++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			texcoordNum++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			subsetNum++;
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			in = 0;

			do
			{
				fscanf( file, "%s", str );
				vertexNum++;
				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c!= '\r' );

			//�l�p�͎O�p�ɕ���
			if( in == 4 )
				in = 6;

			indexNum += in;
		}
	}


	//�������m��
	positionArray = new DirectX::XMFLOAT3[ positionNum ];
	normalArray = new DirectX::XMFLOAT3[ normalNum ];
	texcoordArray = new DirectX::XMFLOAT2[ texcoordNum ];


	ModelObj->VertexArray = new VERTEX3D[ vertexNum ];
	ModelObj->VertexNum = vertexNum;

	ModelObj->IndexArray = new unsigned int[ indexNum ];
	ModelObj->IndexNum = indexNum;

	ModelObj->SubsetArray = new SUBSET[ subsetNum ];
	ModelObj->SubsetNum = subsetNum;


	//�v�f�Ǎ�
	DirectX::XMFLOAT3 *position = positionArray;
	DirectX::XMFLOAT3 *normal = normalArray;
	DirectX::XMFLOAT2 *texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "mtllib" ) == 0 )
		{
			//�}�e���A���t�@�C��
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			LoadMaterial( path, &materialArray, &materialNum );
		}
		else if( strcmp( str, "o" ) == 0 )
		{
			//�I�u�W�F�N�g��
			fscanf( file, "%s", str );
		}
		else if( strcmp( str, "v" ) == 0 )
		{
			//���_���W
			fscanf( file, "%f", &position->x );
			fscanf( file, "%f", &position->y );
			fscanf( file, "%f", &position->z );
			position++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			//�@��
			fscanf( file, "%f", &normal->x );
			fscanf( file, "%f", &normal->y );
			fscanf( file, "%f", &normal->z );
			normal++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			//�e�N�X�`�����W
			fscanf( file, "%f", &texcoord->x );
			fscanf( file, "%f", &texcoord->y );
			//texcoord->x = 1.0f - texcoord->x;
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			//�}�e���A��
			fscanf( file, "%s", str );

			if( sc != 0 )
				ModelObj->SubsetArray[ sc - 1 ].IndexNum = ic - ModelObj->SubsetArray[ sc - 1 ].StartIndex;

			ModelObj->SubsetArray[ sc ].StartIndex = ic;


			for( unsigned int i = 0; i < materialNum; i++ )
			{
				if( strcmp( str, materialArray[i].Name ) == 0 )
				{
					ModelObj->SubsetArray[ sc ].Material.Material = materialArray[i].Material;
					strcpy( ModelObj->SubsetArray[ sc ].Material.TextureName, materialArray[i].TextureName );
					strcpy( ModelObj->SubsetArray[ sc ].Material.Name, materialArray[i].Name );

					break;
				}
			}

			sc++;
			
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			//��
			in = 0;

			do
			{
				fscanf( file, "%s", str );

				s = strtok( str, "/" );	
				ModelObj->VertexArray[vc].pos = positionArray[ atoi( s ) - 1 ];
				if( s[ strlen( s ) + 1 ] != '/' )
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok( nullptr, "/" );
					ModelObj->VertexArray[vc].uv = texcoordArray[ atoi( s ) - 1 ];
				}
				s = strtok( nullptr, "/" );	
				ModelObj->VertexArray[vc].normal = normalArray[ atoi( s ) - 1 ];

				ModelObj->VertexArray[vc].diffuse = DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );

				ModelObj->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c != '\r' );

			//�l�p�͎O�p�ɕ���
			if( in == 4 )
			{
				ModelObj->IndexArray[ic] = vc - 4;
				ic++;
				ModelObj->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if( sc != 0 )
		ModelObj->SubsetArray[ sc - 1 ].IndexNum = ic - ModelObj->SubsetArray[ sc - 1 ].StartIndex;


	fclose( file );


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

void Model::LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum )
{

	char dir[MAX_PATH];
	strcpy(dir, FileName);
	_PathRemoveFileSpecExA(dir);

	char str[256];

	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);

	MODEL_MATERIAL *materialArray;
	unsigned int materialNum = 0;

	//�v�f���J�E���g
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			materialNum++;
		}
	}


	//�������m��
	materialArray = new MODEL_MATERIAL[ materialNum ];


	//�v�f�Ǎ�
	int mc = -1;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			//�}�e���A����
			mc++;
			fscanf( file, "%s", materialArray[ mc ].Name );
			strcpy( materialArray[ mc ].TextureName, "" );

			materialArray[mc].Material.emission.x = 0.0f;
			materialArray[mc].Material.emission.y = 0.0f;
			materialArray[mc].Material.emission.z = 0.0f;
			materialArray[mc].Material.emission.w = 0.0f;
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//�A���r�G���g
			fscanf( file, "%f", &materialArray[ mc ].Material.ambient.x );
			fscanf( file, "%f", &materialArray[ mc ].Material.ambient.y );
			fscanf( file, "%f", &materialArray[ mc ].Material.ambient.z );
			materialArray[ mc ].Material.ambient.w = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//�f�B�t���[�Y
			fscanf( file, "%f", &materialArray[ mc ].Material.diffuse.x );
			fscanf( file, "%f", &materialArray[ mc ].Material.diffuse.y );
			fscanf( file, "%f", &materialArray[ mc ].Material.diffuse.z );
			materialArray[ mc ].Material.diffuse.w = 1.0f;
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//�X�y�L����
			fscanf( file, "%f", &materialArray[ mc ].Material.specular.x );
			fscanf( file, "%f", &materialArray[ mc ].Material.specular.y );
			fscanf( file, "%f", &materialArray[ mc ].Material.specular.z );
			materialArray[ mc ].Material.specular.w = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//�X�y�L�������x
			fscanf( file, "%f", &materialArray[ mc ].Material.shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//�A���t�@
			fscanf( file, "%f", &materialArray[ mc ].Material.diffuse.w );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//�e�N�X�`��
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			strcat( materialArray[ mc ].TextureName, path );
		}
	}

	fclose(file);

	*MaterialArray = materialArray;
	*MaterialNum = materialNum;


}
