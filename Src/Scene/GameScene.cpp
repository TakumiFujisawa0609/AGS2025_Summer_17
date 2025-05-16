#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Camera/Camera.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
	
}

GameScene::~GameScene(void)
{
	
}

void GameScene::Init(void)
{
	//プレイヤー
	player_ = new Player();
	// ステージ
	stage_ = new Stage();
	// カメラ
	camera_ = new Camera();
	


	player_->Init(camera_, stage_);
	stage_->Init(this, player_);
	camera_->Init(player_);
}

void GameScene::Update(void)
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->Update();

	// プレイヤーの更新
	player_->Update();

	// カメラの更新
	camera_->Update();
	
	// シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_R))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}

void GameScene::Draw(void)
{
	// ステージの描画
	stage_->Draw();
	// プレイヤーの描画
	player_->Draw();

	DrawFormatString(0, 0, 0x000000, "GameScene");
	
}


