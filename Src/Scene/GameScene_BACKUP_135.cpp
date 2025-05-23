#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
<<<<<<< HEAD
#include "../Object/Enemy/Enemy.h"
=======
#include "../Object/Stage/Stage.h"
>>>>>>> 0eb14c3af250a85def310bbf5bc90111ef407bd3
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
	player_->Init();
<<<<<<< HEAD
	//エネミー
	enemy_ = new Enemy();
	enemy_->Init();
=======

	// ステージ
	stage_ = new Stage();
	stage_->Init(this);
>>>>>>> 0eb14c3af250a85def310bbf5bc90111ef407bd3
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


