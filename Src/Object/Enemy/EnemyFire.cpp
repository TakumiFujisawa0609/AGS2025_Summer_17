#include "EnemyFire.h"
#include "EnemyManager.h"
#include "../Camera/Camera.h"
#include <DxLib.h>

void EnemyFire::Init(Camera*camera)
{
    //6Vector2 cameraPos = camera_->GetCameraPos();

    pos_.x = 1500.0f;
    pos_.y = 544.0f;

    isAlive_ = false;

    isAttack_ = false;

    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyF.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

    attackCnt_ = 0;

    animFrame_ = 0;
    animCounter_ = 0;
    animInterval_ = ANIM_INTERVAL;
}

void EnemyFire::Update()
{

    if (isAlive_)
    {
        animCounter_++;
        if (animCounter_ >= animInterval_) {
            animCounter_ = 0;
            animFrame_++;
            if (animFrame_ >= ANIM_MAX) {
                animFrame_ = 0;
            }
        }
    }
}

void EnemyFire::Draw()
{
    if (isAlive_)
    {
        DrawRotaGraphF(pos_.x, pos_.y, 1.0f, 0.0f, Array_[animFrame_], true, true);
    }
}