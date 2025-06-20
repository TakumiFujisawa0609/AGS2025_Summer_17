#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
//#include "EnemyWater.h"
//#include "EnemyPlant.h"

void EnemyManager::Init(Player* player, Camera* camera, Stage* stage)
{
	player_ = player;
	camera_ = camera;
	stage_ = stage;

	/*enemyBase_ = new EnemyBase();
	enemyBase_->Init(player_, camera_, stage_);*/

	enemyFire_ = new EnemyFire();
	enemyFire_->Init(player_, camera_, stage_);
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