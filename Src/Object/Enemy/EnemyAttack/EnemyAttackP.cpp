#include "EnemyAttackP.h"
#include "../EnemyPlant.h"
#include "../../Player/Player.h"
#include "../../Camera/Camera.h"

void EnemyAttackP::Init(EnemyPlant* enemyPlant, Player* player, Camera* camera)
{
    enemyPlant_ = enemyPlant;
    player_ = player;
    camera_ = camera;

    // 初期座標
    pos_.x = 100.0f;
    pos_.y = 100.0f;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/AttackP.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

    // アニメーションフレーム数カウント
    animFrame_ = 0;
    // アニメーションのカウンタ
    animCnt_ = 0;

    // 攻撃のクールダウン
    attackCnt_ = 50;

    // 攻撃中判定
    isAttack_ = false;

    // 再生中判定
    isAlive_ = false;

    // 再生折り返し判定
    isCntUp_ = true;
}

void EnemyAttackP::Update()
{

}

void EnemyAttackP::Draw()
{
    // 発見中のみ攻撃クールダウン消費
    if (enemyPlant_->GetFind())
    {
        attackCnt_++;
    }

    // アニメーション処理
    if (attackCnt_ >= ATTACK_INTERVAL && (isAttack_ || isAlive_))
    {
        isAlive_ = true;
        animCnt_++;
        if (animCnt_ <= ANIM_INTERVAL) {
            animCnt_ = 0;
            if (isCntUp_)
            {
                animFrame_++;
                if (animFrame_ <= ANIM_MAX) {
                    isCntUp_ = false;
                }
            }
            else
            {
                animFrame_++;
                if (animFrame_ >= ANIM_MAX) {
                    isCntUp_ = true;
                    isAlive_ = false;
                    isAttack_ = false;
                    attackCnt_ = 0;
                }
            }

        }
    }

    int enemySize = enemyPlant_->GetSizeX();
    bool enemyLeft = enemyPlant_->GetLeft();
    Vector2F enemyPos = enemyPlant_->GetPos();
    // カメラ座標
    Vector2 cameraPos = camera_->GetCameraPos();



    if (isAlive_ && enemyPlant_->GetAlive())
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

Vector2F EnemyAttackP::GetPos()
{
    return pos_;
}

void EnemyAttackP::SetPos(Vector2F pos)
{
    pos_ = pos;
}

int EnemyAttackP::GetSizeX()
{
    return SIZE_X;
}

int EnemyAttackP::GetSizeY()
{
    return SIZE_Y;
}

bool EnemyAttackP::GetAttack()
{
    return isAttack_;
}

void EnemyAttackP::SetAttack(bool isAttack)
{
    isAttack_ = isAttack;
}

bool EnemyAttackP::GetAlive()
{
    return isAlive_;
}

void EnemyAttackP::SetAlive(bool isAlive)
{
    isAlive_ = isAlive;
}