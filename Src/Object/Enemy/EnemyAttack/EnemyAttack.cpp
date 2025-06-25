#include "EnemyAttack.h"
#include "../EnemyFire.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"
#include <DxLib.h>

void EnemyAttack::Init(EnemyFire* enemyFire, Player* player, Camera* camera)
{
    enemyFire_ = enemyFire;
    player_ = player;
    camera_ = camera;

    // 初期座標
    pos_.x = 100.0f;
    pos_.y = 100.0f;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/AttackF.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

    // アニメーションフレーム数カウント
    animFrame_ = 4;
    // アニメーションのカウンタ
    animCnt_ = 0;

    // 攻撃のクールダウン
    attackCnt_ = 50;

    // 攻撃中判定
    isAttack_ = false;

    // 再生中判定
    isAlive_ = false;

    // 再生折り返し判定
    isCntDown_ = true;
}

void EnemyAttack::Update()
{

}

void EnemyAttack::Draw()
{
    // 発見中のみ攻撃クールダウン消費
    if (enemyFire_->GetFind())
    {
        attackCnt_++;
    }

    // アニメーション処理
    if (attackCnt_ >= ATTACK_INTERVAL && (isAttack_ || isAlive_))
    {
        isAlive_ = true;
        animCnt_++;
        if (animCnt_ >= ANIM_INTERVAL) {
            animCnt_ = 0;
            if (isCntDown_)
            {
                animFrame_--;
                if (animFrame_ <= 0) {
                    isCntDown_ = false;
                }
            }
            else
            {
                animFrame_++;
                if (animFrame_ >= ANIM_MAX) {
                    isCntDown_ = true;
                    isAlive_ = false;
                    isAttack_ = false;
                    attackCnt_ = 0;
                }
            }

        }
    }

    int enemySize = enemyFire_->GetSizeX();
    bool enemyLeft = enemyFire_->GetLeft();
    Vector2F enemyPos = enemyFire_->GetPos();
    // カメラ座標
    Vector2 cameraPos = camera_->GetCameraPos();

    if (isAlive_ && enemyFire_->GetAlive())
    {
        if (enemyLeft)
        {
            pos_.x = enemyPos.x - SIZE_X + enemySize / 2 - cameraPos.x;
            pos_.y = enemyPos.y - cameraPos.y;
            // 左向きに描画
            DrawRotaGraphF(pos_.x, pos_.y, 1.0f, 0.0f, Array_[animFrame_], true, false);
        }
        else
        {
            pos_.x = enemyPos.x + enemySize - cameraPos.x;
            pos_.y = enemyPos.y - cameraPos.y;
            // 右向きに描画
            DrawRotaGraphF(pos_.x, pos_.y, 1.0f, 0.0f, Array_[animFrame_], true, true);
        }
    }
}

bool EnemyAttack::GetAttack()
{
    return isAttack_;
}

void EnemyAttack::SetAttack(bool isAttack)
{
    isAttack_ = isAttack;
}

bool EnemyAttack::GetAlive()
{
    return isAlive_;
}
