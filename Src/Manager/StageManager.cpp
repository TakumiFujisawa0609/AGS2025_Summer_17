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
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:

		break;
	case STAGE_TYPE::STAGE2:

		break;
	case STAGE_TYPE::STAGE3:

		break;

	}
}

void StageManager::Draw()
{
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:

		break;
	case STAGE_TYPE::STAGE2:

		break;
	case STAGE_TYPE::STAGE3:

		break;

	}

}

void StageManager::ChangeStage(STAGE_TYPE type)
{
	stageType = type;
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		stage_->InitStage1();
		break;
	case STAGE_TYPE::STAGE2:
		stage_->InitStage2();
		break;
	case STAGE_TYPE::STAGE3:
		stage_->InitStage3();
		break;

	}
}