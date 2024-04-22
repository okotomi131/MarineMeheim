/*********************************************************************
 * @file   SceneStageSelect.h
 * @brief  �X�e�[�W�Z���N�g�V�[��
 *********************************************************************/
#ifndef __SCENE_STAGE_SELECT_H__
#define __SCENE_STAGE_SELECT_H__

 /*
 ==================================================

 �C���N���[�h

 ==================================================
 */
#include "../SceneBase.h"

class SceneStageSelect : public SceneBase
{
public:
	/**
	 * @brief ����������
	 */
	void Init() override;

	void CreateStageView();

	void CreateButton();

	/**
	 * @brief �X�V����
	 */
	void Update(float deltatim) override;
	void MoveScroll();


private:
	std::vector<class ButtonBase*> m_pStageButtons = {};
	std::vector<class ImageDrawer*> m_pStageViews  = {};

	DirectX::XMFLOAT2 m_selectButtonSize = {};
	DirectX::XMFLOAT2 m_selectButtonPos  = {};
	DirectX::XMFLOAT2 m_UnSelectButtonSize = {};

	DirectX::XMFLOAT2 m_viewImageSize = {};
	DirectX::XMFLOAT2 m_viewImagePos  = {};
	int m_selectCnt = 0;
	int m_oldSelectCnt = 0;

};

#endif // !__SCENE_STAGE_SELECT_H__