#include "EnemyFire.h"
#include "EnemyManager.h"
#include "EnemyAttack/EnemyAttack.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"

void EnemyFire::Init(EnemyAttack* enemyAttack, EnemyFire* enemyFire, Player* player, Camera* camera, Stage* stage)
{   
    enemyAttack_ = enemyAttack;
    enemyFire_ = enemyFire;
    player_ = player;
    camera_ = camera;
    stage_ = stage;

    enemyAttack_->Init(enemyFire_, player_, camera_);

    // 初期座標の設定用値
    setInit_ = 2;

    // 生存判定
    isAlive_ = true;

    // 攻撃中判定
    isAttack_ = false;

    // 左右判定(trueなら左向き)
    isLeft_ = true;

    // 発見中判定(trueなら発見中)
    isFind_ = false;

    // 画像の読み込み
    img_ = LoadDivGraph
    ("Data/Image/Enemy/EnemyF.png", ANIM_MAX, ANIM_X, ANIM_Y, SIZE_X, SIZE_Y, Array_);

    // アニメーションフレーム数カウント
    animFrame_ = 0;
    // アニメーションのカウンタ
    animCnt_ = 0;

    // 移動用のカウンタ
    moveCnt_ = 0;
}

void EnemyFire::Update()
{
    if (setInit_ == 2)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 2)
        {
            // 初期座標
            pos_.x = 2460.0f;
            pos_.y = 352.0f;

            // 生存判定
            isAlive_ = true;
            // 攻撃中判定
            isAttack_ = false;
            // 左右判定(trueなら左向き)
            isLeft_ = true;
            // 発見中判定(trueなら発見中)
            isFind_ = false;
            // プレイヤー攻撃ヒット判定
            wasHit_ = false;

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

            setInit_ = 3;
        }
    }
    else if (setInit_ == 3)
    {
        // ステージIDの取得
        int stageId = stage_->GetStageId();

        if (stageId == 3)
        {
            // 仮
            pos_.x = 300.0f;
            pos_.y = 300.0f;

            // 生存判定
            isAlive_ = true;
            // 攻撃中判定
            isAttack_ = false;
            // 左右判定(trueなら左向き)
            isLeft_ = true;
            // 発見中判定(trueなら発見中)
            isFind_ = false;
            // プレイヤー攻撃ヒット判定
            wasHit_ = false;

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
            
            setInit_ = 0;
        }
    }

    Move();
    Attack();
    Damage();
    enemyAttack_->Update();

    // プレイヤー座標
    Vector2F playerPos = player_->GetPlayerPos();

    if (isAlive_)
    {
        // 一定範囲(正方形)に入ったらtrue
        if (!(playerPos.x < pos_.x - FIND_SIZE || playerPos.x > pos_.x + FIND_SIZE) &&
            !(playerPos.y < pos_.y - FIND_SIZE || playerPos.y > pos_.y + FIND_SIZE))
        {
            // 発見中
            isFind_ = true;
            enemyAttack_->SetAttack(true);
        }
        else
        {
            // 発見中でない
            isFind_ = false;
            enemyAttack_->SetAttack(false);
        }
    }

#ifdef _DEBUG

    // 再出現(デバッグ用)
    if (CheckHitKey(KEY_INPUT_B))
    {
        hp_ = 25.0f;
        isAlive_ = true;
    }

#endif // DEBUG
}

void EnemyFire::Draw()
{

    enemyAttack_->Draw();

    // プレイヤー座標
    Vector2F playerPos = player_->GetPlayerPos();
    // カメラ座標
    Vector2 cameraPos = camera_->GetCameraPos();

#ifdef _DEBUG

    // プレイヤー当たり判定円描画
    DrawCircle(playerPos.x - cameraPos.x, playerPos.y - cameraPos.y, 32, (0, 0, 0), false);
    // エネミー当たり判定円描画
    DrawCircle(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 32, (0, 0, 0), false);

#endif // _DEBUG

    // アニメーション処理
    if (!enemyAttack_->GetAlive())
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

    if (isAlive_)
    {
        // 発見中
        if (isFind_)
        {
            // プレイヤーがエネミーの左にいるか
            if (playerPos.x <= pos_.x)
            {
                // 左向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!enemyAttack_->GetAlive())
                {
                    isLeft_ = true;
                }
            }
            else
            {
                // 右向きに描画
                DrawRotaGraphF(pos_.x - cameraPos.x, pos_.y - cameraPos.y, 1.0f, 0.0f, Array_[animFrame_], true, isLeft_);

                if (!enemyAttack_->GetAlive())
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

void EnemyFire::Attack()
{
    if (isAttack_)
    {
        int a = 0; // 仮
    }
}

void EnemyFire::Move()
{
    if (isAlive_ && !enemyAttack_->GetAlive())
    {
        // 発見中でないなら動かす
        if (!isFind_)
        {
            moveCnt_++;
            // 左へ移動
            if (moveCnt_ < MOVE_MAX)
            {
                pos_.x -= MOVE_SPEED;
                isLeft_ = true;
            }
            // 右へ移動
            else if (moveCnt_ < MOVE_MAX * 2)
            {
                pos_.x += MOVE_SPEED;
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

void EnemyFire::Damage()
{
    // 攻撃属性を取得
    int attackColoer = player_->GetCr();
    // 魔法の座標を取得
    Vector2 attackPos = player_->GetAttackPos();

    // 攻撃中かどうかを取得
    bool isAttack = player_->GetAttack();

    // 攻撃中でない
    if (isAttack) {
        wasHit_ = false;
        return;
    }

    // 攻撃ヒット済みなので何もしない
    if (wasHit_)
    {
        return;
    }

    // プレイヤーの攻撃属性が
    // FireまたはNormalのとき
    if (attackColoer == 0xff0000 || attackColoer == 0xffffff)
    {
        // 等倍
        damage_ = 10.0f;
    }
    // Waterのとき
    else if (attackColoer == 0x0000ff)
    {
        // 抜群
        damage_ = 20.0f;
    }
    // Plantのとき
    else if (attackColoer == 0x00ff00)
    {
        // 半減
        damage_ = 5.0f;
    }

    // 球体と点の衝突判定
    // // ２つの座標間の距離をピタゴラスの定理で算出
    VECTOR distance;
    distance.x = pos_.x - attackPos.x;
    distance.y = pos_.y - attackPos.y;
    float dis = distance.x * distance.x + distance.y * distance.y;
    // 半径の２乗よりも、２つの座標間の距離が小さければ球体は衝突している
    float radius = 32.0f;
    if (radius * radius > dis)
    {
        // ダメージを与える
        hp_ -= damage_;
        // 攻撃ヒット済
        wasHit_ = true;
        // 攻撃エフェクト削除
        player_->SetPoint(false);
        // 再攻撃可能
        player_->SetAttack(true);
    }

    // HPが0になったら撃破
    if (hp_ <= 0.0f)
    {
        isAlive_ = false;
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

bool EnemyFire::GetAlive()
{
    return isAlive_;
}

bool EnemyFire::GetLeft()
{
    return isLeft_;
}

bool EnemyFire::GetFind()
{
    return isFind_;
}