#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
//#include "EnemyWater.h"
//#include "EnemyPlant.h"

void EnemyManager::Init(void)
{
	enemyBase_ = new EnemyBase();
	enemyBase_->Init();

	enemyFire_ = new EnemyFire();
	enemyFire_->Init();
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