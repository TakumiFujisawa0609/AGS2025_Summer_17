#include "EnemyFire.h"
#include "EnemyManager.h"
#include "EnemyAttack/EnemyAttackF.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "../Attack/Blast.h"
#include "../Attack/Plants.h"
#include "../Attack/Water.h"

void EnemyFire::Init(EnemyFire* enemyFire, EnemyAttackF* enemyAttackF, Player* player, Camera* camera, Stage* stage, Blast* blast, Plants* plants, Water* water)
{
    enemyFire_ = enemyFire;
    enemyAttackF_ = enemyAttackF;
    player_ = player;
    camera_ = camera;
    stage_ = stage;
    blast_ = blast;
    plants_ = plants;
    water_ = water;

    enemyAttackF_->Init(enemyFire_, player_, camera_);

    // 属性管理用
    fireCr_ = 0xff0000;
    plantCr_ = 0x00ff00;
    waterCr_ = 0x0000ff;
    normalCr_ = 0xffffff;

    // 初期座標の設定用値
    setInit_ = 2;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyF.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

	fireSound_ = LoadSoundMem("Data/Sound/SE/FireMagic.mp3");
}

void EnemyFire::InitStage2()
{
    if (setInit_ == 2)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 2)
        {
            // 初期座標
            pos_.x = 2172.0f;
            pos_.y = 352.0f;

            // 移動速度
            moveSpeed_ = 1.3f;
            moveMax_ = 200;

            // 索敵範囲
            findSize_ = 220.0f;

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
            collisionFire_ = false;
            // 無敵判定
            isInvincible_ = false;
            // 無敵時描画判定
            isVisible_ = true;
            // 死亡判定
            isDead_ = false;

            // アニメーションフレーム数カウント
            animFrame_ = 0;
            // アニメーションのカウンタ
            animCnt_ = 0;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // HP
            hp_ = 25.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 攻撃間隔
            enemyAttackF_->SetAttackIntervalF(110);
            enemyAttackF_->SetAttackCnt(0);

            // 無敵時間
            invincibleMax_ = 45;
            // 無敵時間のカウント
            invincibleCnt_ = 0;

            setInit_ = 3;
        }
    }
}

void EnemyFire::InitStage3()
{
    if (setInit_ == 3)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 3)
        {
            pos_.x = 5952.0f;
            pos_.y = 736.0f;

            // 移動速度
            moveSpeed_ = 1.5f;
            moveMax_ = 0;

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
            collisionFire_ = false;
            // 無敵判定
            isInvincible_ = false;
            // 無敵時描画判定
            isVisible_ = true;
            // 死亡判定
            isDead_ = false;

            // アニメーションフレーム数カウント
            animFrame_ = 0;
            // アニメーションのカウンタ
            animCnt_ = 0;

            // 移動用のカウンタ
            moveCnt_ = 0;

            // HP
            hp_ = 45.0f;
            // 被ダメージ数
            damage_ = 10.0f;

            // 攻撃間隔
            enemyAttackF_->SetAttackIntervalF(45);
            enemyAttackF_->SetAttackCnt(0);

            // 無敵時間
            invincibleMax_ = 60;
            // 無敵時間のカウント
            invincibleCnt_ = 0;

            setInit_ = 0;
        }
    }
}

void EnemyFire::Update()
{
    InitStage2();
    InitStage3();
    Move();
    Attack();

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
            enemyAttackF_->SetAttack(true);
        }
        else
        {
            // 発見中でない
            isFind_ = false;
            enemyAttackF_->SetAttack(false);
        }
    }

#ifdef _DEBUG

    // 再出現(デバッグ用)
    if (CheckHitKey(KEY_INPUT_B))
    {
        hp_ = 45.0f;
        isAlive_ = true;
        collisionFire_ = false;
        isDead_ = false;
    }

#endif // DEBUG
}

void EnemyFire::Draw()
{
    enemyAttackF_->Draw();

    // プレイヤー座標
    Vector2F playerPos = player_->GetPlayerPos();
    // カメラ座標
    Vector2 cameraPos = camera_->GetCameraPos();
    // 攻撃間隔
    int attackCnt = enemyAttackF_->GetAttackCnt();
    int attackInterval = enemyAttackF_->GetAttackIntervalF();

    // アニメーション処理
    if (!enemyAttackF_->GetAlive() && attackCnt <= attackInterval - 15)
    {
        animCnt_++;
        if (animCnt_ >= ANIM_INTERVAL) {
            animCnt_ = 0;
            animFrame_++;
            if (animFrame_ >= ANIM_MAX) {
                animFrame_ = 0;
            }
        }
    }
    else
    {
        animCnt_ = 0;
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

                if (!enemyAttackF_->GetAlive() && !isDead_)
                {
                    isLeft_ = true;
                }
            }
            else
            {
                // 右向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!enemyAttackF_->GetAlive() && !isDead_)
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

#ifdef _DEBUG

    // プレイヤー当たり判定円描画
    DrawCircle(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y, 32, (0x000000), false);
    // エネミー当たり判定円描画
    DrawCircle(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 32, (0x000000), false);

#endif // _DEBUG
}

void EnemyFire::Move()
{
    if (isAlive_ && !enemyAttackF_->GetAlive())
    {
        // 発見中でないかつ死亡してないなら動かす
        if (!isFind_ && !isDead_)
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

void EnemyFire::Attack()
{
    CollisionPlayerAttack();
    CollisionEnemyAttack();
    Damage();
    InvincibleFire();
    enemyAttackF_->Update();
}

void EnemyFire::CollisionPlayerAttack()
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
    if (isAlive_) {
        // 魔法攻撃
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
            }
        }
        // 剣攻撃
        else if (magicColoer == normalCr_ && CheckHitKey(KEY_INPUT_K))
        {
            player_->GetSword();
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
            else
            {
                collisionDamage_ = false;
            }
        }
    }
}

void EnemyFire::CollisionEnemyAttack()
{
    if (isAlive_)
    {
        

        
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
            collisionFire_ = true;
        }

        // プレイヤーとエネミーの攻撃の衝突判定
        // エネミーの攻撃座標の取得
        Vector2F attackPos = enemyAttackF_->GetPos();
        // エネミーの攻撃画像のサイズ取得
        int attackSizeX = enemyAttackF_->GetSizeX();
        int attackSizeY = enemyAttackF_->GetSizeY();
        // カメラ座標の取得
        Vector2 cameraPos = camera_->GetCameraPos();
        // エネミーの攻撃のフレーム数取得
        int attackFrame = enemyAttackF_->GetAnimFrameAttackF();

        if (enemyAttackF_->GetAlive())
        {
            if (CheckSoundMem(fireSound_) == 0) {
                PlaySoundMem(fireSound_, DX_PLAYTYPE_BACK);
            }
            // 当たり判定調整
            if (attackFrame == 4)
            {
                leftControl_ = 32.0f;
            }
            else if (attackFrame == 3)
            {
                leftControl_ = 21.0f;
            }
            else if (attackFrame == 2)
            {
                leftControl_ = 12.0f;
            }
            else
            {
                leftControl_ = 0.0f;
            }

            // エネミーの攻撃の当たり判定座標
            // 左向きのとき
            if (isLeft_)
            {
                // 左
                leftAttackPos = pos_.x - attackSizeX + 12.0f + leftControl_;
                // 右
                rightAttackPos = pos_.x;
                // 上
                topAttackPos = pos_.y;
                // 下
                bottomAttackPos = pos_.y + attackSizeY;
            }
            // 右向きのとき
            else
            {
                // 左
                leftAttackPos = pos_.x + SIZE_X;
                // 右
                rightAttackPos = pos_.x + SIZE_X / 2 + attackSizeX + 12.0f - leftControl_;
                // 上
                topAttackPos = pos_.y;
                // 下
                bottomAttackPos = pos_.y + attackSizeY;
            }

            // プレイヤー画像のサイズ
            float playrSize = 58.0f;
            // 衝突判定
            if (rightAttackPos > playerPos.x &&
                leftAttackPos < playerPos.x + playrSize &&
                topAttackPos < playerPos.y + playrSize &&
                bottomAttackPos > playerPos.y)
            {
                // 衝突した
                collisionFire_ = true;
            }
        }
    }
}

void EnemyFire::Damage()
{
    // 攻撃属性を取得
    int magicColoer = player_->GetCr();
    // 攻撃中かどうかを取得
    bool isAttack = !player_->GetAttack();
    // 魔法の座標を取得
    Vector2 magicPos = player_->GetAttackPos();

    // 攻撃中でない
    if (!isAttack && !player_->GetSword())
    {
        collisionDamage_ = false;
        return;
    }

    // プレイヤーの攻撃属性が
    // FireまたはNormalのとき
    if (magicColoer == fireCr_)
    {
        // 等倍
        damage_ = 10.0f;
    }
    // Waterのとき
    else if (magicColoer == waterCr_)
    {
        // 抜群
        damage_ = 20.0f;
    }
    // Plantのとき
    else if (magicColoer == plantCr_ || magicColoer == normalCr_)
    {
        // 半減
        damage_ = 5.0f;
    }

    // 衝突した
    if (collisionDamage_)
    {
        // 無敵状態でなければダメージを与える
        if (!isInvincible_)
        {
            hp_ -= damage_;
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
        // 攻撃エフェクト削除
        player_->SetPoint(false);
        // 再攻撃可能
        player_->SetAttack(true);
    }

    // HPが0
    if (hp_ <= 0.0f)
    {
        hp_ = 0.0f;
        isDead_ = true;
    }
}

void EnemyFire::InvincibleFire()
{
    if (collisionDamage_ || isInvincible_)
    {
        isInvincible_ = true;
        invincibleCnt_++;
        if (invincibleCnt_ >= invincibleMax_)
        {
            isInvincible_ = false;
            invincibleCnt_ = 0;

            // HPが0なら撃破
            if (isDead_)
            {
                if (isAlive_)
                {
                    // MP回復
                    player_->DownMp(-30);
                    // MPが上限(100)を超えたら戻す
                    if (player_->GetMp() >= 100)
                    {
                        player_->SetMp(100);
                    }
                }

                // 撃破
                isAlive_ = false;
            }
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

int EnemyFire::GetSizeX()
{
    return SIZE_X;
}

Vector2F EnemyFire::GetPos()
{
    return pos_;
}

void EnemyFire::SetPos(Vector2F pos)
{
    pos_ = pos;
}

bool EnemyFire::GetAlive()
{
    return isAlive_;
}

void EnemyFire::SetAlive(bool isAlive)
{
    isAlive_ = isAlive;
}

bool EnemyFire::GetLeft()
{
    return isLeft_;
}

void EnemyFire::SetLeft(bool isLeft)
{
    isLeft_ = isLeft;
}

bool EnemyFire::GetFind()
{
    return isFind_;
}

void EnemyFire::SetFind(bool isFind)
{
    isFind_ = isFind;
}

bool EnemyFire::GetCollisionFire()
{
    return collisionFire_;
}

void EnemyFire::SetCollisionFire(bool collisionFire)
{
    collisionFire_ = collisionFire;
}

bool EnemyFire::GetAnimFrameFire()
{
    return animFrame_;
}

void EnemyFire::SetAnimFrameFire(int animFrame)
{
    animFrame_ = animFrame;
}

bool EnemyFire::GetDeadFire()
{
    return isDead_;
}

void EnemyFire::SetDeadFire(bool isDead)
{
	isDead_ = isDead;
}
