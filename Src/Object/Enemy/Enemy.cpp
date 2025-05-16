#include <DxLib.h>
#include "Enemy.h"

void Enemy::Init()
{
	// 座標
	pos_ = INIT_POS;
	// 攻撃のクールダウンカウント
	attackCnt_ = 0;
	// 生存判定
	isAlive_ = true;
	// 攻撃中判定
	isAttack_ = false;

	// 画像読み込み(仮)
	img_ = LoadGraph("Data/Image/Stage/Map1.png");
}

void Enemy::Update()
{
	Move();
	if (isAlive_) {
		attackCnt_++;
	}
}

void Enemy::Draw()
{
	if (isAlive_) {
		DrawGraph(pos_.x, pos_.y, img_, true);
	}
}

void Enemy::Move()
{
	if (isAlive_ && !isAttack_) {
		pos_.x += MOVE_SPEED;
	}
}

void Enemy::Attack()
{
	if (isAlive_ && isAttack_) {
		// 攻撃処理
	}
}