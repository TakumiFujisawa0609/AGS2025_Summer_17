#include "EnemyPlant.h"
#include "EnemyManager.h"
#include "EnemyAttack/EnemyAttackP.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"

void EnemyPlant::Init(EnemyPlant* enemyPlant, EnemyAttackP* enemyAttackP, Player* player, Camera* camera, Stage* stage)
{
    enemyAttackP_ = enemyAttackP;
    enemyPlant_ = enemyPlant;
    player_ = player;
    camera_ = camera;
    stage_ = stage;

    enemyAttackP_->Init(enemyPlant_, player_, camera_);

    // 初期化用変数
    setInit_ = 2;

    // 属性管理用
    fire_ = 0xff0000;
    plant_ = 0x00ff00;
    water_ = 0x0000ff;
    normal_ = 0xffffff;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyP.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);
}

void EnemyPlant::InitStage2()
{
    // ステージ2
    if (setInit_ == 2)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 2)
        {
            // 初期座標
            pos_.x = 5368.0f;
            pos_.y = 672.0f;

            // 移動速度
            moveSpeed_ = 1.0f;
            moveMax_ = 200;

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
            collisionPlant_ = false;

            // アニメーションフレーム数カウント
            animFrame_ = WALK_ANIM_MIN;
            // アニメーションのカウンタ
            animCnt_ = 0;
            // アニメーションの進行間隔
            animInterval_ = 10;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // HP
            hp_ = 25.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 初期化用変数
            setInit_ = 3;
        }
    }
}

void EnemyPlant::InitStage3()
{
    // ステージ3
    if (setInit_ == 3)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 3)
        {
            // 仮
            pos_.x = 300.0f;
            pos_.y = 300.0f;

            // 移動速度
            moveSpeed_ = 2.0f;
            moveMax_ = 100;

            // 索敵範囲
            findSize_ = 120.0f;

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
            collisionPlant_ = false;

            // アニメーションフレーム数カウント
            animFrame_ = WALK_ANIM_MIN;
            // アニメーションのカウンタ
            animCnt_ = 0;
            // アニメーションの進行間隔
            animInterval_ = 10;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // HP
            hp_ = 45.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 初期化用変数
            setInit_ = 0;
        }
    }
}

void EnemyPlant::Update()
{
    InitStage2();
    InitStage3();
    Move();
    Attack();
    PlayerAttackCollision();
    EnemyAttackCollision();
    Damage();
    enemyAttackP_->Update();

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
            enemyAttackP_->SetAttack(true);
        }
        else
        {
            // 発見中でない
            isFind_ = false;
            enemyAttackP_->SetAttack(false);
        }
    }

#ifdef _DEBUG

    // 再出現(デバッグ用)
    if (CheckHitKey(KEY_INPUT_N))
    {
        hp_ = 25.0f;
        isAlive_ = true;
        collisionPlant_ = false;
    }

#endif // DEBUG
}

void EnemyPlant::Draw()
{

    enemyAttackP_->Draw();

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
    // 攻撃モーション
    if (enemyAttackP_->GetAlive())
    {
        int attackFrame = enemyAttackP_->GetAnimFrameAttackP();
        if (attackFrame == 0)
        {
            animFrame_ = ATTACK_ANIM_MIN;
            animInterval_ = 8;
        }
        else if (attackFrame >= 1)
        {
            animCnt_++;
            if (animCnt_ >= animInterval_) {
                animCnt_ = 0;
                animFrame_++;
                if (animFrame_ >= ATTACK_ANIM_MAX)
                {
                    animFrame_ = IDLE_ANIM_MIN;
                }
                else if (animFrame_ > IDLE_ANIM_MAX && animFrame_ < ATTACK_ANIM_MIN)
                {
                    animInterval_ = 12;
                    animFrame_ = IDLE_ANIM_MIN;
                }
            }
        }
    }
    // 歩行モーション
    else if (!enemyAttackP_->GetAlive())
    {
        animInterval_ = 10;
        animCnt_++;
        if (animCnt_ >= animInterval_) {
            animCnt_ = 0;
            animFrame_++;
            if (animFrame_ > WALK_ANIM_MAX) {
                animFrame_ = WALK_ANIM_MIN;
            }
        }
    }

    if (isAlive_)
    {
        // 発見中
        if (isFind_)
        {
            // 待機時フレーム
            if (!enemyAttackP_->GetAlive())
            {
                animFrame_ = 18;
            }

            // プレイヤーがエネミーの左にいるか
            if (playerPos.x <= pos_.x)
            {
                // 左向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!enemyAttackP_->GetAlive())
                {
                    isLeft_ = true;
                }
            }
            else
            {
                // 右向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!enemyAttackP_->GetAlive())
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

void EnemyPlant::Attack()
{
    if (isAttack_)
    {
        int a = 0; // 仮
    }
}

void EnemyPlant::Move()
{
    if (isAlive_ && !enemyAttackP_->GetAlive())
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

void EnemyPlant::PlayerAttackCollision()
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
    if (magicColoer != 0xffffff)
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
        }
    }
    //// 剣攻撃
    //else if (magicColoer == 0xffffff)
    //{
    //    //player_->GetSotd();
    //    // 剣の座標を取得
    //    Vector2F swordPos = player_->GetAttckAnglePoint();
    //    // 球体同士の衝突判定
    //    bool ret = false;
    //    // お互いの半径の合計
    //    float radius = enemyRadius + swordRadius;
    //    // ２つの座標間の距離をピタゴラスの定理で算出
    //    VECTOR distance = VECTOR();
    //    distance.x = pos_.x - swordPos.x;
    //    distance.y = pos_.y - swordPos.y;
    //    float dis = distance.x * distance.x + distance.y * distance.y;
    //    // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
    //    if (dis < (radius * radius))
    //    {
    //        // 攻撃ヒット済
    //        collisionDamage_ = true;
    //    }
    //}
}

void EnemyPlant::EnemyAttackCollision()
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
            collisionPlant_ = true;
        }

        // プレイヤーとエネミーの攻撃の衝突判定
        // エネミーの攻撃座標の取得
        Vector2F attackPos = enemyAttackP_->GetPos();
        // エネミーの攻撃画像のサイズ取得
        int attackSizeX = enemyAttackP_->GetSizeX();
        int attackSizeY = enemyAttackP_->GetSizeY();
        // カメラ座標の取得
        Vector2 cameraPos = camera_->GetCameraPos();
        // エネミーの攻撃のフレーム数取得
        int attackFrame = enemyAttackP_->GetAnimFrameAttackP();

        if (enemyAttackP_->GetAlive()) {
            // エネミーの攻撃の当たり判定座標
            leftAttackPos = attackPos.x - attackSizeX / 2 - cameraPos.x;
            // 左
            rightAttackPos = attackPos.x + attackSizeX / 2 - cameraPos.x;
            // 上
            topAttackPos = attackPos.y - attackSizeY / 2 - cameraPos.y;
            // 下
            bottomAttackPos = attackPos.y + attackSizeY / 2 - cameraPos.y;

            // プレイヤー画像のサイズ
            float playrSize = 58.0f;
            // 衝突判定
            if (leftAttackPos < playerPos.x + playrSize - cameraPos.x &&
                rightAttackPos > playerPos.x - cameraPos.x &&
                topAttackPos < playerPos.y + playrSize - cameraPos.y &&
                bottomAttackPos > playerPos.y - cameraPos.y &&
                attackFrame >= 2)
            {
                // 衝突した
                collisionPlant_ = true;
                isAlive_ = false;
            }
        }
    }
}

void EnemyPlant::Damage()
{
    // 攻撃属性を取得
    int attackColoer = player_->GetCr();
    // 攻撃中かどうかを取得
    bool isAttack = player_->GetAttack();

    // 攻撃中でない
    if (isAttack) {
        wasHit_ = false;
        collisionDamage_ = false;
        return;
    }

    // 攻撃ヒット済みなので何もしない
    if (wasHit_)
    {
        return;
    }

    // プレイヤーの攻撃属性が
    // PlantまたはNormalのとき
    if (attackColoer == plant_ || attackColoer == normal_)
    {
        // 等倍
        damage_ = 10.0f;
    }
    // Fireのとき
    else if (attackColoer == fire_)
    {
        // 抜群
        damage_ = 20.0f;
    }
    // Waterのとき
    else if (attackColoer == water_)
    {
        // 半減
        damage_ = 5.0f;
    }

    // 衝突したかつエネミー生存中
    if (collisionDamage_ && isAlive_)
    {
        // ダメージを与える
        hp_ -= damage_;
        // 攻撃エフェクト削除
        player_->SetPoint(false);
        // 再攻撃可能
        player_->SetAttack(true);
    }

    // HPが0になったら撃破
    if (hp_ <= 0.0f)
    {
        hp_ = 0.0f;
        isAlive_ = false;
    }
}

int EnemyPlant::GetSizeX()
{
    return SIZE_X;
}

Vector2F EnemyPlant::GetPos()
{
    return pos_;
}

void EnemyPlant::SetPos(Vector2F pos)
{
    pos_ = pos;
}

bool EnemyPlant::GetAlive()
{
    return isAlive_;
}

void EnemyPlant::SetAlive(bool isAlive)
{
    isAlive_ = isAlive;
}

bool EnemyPlant::GetLeft()
{
    return isLeft_;
}

void EnemyPlant::SetLeft(bool isLeft)
{
    isLeft_ = isLeft;
}

bool EnemyPlant::GetFind()
{
    return isFind_;
}

void EnemyPlant::SetFind(bool isFind)
{
    isFind_ = isFind;
}

bool EnemyPlant::GetCollisionPlant()
{
    return collisionPlant_;
}

void EnemyPlant::SetCollisionPlant(bool collisionPlant)
{
    collisionPlant_ = collisionPlant;
}

bool EnemyPlant::GetAnimFramePlant()
{
    return animFrame_;
}

void EnemyPlant::SetAnimFramePlant(int animFrame)
{
    animFrame_ = animFrame;
}
