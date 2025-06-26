#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "EnemyAttack/EnemyAttack.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
//#include "EnemyWater.h"
//#include "EnemyPlant.h"

void EnemyManager::Init(EnemyAttack* enemyAttack, EnemyFire* enemyFire, Player* player, Camera* camera, Stage* stage)
{
	enemyAttack_ = enemyAttack;
	enemyFire_ = enemyFire;
	player_ = player;
	camera_ = camera;
	stage_ = stage;

	collisionEnemy_ = false;
	
	/*enemyBase_ = new EnemyBase();
	enemyBase_->Init(player_, camera_, stage_);*/

	enemyFire_ = new EnemyFire();
	enemyFire_->Init(enemyAttack_, enemyFire_, player_, camera_, stage_);
}

void EnemyManager::Update()
{
	CollisionAttack();
	enemyBase_->Update();
	enemyFire_->Update();

}

void EnemyManager::Draw()
{
	enemyBase_->Draw();
	enemyFire_->Draw();
}

void EnemyManager::CollisionAttack()
{
	fireCollision_ = enemyFire_->GetCollisionFire();
	if (fireCollision_)
	{
		collisionEnemy_ = true;
	}
	else
	{
		collisionEnemy_ = false;
		enemyFire_->SetCollisionFire(false);
	}
}

bool EnemyManager::GetCollisionEnemy()
{
	return collisionEnemy_;
}

void EnemyManager::SetCollisionEnemy(bool collisionEnemy)
{
	collisionEnemy_ = collisionEnemy;
}
