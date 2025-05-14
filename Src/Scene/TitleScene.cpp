#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{
	
}

void TitleScene::Init(void)
{
	//‰æ‘œ“Ç‚İ‚İ
	//int ret;
	//ret = img_;
	//img_ = res.Load(ResourceManager::SRC::BLOCK).handleId_;
	//if (img_ == -1)
	//{
	//	return;
	//}
	

}

void TitleScene::Update(void)
{

	
	// ƒV[ƒ“‘JˆÚ
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
	
}

void TitleScene::Draw(void)
{
	
	DrawFormatString(0, 0, 0x000000, "TitleScene");

}

