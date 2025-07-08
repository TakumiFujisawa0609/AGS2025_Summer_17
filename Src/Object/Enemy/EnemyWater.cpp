#include "EnemyWater.h"
#include "EnemyManager.h"
#include "EnemyAttack/EnemyAttackW.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "../Attack/Blast.h"
#include "../Attack/Plants.h"
#include "../Attack/Water.h"

void EnemyWater::Init(EnemyWater* enemyWater, EnemyAttackW* enemyAttackW, Player* player, Camera* camera, Stage* stage, Blast* blast, Plants* plants, Water* water)
{
    enemyAttackW_ = enemyAttackW;
    enemyWater_ = enemyWater;
    player_ = player;
    camera_ = camera;
    stage_ = stage;
    blast_ = blast;
    plants_ = plants;
    water_ = water;

    // 初期化用変数
    setInit_ = 2;

    // 属性管理用
    fireCr_ = 0xff0000;
    plantCr_ = 0x00ff00;
    waterCr_ = 0x0000ff;
    normalCr_ = 0xffffff;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyW.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);
}

void EnemyWater::InitStage2()
{
    // ステージ2
    if (setInit_ == 2)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 2)
        {
            // 初期座標

            pos_.x = 4394.0f;

            pos_.x = 4426.0f;

            pos_.y = 640.0f;

            // 移動速度
            moveSpeed_ = 0.8f;

            moveMax_ = 150;

            moveMax_ = 210;


            // 索敵範囲
            findSize_ = 300.0f;

            // 生存判定
            isAlive_ = true;
            // 攻撃中判定
            isAttack_ = false;
            // 左右判定(trueなら左向き)
            isLeft_ = true;
            // 発見中判定(trueなら発見中)
            isFind_ = false;
            // プレイヤー攻撃ヒット済み判定
            wasHit_ = false;
            // プレイヤーの攻撃とエネミーの衝突判定
            collisionDamage_ = false;
            // エネミー(エネミーの攻撃)とプレイヤーの衝突判定
            collisionWater_ = false;
            // 無敵判定
            isInvincible_ = false;
            // 無敵時描画判定
            isVisible_ = true;

            // アニメーションフレーム数カウント
            animFrame_ = WALK_ANIM_MIN;
            // アニメーションのカウンタ
            animCnt_ = 0;

            // 攻撃
            attackCnt_ = 0;
            attackPosX_ = 0.0f;
            attackPosY_ = 0.0f;
            attackSpeed_ = 4.0f;
            attackMax_ = 150.0f;
            attackInterval_ = 110;

            attackSize1_ = 10.0f;
            attackSize2_ = 15.0f;
            attackSize3_ = 20.0f;
            attackSize4_ = 26.0f;
            attackSize5_ = 32.0f;

            // エネミー座標取得済み判定
            isGetPos_ = false;
            // 攻撃中判定
            isAttackAlive_ = false;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // HP
            hp_ = 25.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 無敵時間
            invincibleMax_ = 45;
            // 無敵時間のカウント
            invincibleCnt_ = 0;

            // 初期化用変数
            setInit_ = 3;
        }
    }
}

void EnemyWater::InitStage3()
{
    // ステージ3
    if (setInit_ == 3)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 3)
        {
            pos_.x = 2976.0f;
            pos_.y = 1260.8f;

            // 移動速度
            moveSpeed_ = 0;
            moveMax_ = 0;

            // 索敵範囲
            findSize_ = 1000.0f;

            // 生存判定
            isAlive_ = true;
            // 攻撃中判定
            isAttack_ = false;
            // 左右判定(trueなら左向き)
            isLeft_ = true;
            // 発見中判定(trueなら発見中)
            isFind_ = false;
            // プレイヤー攻撃ヒット済み判定
            wasHit_ = false;
            // プレイヤーの攻撃とエネミーの衝突判定
            collisionDamage_ = false;
            // エネミー(エネミーの攻撃)とプレイヤーの衝突判定
            collisionWater_ = false;
            // 無敵判定
            isInvincible_ = false;
            // 無敵時描画判定
            isVisible_ = true;

            // アニメーションフレーム数カウント
            animFrame_ = WALK_ANIM_MIN;
            // アニメーションのカウンタ
            animCnt_ = 0;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // 攻撃
            attackCnt_ = 0;
            attackPosX_ = 0.0f;
            attackPosY_ = 0.0f;
            attackSpeed_ = 10.0;
            attackMax_ = 90.0f;
            attackInterval_ = 80;

            attackSize1_ = 10.0f;
            attackSize2_ = 20.0f;
            attackSize3_ = 32.0f;
            attackSize4_ = 45.0f;
            attackSize5_ = 64.0f;

            // エネミー座標取得済み判定
            isGetPos_ = false;
            // 攻撃中判定
            isAttackAlive_ = false;

            // HP
            hp_ = 45.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 無敵時間
            invincibleMax_ = 80;
            // 無敵時間のカウント
            invincibleCnt_ = 0;

            // 初期化用変数
            setInit_ = 0;
        }
    }
}

void EnemyWater::Update()
{
    InitStage2();
    InitStage3();
    Move();
    Attack();
    CollisionPlayerAttack();
    CollisionEnemyAttack();
    Damage();
    InvincibleWater();

    // プレイヤー座標
    Vector2F playerPos = player_->GetPlayerPos();

    if (isAlive_)
    {
        // 一定範囲(正方形)に入ったらtrue
        if (!(playerPos.x < pos_.x - findSize_ || playerPos.x > pos_.x + findSize_) &&
            !(playerPos.y < pos_.y - findSize_ || playerPos.y > pos_.y + findSize_))
        {
            // 発見中
            isFind_ = true;
            isAttack_ = true;
        }
        else
        {
            // 発見中でない
            isFind_ = false;
            isAttack_ = true;
        }
    }

#ifdef _DEBUG

    // 再出現(デバッグ用)
    if (CheckHitKey(KEY_INPUT_M))
    {
        hp_ = 45.0f;
        isAlive_ = true;
        collisionWater_ = false;
    }

#endif // DEBUG
}

void EnemyWater::Draw()
{
    Attack();

    // プレイヤー座標
    Vector2F playerPos = player_->GetPlayerPos();
    // カメラ座標
    Vector2 cameraPos = camera_->GetCameraPos();

#ifdef _DEBUG

    // プレイヤー当たり判定円描画
    DrawCircle(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y, 32, (0x000000), false);
    // エネミー当たり判定円描画
    DrawCircle(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 32, (0x000000), false);

#endif // _DEBUG

    // アニメーション処理
    if (isAttackAlive_)
    {
        animFrame_ = ATTACK_ANIM;
    }
    else
    {
        animCnt_++;
        if (animCnt_ >= ANIM_INTERVAL) {
            animCnt_ = 0;
            animFrame_++;
            if (animFrame_ > WALK_ANIM_MAX) {
                animFrame_ = WALK_ANIM_MIN;
            }
        }
    }

    if (isAlive_ && isVisible_)
    {
        // 発見中
        if (isFind_)
        {
            // プレイヤーがエネミーの左にいるか
            if (playerPos.x <= pos_.x)
            {
                // 左向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!isAttackAlive_)
                {
                    isLeft_ = true;
                }
            }
            else
            {
                // 右向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!isAttackAlive_)
                {
                    isLeft_ = false;
                }

            }
        }
        // 発見中でない
        else
        {
            // 左を向いているか
            if (isLeft_)
            {
                // 左向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, true);
            }
            else
            {
                // 右向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, false);
            }
        }
    }
}

void EnemyWater::Move()
{
    if (isAlive_ && !isAttackAlive_)
    {
        // 発見中でないなら動かす
        if (!isFind_)
        {
            moveCnt_++;
            // 左へ移動
            if (moveCnt_ < moveMax_)
            {
                pos_.x -= moveSpeed_;
                isLeft_ = true;
            }
            // 右へ移動
            else if (moveCnt_ < moveMax_ * 2)
            {
                pos_.x += moveSpeed_;
                isLeft_ = false;
            }
            // 往復したのでカウンタをリセット
            else
            {
                moveCnt_ = 0;
            }
        }
    }
}


void EnemyWater::Attack()
{
    Vector2 cameraPos = camera_->GetCameraPos();
    // 発見中のみ攻撃クールダウン消費
    if (isFind_ && isAlive_)
    {
        attackCnt_++;
    }
    // アニメーション処理
    if (attackCnt_ >= attackInterval_)
    {
        isAttackAlive_ = true;
        if (isAttackAlive_)
        {
            // カメラ座標
            if (!isGetPos_)
            {
                if (isLeft_)
                {
                    attackPosX_ = pos_.x - SIZE_X;
                    attackPosY_ = pos_.y;
                }
                else
                {
                    attackPosX_ = pos_.x + SIZE_X;
                    attackPosY_ = pos_.y;
                }
                isGetPos_ = true;
            }

            attackAnimCnt_++;
            if (attackAnimCnt_ == 4)
            {
                attackRadius_ = attackSize1_;
            }
            else if (attackAnimCnt_ == 8)
            {
                attackRadius_ = attackSize2_;
            }
            else if (attackAnimCnt_ == 12)
            {
                attackRadius_ = attackSize3_;
            }
            else if (attackAnimCnt_ == 16)
            {
                attackRadius_ = attackSize4_;
            }
            else if (attackAnimCnt_ == 20)
            {
                attackRadius_ = attackSize5_;
            }
            else if (attackAnimCnt_ >= 26)
            {
                if (isLeft_)
                {
                    attackPosX_ -= attackSpeed_;
                }
                else
                {
                    attackPosX_ += attackSpeed_;
                }
            }

            if (attackAnimCnt_ == attackMax_)
            {
                isAttackAlive_ = false;
                isGetPos_ = false;
                attackAnimCnt_ = 0;
                attackCnt_ = 0;
                attackRadius_ = 5;
            }

            DrawCircle(attackPosX_ - cameraPos.x, attackPosY_ - cameraPos.y, attackRadius_, 0x0072ff, true);
        }
    }
}

void EnemyWater::CollisionPlayerAttack()
{
    // エネミーの衝突用半径
    float enemyRadius = 32.0f;
    // 魔法の衝突用半径
    float magicRadius = 5.0f;
    // 剣の衝突用半径
    float swordRadius = 32.0f;
    // プレイヤーの衝突用半径
    float playerRadius = 32.0f;

    // 攻撃属性を取得
    int magicColoer = player_->GetCr();

    // 魔法攻撃使用中
    if (magicColoer != normalCr_)
    {
        // 魔法とエネミーの衝突判定
        // 魔法の座標を取得
        Vector2 magicPos = player_->GetAttackPos();
        // 球体同士の衝突判定
        bool ret = false;
        // お互いの半径の合計
        float radius = enemyRadius + magicRadius;
        // ２つの座標間の距離をピタゴラスの定理で算出
        VECTOR distance = VECTOR();
        distance.x = pos_.x - magicPos.x;
        distance.y = pos_.y - magicPos.y;
        float dis = distance.x * distance.x + distance.y * distance.y;
        // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
        if (dis < (radius * radius))
        {
            // 攻撃ヒット済
            collisionDamage_ = true;
            // 攻撃ヒット時エフェクト
            if (magicColoer == fireCr_)
            {
                blast_->SetBlastPos(magicPos);
                blast_->SetIsBlast(true);

            }
            else if (magicColoer == plantCr_)
            {
                plants_->SetPlantsPos(magicPos);
                plants_->SetIsPlants(true);
            }
            else if (magicColoer == waterCr_)
            {
                water_->CreateEffect(magicPos);
            }
        }
    }
    // 剣攻撃
    else if (magicColoer == normalCr_ && CheckHitKey(KEY_INPUT_K))
    {
        isSword_ = true;
        // カメラ座標の取得
        Vector2 cameraPos = camera_->GetCameraPos();
        // 剣の座標を取得
        Vector2F swordPos = player_->GetAttckAnglePoint();
        // 球体同士の衝突判定
        bool ret = false;
        // お互いの半径の合計
        float radius = enemyRadius + swordRadius;
        // ２つの座標間の距離をピタゴラスの定理で算出
        VECTOR distance = VECTOR();
        distance.x = pos_.x - swordPos.x;
        distance.y = pos_.y - swordPos.y;
        float dis = distance.x * distance.x + distance.y * distance.y;
        // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
        if (dis < (radius * radius))
        {
            // 攻撃ヒット済
            collisionDamage_ = true;
        }
    }
}

void EnemyWater::CollisionEnemyAttack()
{
    if (isAlive_) {
        // エネミーの衝突用半径
        float enemyRadius = 32.0f;
        // 魔法の衝突用半径
        float magicRadius = 5.0f;
        // 剣の衝突用半径
        float swordRadius = 32.0f;
        // プレイヤーの衝突用半径
        float playerRadius = 32.0f;

        // プレイヤーとエネミーの衝突判定
        //プレイヤー座標の取得
        Vector2F playerPos = player_->GetPlayerPos();
        // 球体同士の衝突判定
        bool ret = false;
        // お互いの半径の合計
        float radius = enemyRadius + playerRadius;
        // ２つの座標間の距離をピタゴラスの定理で算出
        VECTOR distance = VECTOR();
        distance.x = pos_.x - playerPos.x;
        distance.y = pos_.y - playerPos.y;
        float dis = distance.x * distance.x + distance.y * distance.y;
        // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
        if (dis < (radius * radius))
        {
            // 衝突した
            collisionWater_ = true;
        }

        // プレイヤーとエネミーの攻撃の衝突判定
        if (isAttackAlive_)
        {
            // 球体同士の衝突判定
            bool ret = false;
            // お互いの半径の合計
            float radius = playerRadius + attackRadius_;
            // ２つの座標間の距離をピタゴラスの定理で算出
            VECTOR distance = VECTOR();
            distance.x = playerPos.x - attackPosX_;
            distance.y = playerPos.y - attackPosY_;
            float dis = distance.x * distance.x + distance.y * distance.y;
            // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
            if (dis < (radius * radius))
            {
                // 攻撃ヒット済
                collisionWater_ = true;
            }
        }
    }
}

void EnemyWater::Damage()
{
    // 攻撃属性を取得
    int attackColoer = player_->GetCr();
    // 攻撃中かどうかを取得
    bool isAttack = player_->GetAttack();

    // 攻撃中でない
    if (isAttack && !isSword_)
    {
        collisionDamage_ = false;
        return;
    }

    // プレイヤーの攻撃属性が
    // WaterまたはNormalのとき
    if (attackColoer == waterCr_)
    {
        // 等倍
        damage_ = 10.0f;
    }
    // Plantのとき
    else if (attackColoer == plantCr_)
    {
        // 抜群
        damage_ = 20.0f;
    }
    // Fireのとき
    else if (attackColoer == fireCr_ || attackColoer == normalCr_)
    {
        // 半減
        damage_ = 5.0f;
    }

    // 衝突したかつエネミー生存中
    if (collisionDamage_ && isAlive_)
    {
        // 無敵状態でなければダメージを与える
        if (!isInvincible_)
        {
            hp_ -= damage_;
        }
        // 攻撃エフェクト削除
        player_->SetPoint(false);
        // 再攻撃可能
        player_->SetAttack(true);
        // 剣判定復活
        isSword_ = false;
    }

    // HPが0になったら撃破
    if (hp_ <= 0.0f)
    {
        hp_ = 0.0f;
        isAlive_ = false;
    }
}

void EnemyWater::InvincibleWater()
{
    invincibleMax_ = 60;
    if (collisionDamage_ || isInvincible_)
    {
        isInvincible_ = true;
        invincibleCnt_++;
        if (invincibleCnt_ >= invincibleMax_)
        {
            isInvincible_ = false;
            invincibleCnt_ = 0;
        }

        if (invincibleCnt_ % 5 >= 3 && invincibleCnt_ > 4)
        {
            isVisible_ = false;
        }
        else
        {
            isVisible_ = true;
        }
    }
}

int EnemyWater::GetSizeX()
{
    return SIZE_X;
}

Vector2F EnemyWater::GetPos()
{
    return pos_;
}

void EnemyWater::SetPos(Vector2F pos)
{
    pos_ = pos;
}

bool EnemyWater::GetAlive()
{
    return isAlive_;
}

void EnemyWater::SetAlive(bool isAlive)
{
    isAlive_ = isAlive;
}

bool EnemyWater::GetLeft()
{
    return isLeft_;
}

void EnemyWater::SetLeft(bool isLeft)
{
    isLeft_ = isLeft;
}

bool EnemyWater::GetFind()
{
    return isFind_;
}

void EnemyWater::SetFind(bool isFind)
{
    isFind_ = isFind;
}

bool EnemyWater::GetCollisionWater()
{
    return collisionWater_;
}

void EnemyWater::SetCollisionWater(bool collisionWater)
{
    collisionWater_ = collisionWater;
}

bool EnemyWater::GetAnimFrameWater()
{
    return animFrame_;
}

void EnemyWater::SetAnimFrameWater(int animFrame)
{
    animFrame_ = animFrame;
}
