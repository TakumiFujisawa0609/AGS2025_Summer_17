#include<DxLib.h>
#include "ClearScene.h"
#include "../Application.h"

void ClearScene::Init(void)
{
	Img_ = LoadGraph((Application::PATH_IMAGE + "Scene/Clear.jpg").c_str());
}

void ClearScene::Update(void)
{
}

void ClearScene::Draw(void)
{
	DrawFormatString(0, 0, 0x000000, "ClearScene");
	// ‰æ‘œ•`‰æ
	DrawGraph(0, 0, Img_, TRUE);
}
