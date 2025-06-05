#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
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
	enemyManager_ = new EnemyManager();
	// ステージ
	stage_ = new Stage();
	// ステージ
	stage_ = new Stage();
	// カメラ
	camera_ = new Camera();
	// 壁
	wall_ = new Wall();
	//攻撃
	//爆発
	blast_ = new Blast();
	//植物
	plants_ = new Plants();
	//水
	water_ = new Water();


	backImg_ = LoadGraph((Application::PATH_IMAGE + "Scene/BackBue.png").c_str());

	player_->Init(camera_, stage_, wall_, blast_, water_, plants_);
	stage_->Init(this, player_, camera_);
	camera_->Init(player_, this);
	enemyManager_->Init();

	//enemy_->Init();
	wall_->Init(camera_);





	blast_->Init(camera_);
	water_->Init(camera_);
	plants_->Init(camera_);
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
	enemyManager_->Update();

	// カメラの更新
	camera_->Update();

	// 壁の更新
	wall_->Update();
	blast_->Update();
	water_->Update();
	plants_->Update();

	/*if (ins.IsTrgDown(KEY_INPUT_N))
	{
		Vector2 pos;
		pos.x = 100;
		pos.y = 100;

		blast_->SetBlastPos(pos);
		blast_->SetIsBlast(true);

	}
	if (ins.IsTrgDown(KEY_INPUT_Z))
	{
		Vector2 pos;
		pos.x = 100;
		pos.y = 100;

		water_->CreateEffect(pos);


	}
	if (ins.IsTrgDown(KEY_INPUT_V))
	{
		Vector2 pos;
		pos.x = 100;
		pos.y = 100;

		
		plants_->SetPlantsPos(pos);
		plants_->SetIsPlants(true);
	}*/
	// シーン遷移
	if (player_->GetPlayerPos().x>64 * 78)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}

}

void GameScene::Draw(void)
{

	//背景の描画
	DrawGraph(0, 0, backImg_, true);
	
	// ステージの描画
	stage_->Draw();

	// プレイヤーの描画
	player_->Draw();

	//壁の描画
	wall_->Draw();
	
	// ステージの描画
	stage_->Draw();
	
	// エネミーの描画
	enemyManager_->Draw();

	blast_->Draw();
	water_->Draw();
	plants_->Draw();

	
#ifdef _DEBUG
	DrawFormatString(0, 0, 0x000000, "GameScene");



#endif // DEBUG

}

void GameScene::Release()
{
	delete plants_;
	delete stage_;
	delete wall_;
	delete camera_;
	blast_->Release();
	delete blast_;
	water_->Release();
	delete water_;
	plants_->Release();
	delete plants_;
}
