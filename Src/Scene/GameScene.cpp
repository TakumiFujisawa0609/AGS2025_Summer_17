#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/StageManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyFire.h"
#include "../Object/Enemy/EnemyPlant.h"
#include "../Object/Enemy/EnemyAttack/EnemyAttackF.h"
#include "../Object/Enemy/EnemyAttack/EnemyAttackP.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Wall/Wall.h"
#include "../Object/Attack/Blast.h"
#include "../Object/Attack/Plants.h"
#include "../Object/Ui/PlayerUi.h"
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
	enemyFire_ = new EnemyFire();
	enemyPlant_ = new EnemyPlant();
	enemyAttackF_ = new EnemyAttackF();
	enemyAttackP_ = new EnemyAttackP();
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

	stageManager_ = new StageManager();

	playerUi_ = new PlayerUi();


	backImg_ = LoadGraph((Application::PATH_IMAGE + "Scene/BackBue.png").c_str());


	player_->Init(camera_, stage_, wall_, blast_, water_, plants_);
	stage_->Init(player_, camera_);
	camera_->Init(player_);
	enemyManager_->Init(enemyFire_, enemyPlant_, enemyAttackF_, enemyAttackP_, player_, camera_, stage_);

	//enemy_->Init();
	wall_->Init(camera_);

	playerUi_->Init(player_);

	stageManager_->Init(player_, enemyManager_, enemyFire_, stage_, camera_, wall_, blast_, plants_, water_);



	blast_->Init(camera_);
	water_->Init(camera_);
	plants_->Init(camera_);
	

	//スクリーン系
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	screenShakeInterevalCount_ = 0;
	screenShakePos_ = SHAKE_WIDTH;
}

void GameScene::Update(void)
{

	//ストップ処理・振動処理
	if (hitStopCnt_ > 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		++screenShakeInterevalCount_;
		if (SCREEN_SHAKE_INTERVAL_COUNT <= screenShakeInterevalCount_)
		{
			screenShakeInterevalCount_ = 0;
			//右揺れ
			if (screenShakePos_ == SHAKE_WIDTH)
			{
				screenShakePos_ = -SHAKE_WIDTH;
			}
			//左揺れ
			else if (screenShakePos_ == -SHAKE_WIDTH)
			{
				screenShakePos_ = SHAKE_WIDTH;
			}

		}
		DrawGraph(screenShakePos_, screenShakePos_, tmpScreen_, true);
		hitStopCnt_--;
		return;
	}


	// 入力の更新
	InputManager& ins = InputManager::GetInstance();

	stageManager_->Update();

	playerUi_->Update();

	//// ステージの更新
	//stage_->Update();

	//// プレイヤーの更新
	//player_->Update();

	//// エネミーの更新
	//enemyManager_->Update();

	//// カメラの更新
	//camera_->Update();

	//// 壁の更新
	//wall_->Update();
	//blast_->Update();
	//water_->Update();
	//plants_->Update();

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
	/*if (player_->GetPlayerPos().x>64 * 78)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
	}*/

}

void GameScene::Draw(void)
{
	SetDrawScreen(tmpScreen_);

	stageManager_->Draw();
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(screenShakePos_, screenShakePos_, tmpScreen_, true);

	stageManager_->Draw();
	playerUi_->Draw();
	SetFontSize(32);
	DrawFormatString(1650, 0, 0xFFFFFF, "ESCでメニュー");
	SetFontSize(16);
	//// ステージの描画
	//stage_->Draw();

	//// プレイヤーの描画
	//player_->Draw();

	////壁の描画
	//wall_->Draw();
	//
	//// ステージの描画
	//stage_->Draw();
	//
	//// エネミーの描画
	//enemyManager_->Draw();

	//blast_->Draw();
	//water_->Draw();
	//plants_->Draw();

	
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
	delete enemyManager_;

	
}

int GameScene::GetHitStop()
{
	return hitStopCnt_;
}

void GameScene::SetHitStop(int cnt)
{
	hitStopCnt_ = cnt;
}
