#include "EnemyFire.h"
#include "EnemyManager.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"

void EnemyFire::Init(Player* player, Camera* camera, Stage* stage)
{
    player_ = player;
    camera_ = camera;
    stage_ = stage;

    int stageId = stage_->GetStageId();
    
    pos_.x = 2460.0f;
    pos_.y = 352.0f;

    isAlive_ = true;
    isAttack_ = false;
    isLeft_ = true;
    isFind_ = false;

    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyF.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

    attackCnt_ = 0;

    animFrame_ = 0;
    animCnt_ = 0;
    animInterval_ = ANIM_INTERVAL;

}

void EnemyFire::Update()
{
    Attack();
    Move();

    Vector2F playerPos = player_->GetPlayerPos();
    if (isAlive_)
    {
        // ˆê’è”ÍˆÍ‚É“ü‚Á‚½‚çtrue
        if (!(playerPos.x < pos_.x - FIND_SIZE || playerPos.x > pos_.x + FIND_SIZE) && !(playerPos.y < pos_.y - FIND_SIZE || playerPos.y > pos_.y + FIND_SIZE))
        {
            isFind_ = true;
        }
        else
        {
            isFind_ = false;
        }

        animCnt_++;
        if (animCnt_ >= animInterval_) {
            animCnt_ = 0;
            animFrame_++;
            if (animFrame_ >= ANIM_MAX) {
                animFrame_ = 0;
            }
        }
    }
}

void EnemyFire::Draw()
{

    Vector2F playerPos = player_->GetPlayerPos();
    Vector2 cameraPos = camera_->GetCameraPos();

    if (isAlive_)
    {
        if (isFind_)
        {
            if (playerPos.x <= pos_.x)
            {
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, true);
            }
            else
            {
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, false);
            }
        }
        else
        {
            if (isLeft_)
            {
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, true);
            }
            else
            {
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, false);
            }
        }
    }
}

void EnemyFire::Attack()
{

}

void EnemyFire::Move()
{
    if (isAlive_)
    {
        if (!isFind_)
        {
            moveCnt_++;
            if (moveCnt_ < MOVE_MAX)
            {
                pos_.x -= MOVE_SPEED;
                isLeft_ = true;
            }
            else if (moveCnt_ < MOVE_MAX * 2)
            {
                pos_.x += MOVE_SPEED;
                isLeft_ = false;
            }
            else
            {
                moveCnt_ = 0;
            }
        }
    }
}
