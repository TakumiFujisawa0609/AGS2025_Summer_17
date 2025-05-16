#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
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
	//エネミー
	enemy_ = new Enemy();
	// ステージ
	stage_ = new Stage();
	// ステージ
	stage_ = new Stage();
	// カメラ
	camera_ = new Camera();
	


	player_->Init(camera_, stage_);
	stage_->Init(this, player_,camera_);
	camera_->Init(player_,this);
	enemy_->Init();

}

void GameScene::Update(void)
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->Update();

	// プレイヤーの更新
	player_->Update();

	// エネミーの更新
	enemy_->Update();

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
	// エネミーの描画
	enemy_->Draw();

	DrawFormatString(0, 0, 0x000000, "GameScene");
	
}


