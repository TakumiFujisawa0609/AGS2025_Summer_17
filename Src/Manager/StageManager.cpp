#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Common/Fader.h"
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Common/Vector2F.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Enemy/EnemyFire.h"
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
void StageManager::Init(Player* player, EnemyManager* enemyManager, EnemyFire* enemyFire, Stage* stage, Camera* camera, Wall* wall, Blast* blast, Plants* plants, Water* water)
{
	player_ = player;
	enemyManager_ = enemyManager;
	enemyFire_ = enemyFire;
	stage_ = stage;
	camera_ = camera;
	wall_ = wall;
	blast_ = blast;
	plants_ = plants;
	water_ = water;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	stageType = STAGE_TYPE::STAGE1;

	nextStageType = STAGE_TYPE::NONE;

	Img_ = LoadDivGraph("Data/Image/Stage/Doa.png", 3, 3, 1, 64 * 4, 64 * 2, doaImg_);

	backImg_ = LoadGraph((Application::PATH_IMAGE + "Scene/BackBue.png").c_str());
	back3Img_ = LoadGraph((Application::PATH_IMAGE + "Scene/StarSky.jpg").c_str());
		
	//BackSoundHandle3_ = LoadSoundMem("Data/Sound/BGM//BackSound3.mp3");

	BackSoundHandle_ = LoadSoundMem("Data/Sound/BGM/BackSound.mp3");
	
	
	closeSoundHandle_ = LoadSoundMem("Data/Sound/SE/Close.mp3");

	//if (BackSoundHandle3_ == -1) {
	//	printfDx("BackSound3.mp3のロードに失敗しました\n");
	//}
	back3Img_ = LoadGraph((Application::PATH_IMAGE + "Scene/rock.png").c_str());

	isChange_ = false;
	changeCnt_ = 0;
	animCnt_ = 0;
}
void StageManager::Update()
{
	// カメラの更新
	camera_->Update();
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{

		
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
	if (player_->GetHp() <= 0)
	{
		StopSoundMem(BackSoundHandle_);
		DeleteSoundMem(BackSoundHandle_);
		DeleteSoundMem(closeSoundHandle_);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}

}
void StageManager::Update1()
{

	
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage1();

	
	
	// 壁の更新
	wall_->Update1();
	blast_->Update();
	water_->Update();
	plants_->Update();
	// シーン遷移
	if (player_->GetPlayerPos().x > 64 * 78)
	{
		
		isChange_ = true;
		if (isChange_ == true)
		{
			changeCnt_++;
			if (changeCnt_ >= 60)
			{
				
				ChangeStage(STAGE_TYPE::STAGE2);
			}
		}

	}
	else
	{
		player_->Update();
	}
	
}
void StageManager::Update2()
{

	
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage2();

	

	// エネミーの更新
	enemyManager_->Update();
	blast_->Update();
	water_->Update();
	plants_->Update();
	
	if (player_->GetPlayerPos().x > 64 * 90)
	{
		isChange_ = true;
		if (isChange_ == true)
		{
			changeCnt_++;
			if (changeCnt_ >= 60)
			{
				ChangeStage(STAGE_TYPE::STAGE3);
			}
		}

	}
	else
	{
		player_->Update();
	}
	
}
void StageManager::Update3()
{
	// 入力の更新
	InputManager& ins = InputManager::GetInstance();
	// ステージの更新
	stage_->UpdateStage3();

	// プレイヤーの更新
	

	// エネミーの更新
	enemyManager_->Update();

	wall_->Update2();
	blast_->Update();
	water_->Update();
	plants_->Update();
	if (player_->GetPlayerPos().x > 64 * 97&& player_->GetPlayerPos().y<64*12)
	{
		isChange_ = true;
		if (isChange_ == true)
		{
			changeCnt_++;
			if (changeCnt_ >= 60)
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::CLEAR);
			}
		}
		
	}
	else
	{
		player_->Update();
	}
	
	
}

void StageManager::Draw()
{
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	
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
	
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	// 暗転・明転
	fader_->Draw();
}
void StageManager::Draw1()
{
	if (CheckSoundMem(BackSoundHandle_) == 0) {
		PlaySoundMem(BackSoundHandle_, DX_PLAYTYPE_LOOP);
	}

	DrawGraph(0, 0, backImg_, true);
	//壁の描画
	wall_->Draw1();
	
	
	

	// ステージの描画
	stage_->DrawStage1();
	if (isChange_ == false)
	{
		PlaySoundMem(closeSoundHandle_, DX_PLAYTYPE_BACK);
		DrawGraph(64 * 76 - camera_->GetCameraPos().x, 64 * 9 - camera_->GetCameraPos().y, doaImg_[0], true);
		
	}
	// プレイヤーの描画
	player_->Draw();
	if (isChange_ == true)
	{
		DrawGraph(64 * 76 - camera_->GetCameraPos().x, 64 * 9 - camera_->GetCameraPos().y, doaImg_[2], true);
	}
	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}
void StageManager::Draw2()
{
	
	DrawGraph(0, 0, backImg_, true);

	////壁の描画
	//wall_->Draw();
	
	

	// ステージの描画
	stage_->DrawStage2();

	
	if (isChange_ == false)
	{
		
		PlaySoundMem(closeSoundHandle_, DX_PLAYTYPE_BACK);
		DrawGraph(64 * 88 - camera_->GetCameraPos().x, 64 * 9 - camera_->GetCameraPos().y, doaImg_[0], true);
	}
	// プレイヤーの描画
	player_->Draw();
	if (isChange_ == true)
	{
		DrawGraph(64 * 88 - camera_->GetCameraPos().x, 64 * 9 - camera_->GetCameraPos().y, doaImg_[2], true);
	}

	// エネミーの描画
	enemyManager_->Draw();

	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}
void StageManager::Draw3()
{
	StopSoundMem(BackSoundHandle_);
	if (CheckSoundMem(BackSoundHandle3_) == 0) {
		PlaySoundMem(BackSoundHandle3_, DX_PLAYTYPE_LOOP);
	}
	DrawGraph( 0, 0,back3Img_, true);
	//壁の描画
	wall_->Draw2();
	
	

	// ステージの描画
	stage_->DrawStage3();

	
	if (isChange_ == false)
	{
		PlaySoundMem(closeSoundHandle_, DX_PLAYTYPE_BACK);
		DrawGraph(64 * 95 - camera_->GetCameraPos().x, 64 * 10 - camera_->GetCameraPos().y, doaImg_[0], true);
	}
	// プレイヤーの描画
	player_->Draw();
	if (isChange_ == true)
	{
		DrawGraph(64 * 95 - camera_->GetCameraPos().x, 64 * 10 - camera_->GetCameraPos().y, doaImg_[2], true);
	}

	// エネミーの描画
	enemyManager_->Draw();

	blast_->Draw();
	water_->Draw();
	plants_->Draw();
}

void StageManager::ChangeStage(STAGE_TYPE type)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	nextStageType = type;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;

}

void StageManager::DoChangeStage(STAGE_TYPE type)
{
	Vector2F pos;
	pos.x = 64 * 2;
	pos.y = 64 * 10;
	stageType = type;
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		isChange_ = false;
		stage_->InitStage1();
		wall_->Init1();
		break;
	case STAGE_TYPE::STAGE2:
		isChange_ = false;
		player_->SetPlayerPos(pos);
		stage_->InitStage2();
		break;
	case STAGE_TYPE::STAGE3:
		isChange_ = false;
		player_->SetPlayerPos(pos);
		stage_->InitStage3();

		wall_->Init2();
		break;

	}
	nextStageType = STAGE_TYPE::NONE;
}
void StageManager::Fade(void)
{

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			// 完全に暗転してからシーン遷移
			DoChangeStage(nextStageType);
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}