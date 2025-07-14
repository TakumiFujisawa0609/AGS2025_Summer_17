#include<DxLib.h>
#include "../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include "ClearScene.h"
#include "../Application.h"

void ClearScene::Init(void)
{
	Img_ = LoadGraph((Application::PATH_IMAGE + "Scene/castle.jpg").c_str());

	SoundImg_ = LoadSoundMem("Data/Sound/SE/Clear.mp3");

	clearImg_ = LoadGraph((Application::PATH_IMAGE + "Scene/Clear.png").c_str());

	successSound = LoadSoundMem("Data/Sound/SE/success.mp3");
	PlaySoundMem(SoundImg_, DX_PLAYTYPE_BACK); // 効果音をループ再生

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
		PlaySoundMem(successSound, DX_PLAYTYPE_BACK); // 成功音を再生
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	
}

void ClearScene::Draw(void)
{

	// 入力マネージャのインスタンスを取得
	InputManager& ins = InputManager::GetInstance();
	Application& app = Application::GetInstance();
	frameCount++;
	// 画像描画
	DrawGraph(0, 0, Img_, TRUE);

	DrawGraph((1920-666)/2,(1080/2) - 375
		, clearImg_, TRUE);
	SetFontSize(50);
	if ((static_cast<int>(frameCount) % static_cast<int>(blinkCycle)) < static_cast<int>(blinkCycle) / 2) {
		DrawFormatString(725, 700, 0xFFFFFF, "SPACEキーでタイトルに戻る");

	}
	SetFontSize(16);
	
#ifdef _DEBUG
	//当たり判定の可視化
	DrawFormatString(0, 0, 0x000000, "ClearScene");



#endif // DEBUG
}