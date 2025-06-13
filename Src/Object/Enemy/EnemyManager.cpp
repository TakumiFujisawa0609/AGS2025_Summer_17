#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../Camera/Camera.h"
//#include "EnemyWater.h"
//#include "EnemyPlant.h"

void EnemyManager::Init(Camera*camera)
{
	camera_ = camera;



	enemyBase_ = new EnemyBase();
	enemyBase_->Init();

	enemyFire_ = new EnemyFire();
	enemyFire_->Init(camera_);
}

void EnemyManager::Update(void)
{
	enemyBase_->Update();
	enemyFire_->Update();
}

void EnemyManager::Draw(void)
{
	enemyBase_->Draw();
	enemyFire_->Draw();
}