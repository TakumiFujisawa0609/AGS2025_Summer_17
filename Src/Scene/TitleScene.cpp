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

// 点滅させたい周期（例：30フレームで切り替え、約0.5秒）
blinkCycle = 60;

//フレームカウントの初期化
frameCount = 0;

}

void TitleScene::Update(void)
{
// シーン遷移
InputManager& ins = InputManager::GetInstance();
if (ins.IsTrgDown(KEY_INPUT_SPACE))
{
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}
}

void TitleScene::Draw(void)  
{  
  frameCount++;  
  DrawFormatString(0, 0, 0x000000, "TitleScene");  

  // 画像描画  
  DrawGraph(0, 0, img_, TRUE);  

  SetFontSize(50);
  if ((static_cast<int>(frameCount) % static_cast<int>(blinkCycle)) < static_cast<int>(blinkCycle) / 2) {  
      DrawFormatString(725, 700, 0x000000, "PREASE_HIT_SPACE_KEY");
  }  
  SetFontSize(16);
}
