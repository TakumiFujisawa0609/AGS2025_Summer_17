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
//画像読み込み
img_ = LoadGraph((Application::PATH_IMAGE + "Scene/Title.png").c_str());



// タイトルBGMの読み込み
TitleSoundHandle_ = LoadSoundMem("Data/Sound/BGM/TBGM.mp3");

successSound = LoadSoundMem("Data/Sound/SE/success.mp3");

PlaySoundMem(TitleSoundHandle_, DX_PLAYTYPE_LOOP); // タイトルBGMをループ再生


// 点滅させたい周期（例：30フレームで切り替え、約0.5秒）
blinkCycle = 120;

//フレームカウントの初期化
frameCount = 0;
count_ = 0;

}

void TitleScene::Update(void)
{
	count_++;
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (count_ >= 3)
	{
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{

			StopSoundMem(TitleSoundHandle_); // タイトルBGMを停止
			PlaySoundMem(successSound, DX_PLAYTYPE_BACK); // 成功音を再生

			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			count_ = 0;
			
		}
	}
}

void TitleScene::Draw(void)  
{  
  frameCount++;  
 

  // 画像描画  
  DrawGraph(0, 0, img_, TRUE);  

  SetFontSize(50);
  if ((static_cast<int>(frameCount) % static_cast<int>(blinkCycle)) < static_cast<int>(blinkCycle) / 2) {  
      DrawFormatString(650, 700, 0x000000, "SPACEキーを押してスタート\n\n  ESCでポーズメニュー");
  }  
  SetFontSize(16);

#ifdef _DEBUG
  //当たり判定の可視化
  DrawFormatString(0, 0, 0x000000, "TitleScene");



#endif // DEBUG
}
