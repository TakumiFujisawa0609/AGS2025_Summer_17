#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "EnemyPlant.h"
#include "EnemyAttack/EnemyAttackF.h"
#include "EnemyAttack/EnemyAttackP.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
//#include "EnemyWater.h"
//#include "EnemyPlant.h"

void EnemyManager::Init(EnemyFire* enemyFire, EnemyPlant* enemyPlant, EnemyAttackF* enemyAttackF, EnemyAttackP* enemyAttackP, Player* player, Camera* camera, Stage* stage)
{
	enemyFire_ = enemyFire;
	enemyPlant_ = enemyPlant;
	enemyAttackF_ = enemyAttackF;
	enemyAttackP_ = enemyAttackP;
	player_ = player;
	camera_ = camera;
	stage_ = stage;

	collisionEnemy_ = false;
	
	/*enemyBase_ = new EnemyBase();
	enemyBase_->Init(player_, camera_, stage_);*/

	enemyFire_ = new EnemyFire();
	enemyFire_->Init(enemyFire_, enemyAttackF_, player_, camera_, stage_);
	enemyPlant_ = new EnemyPlant();
	enemyPlant_->Init(enemyPlant_, enemyAttackP_, player_, camera_, stage_);
}

void EnemyManager::Update()
{
	CollisionAttack();
	enemyBase_->Update();
	enemyFire_->Update();
	enemyPlant_->Update();

}

void EnemyManager::Draw()
{
	enemyBase_->Draw();
	enemyFire_->Draw();
	enemyPlant_->Draw();
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
