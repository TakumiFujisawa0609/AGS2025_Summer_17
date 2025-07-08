#include "EnemyManager.h"
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "EnemyPlant.h"
#include "EnemyWater.h"
#include "EnemyAttack/EnemyAttackF.h"
#include "EnemyAttack/EnemyAttackP.h"
#include "EnemyAttack/EnemyAttackW.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "../Attack/Blast.h"
#include "../Attack/Plants.h"
#include "../Attack/Water.h"

void EnemyManager::Init(EnemyFire* enemyFire, EnemyPlant* enemyPlant, EnemyWater* enemyWater,
	EnemyAttackF* enemyAttackF, EnemyAttackP* enemyAttackP, EnemyAttackW* enemyAttackW,
	Player* player, Camera* camera, Stage* stage, Blast* blast, Plants* plants, Water* water)
{
	enemyFire_ = enemyFire;
	enemyPlant_ = enemyPlant;
	enemyWater_ = enemyWater;
	enemyAttackF_ = enemyAttackF;
	enemyAttackP_ = enemyAttackP;
	enemyAttackW_ = enemyAttackW;
	player_ = player;
	camera_ = camera;
	stage_ = stage;
	blast_ = blast;
	plants_ = plants;
	water_ = water;

	collisionEnemy_ = false;

	/*enemyBase_ = new EnemyBase();
	enemyBase_->Init(player_, camera_, stage_);*/

	enemyFire_ = new EnemyFire();
	enemyFire_->Init(enemyFire_, enemyAttackF_, player_, camera_, stage_, blast_, plants_, water_);
	enemyPlant_ = new EnemyPlant();
	enemyPlant_->Init(enemyPlant_, enemyAttackP_, player_, camera_, stage_, blast_, plants_, water_);
	enemyWater_ = new EnemyWater();
	enemyWater_->Init(enemyWater_, enemyAttackW_, player_, camera_, stage_, blast_, plants_, water_);
}

void EnemyManager::Update()
{
	CollisionAttack();
	enemyBase_->Update();
	enemyFire_->Update();
	enemyPlant_->Update();
	enemyWater_->Update();

}

void EnemyManager::Draw()
{
	enemyBase_->Draw();
	enemyFire_->Draw();
	enemyPlant_->Draw();
	enemyWater_->Draw();
}

void EnemyManager::CollisionAttack()
{
	// エネミーの消灯判定取得
	fireCollision_ = enemyFire_->GetCollisionFire();
	plantCollision_ = enemyPlant_->GetCollisionPlant();
	waterCollision_ = enemyWater_->GetCollisionWater();

	// falseになったらエネミーの衝突判定もfalseになる
	if (!collisionEnemy_)
	{
		enemyFire_->SetCollisionFire(false);
		enemyPlant_->SetCollisionPlant(false);
		enemyWater_->SetCollisionWater(false);
	}

	// どれかと衝突したらtrue
	if (fireCollision_ || plantCollision_ || waterCollision_)
	{
		player_->DownHp(20);
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
