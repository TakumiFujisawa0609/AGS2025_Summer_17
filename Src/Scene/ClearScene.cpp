#include<DxLib.h>
#include "../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include "ClearScene.h"
#include "../Application.h"

void ClearScene::Init(void)
{
	Img_ = LoadGraph((Application::PATH_IMAGE + "Scene/castle.jpg").c_str());

	clearImg_ = LoadGraph((Application::PATH_IMAGE + "Scene/Clear.png").c_str());

	// 点滅させたい周期（例：30フレームで切り替え、約0.5秒）
	blinkCycle = 60;

	//フレームカウントの初期化
	frameCount = 0;

}

void ClearScene::Update(void)
{
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void ClearScene::Draw(void)
{
	frameCount++;
	// 画像描画
	DrawGraph(0, 0, Img_, TRUE);

	DrawGraph((1920-666)/2,(1080/2) - 375
		, clearImg_, TRUE);
	SetFontSize(50);
	if ((static_cast<int>(frameCount) % static_cast<int>(blinkCycle)) < static_cast<int>(blinkCycle) / 2) {
		DrawFormatString(725, 700, 0xFFFFFF, "PREASE_HIT_SPACE_KEY");

	}
	SetFontSize(16);
#ifdef _DEBUG
	//当たり判定の可視化
	DrawFormatString(0, 0, 0x000000, "ClearScene");



#endif // DEBUG
}