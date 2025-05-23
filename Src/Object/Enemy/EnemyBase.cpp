#include "EnemyBase.h"
#include "../Camera/Camera.h"
#include "../../Application.h"
#include <DxLib.h>

void EnemyBase::Init() {
    pos_.x = 100.0f;
    pos_.y = 100.0f;
    attackCnt_ = 0;
    isAlive_ = false;
    isAttack_ = false;
    img_ = LoadGraph("Data/Image/Stage/Map1.png"); // ‰æ‘œ‰¼
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
}

void EnemyBase::Move()
{
}

void EnemyBase::Attack()
{
}