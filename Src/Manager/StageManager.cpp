#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Wall/Wall.h"
#include "../Object/Attack/Blast.h"
#include "../Object/Attack/Plants.h"
#include "../Object/Attack/Water.h"
#include "StageManager.h"
StageManager::StageManager()
{

}
StageManager::~StageManager()
{

}
void StageManager::Init(Player* player, EnemyManager* enemyManager, Stage* stage, Camera* camera, Wall* wall, Blast* blast, Plants* plants, Water* water)
{
	player_ = player;
	enemyManager_ = enemyManager;
	stage_ = stage;
	camera_ = camera;
	wall_ = wall;
	blast_ = blast;
	plants_ = plants;
	water_ = water;

	stageType = STAGE_TYPE::STAGE1;

	
}
void StageManager::Update()
{
	// カメラの更新
	camera_->Update();
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		Update1();
		break;
	case STAGE_TYPE::STAGE2:
		Update2();
		break;
	case STAGE_TYPE::STAGE3:
		Update3();
		break;

	}

}
void StageManager::Update1()
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage1();

	// プレイヤーの更新
	player_->Update();
	
	// 壁の更新
	wall_->Update();
	blast_->Update();
	water_->Update();
	plants_->Update();
	// シーン遷移
	if (player_->GetPlayerPos().x>64 * 78)
	{
		ChangeStage(STAGE_TYPE::STAGE2);
	}
}
void StageManager::Update2()
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage2();

	// プレイヤーの更新
	player_->Update();

	// エネミーの更新
	enemyManager_->Update();

	if (player_->GetPlayerPos().x > 64 * 86)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}
	
}
void StageManager::Update3()
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage3();

	// プレイヤーの更新
	player_->Update();

	// エネミーの更新
	enemyManager_->Update();

	
}

void StageManager::Draw()
{
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		Draw1();
		break;
	case STAGE_TYPE::STAGE2:
		Draw2();
		break;
	case STAGE_TYPE::STAGE3:
		Draw3();
		break;

	}

}
void StageManager::Draw1()
{

	//壁の描画
	wall_->Draw();
	

	// プレイヤーの描画
	player_->Draw();

	// ステージの描画
	stage_->DrawStage1();



	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}
void StageManager::Draw2()
{
	////壁の描画
	//wall_->Draw();
	
	// プレイヤーの描画
	player_->Draw();

	
	// ステージの描画
	stage_->DrawStage2();

	

	// エネミーの描画
	enemyManager_->Draw();

	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}
void StageManager::Draw3()
{
	//壁の描画
	wall_->Draw();
	

	// プレイヤーの描画
	player_->Draw();

	

	// ステージの描画
	stage_->DrawStage3();
	// エネミーの描画
	enemyManager_->Draw();

	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}

void StageManager::ChangeStage(STAGE_TYPE type)
{
	Vector2F pos;
	pos.x = 64 * 2;
	pos.y = 64 * 10;
	stageType = type;
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		stage_->InitStage1();
		break;
	case STAGE_TYPE::STAGE2:
		player_->SetPlayerPos(pos);
		stage_->InitStage2();

		break;
	case STAGE_TYPE::STAGE3:
		player_->SetPlayerPos(pos);
		stage_->InitStage3();
		break;

	}
}