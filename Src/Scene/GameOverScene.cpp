#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{//画像読み込み
	img_ = LoadGraph((Application::PATH_IMAGE + "Scene/false.png").c_str());

	soundImg_ = LoadSoundMem("Data/Sound/BGM/Lose.mp3");

	successSound = LoadSoundMem("Data/Sound/SE/success.mp3");

	PlaySoundMem(soundImg_, DX_PLAYTYPE_LOOP); // 効果音をループ再生

	// 点滅させたい周期（例：30フレームで切り替え、約0.5秒）
	blinkCycle = 90;

	//フレームカウントの初期化
	frameCount = 0;
}

void GameOverScene::Update(void)
{
	

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		StopSoundMem(soundImg_); // 効果音を停止
		PlaySoundMem(successSound, DX_PLAYTYPE_BACK); // 成功音を再生
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameOverScene::Draw(void)
{
	frameCount++;
	
	
	// 画像描画  
	DrawGraph(0, 0, img_, TRUE);

	SetFontSize(50);
	if ((static_cast<int>(frameCount) % static_cast<int>(blinkCycle)) < static_cast<int>(blinkCycle) / 2) {
		DrawFormatString(725, 700, 0x000000, "SPACEでタイトルに戻る");
	}
	SetFontSize(16);
}
