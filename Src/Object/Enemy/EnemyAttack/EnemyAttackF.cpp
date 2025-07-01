#include "EnemyAttackF.h"
#include "../EnemyFire.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"

void EnemyAttackF::Init(EnemyFire* enemyFire, Player* player, Camera* camera)
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
    // アニメーションの進行間隔
    animInterval_ = 8;

    // 攻撃のクールダウン
    attackCnt_ = 50;

    // 攻撃中判定
    isAttack_ = false;

    // 再生中判定
    isAlive_ = false;

    // 再生折り返し判定
    isCntDown_ = true;
}

void EnemyAttackF::Update()
{

}

void EnemyAttackF::Draw()
{
    // 発見中のみ攻撃クールダウン消費
    if (enemyFire_->GetFind())
    {
        attackCnt_++;
    }

    if (animFrame_ == 0)
    {
        animInterval_ = 60;
    }
    else
    {
        animInterval_ = 8;
    }

    // アニメーション処理
    if (attackCnt_ >= ATTACK_INTERVAL && (isAttack_ || isAlive_))
    {
        isAlive_ = true;
        animCnt_++;
        if (animCnt_ >= animInterval_) {
            animCnt_ = 0;
            if (isCntDown_)
            {
                animFrame_--;
                if (animFrame_ <= 0) {
                    isCntDown_ = false;
                }
            }
            else if (animFrame_ == 0)
            {
                animInterval_ = 45;
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

#ifdef _DEBUG

    // エネミーの攻撃当たり判定描画
    if (isAlive_)
    {
        //// 当たり判定用座標
        DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0x000000, false);
    }

#endif // _DEBUG
}

Vector2F EnemyAttackF::GetPos()
{
    return pos_;
}

void EnemyAttackF::SetPos(Vector2F pos)
{
    pos_ = pos;
}

int EnemyAttackF::GetSizeX()
{
    return SIZE_X;
}

int EnemyAttackF::GetSizeY()
{
    return SIZE_Y;
}

bool EnemyAttackF::GetAttack()
{
    return isAttack_;
}

void EnemyAttackF::SetAttack(bool isAttack)
{
    isAttack_ = isAttack;
}

bool EnemyAttackF::GetAlive()
{
    return isAlive_;
}

void EnemyAttackF::SetAlive(bool isAlive)
{
    isAlive_ = isAlive;
}