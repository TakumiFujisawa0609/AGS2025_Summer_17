#pragma once
#include "EnemyBase.h"
#include <DxLib.h>
class EnemyManager;
class EnemyAttackW;
class EnemyWater;
class Player;
class Camera;
class Stage;

class EnemyWater
{
public:

    // サイズ
    static constexpr int SIZE_X = 64;
    static constexpr int SIZE_Y = 64;

    // アニメーション
    static constexpr int ANIM_X = 3;
    static constexpr int ANIM_Y = 3;
    static constexpr int ANIM_MAX = ANIM_X * ANIM_Y;
    static constexpr int ANIM_INTERVAL = 12;
    // アニメーションフレーム
    static constexpr int ATTACK_ANIM = 6;
    static constexpr int WALK_ANIM_MIN = 3;
    static constexpr int WALK_ANIM_MAX = 5;

    // 初期化
    void Init(EnemyWater* enemyWater, EnemyAttackW* enemyAttackW, Player* player, Camera* camera, Stage* stage);
    void InitStage2();
    void InitStage3();
    // 更新
    void Update();
    // 描画
    void Draw();

    // 攻撃
    void Attack();
    // 移動
    void Move();
    // 衝突判定
    void CollisionPlayerAttack();
    void CollisionEnemyAttack();
    // 被ダメージ
    void Damage();

    // サイズ
    int GetSizeX();

    // 座標の取得・更新
    Vector2F GetPos();
    void SetPos(Vector2F pos);

    // 生存中判定の取得・更新
    bool GetAlive();
    void SetAlive(bool isAlive);

    // 左右判定の取得・更新(trueなら左向き)
    bool GetLeft();
    void SetLeft(bool isLeft);

    // 発見中判定の取得・更新(trueなら発見中)
    bool GetFind();
    void SetFind(bool isFind);

    // エネミー(エネミーの攻撃)とプレイヤーの衝突判定の取得・更新
    bool GetCollisionWater();
    void SetCollisionWater(bool collisionWater);

    // アニメーションフレーム数カウント
    bool GetAnimFrameWater();
    void SetAnimFrameWater(int animFrame);

private:

    // エネミー
    EnemyManager* enemyManager_;
    EnemyAttackW* enemyAttackW_;
    EnemyWater* enemyWater_;
    // プレイヤー
    Player* player_;
    // カメラ
    Camera* camera_;
    // ステージ
    Stage* stage_;

    // 座標
    Vector2F pos_;
    // 初期座標の設定用値
    int setInit_;

    // エネミーの攻撃の当たり判定座標
    float leftAttackPos;
    float rightAttackPos;
    float topAttackPos;
    float bottomAttackPos;

    // 移動速度
    float moveSpeed_;
    int moveMax_;

    // 索敵範囲
    float findSize_ = 160.0f;

    // 画像のハンドルID
    int img_;

    // アニメーション数
    int Array_[ANIM_MAX];
    // アニメーションフレーム数カウント
    int animFrame_;
    // アニメーションのカウンタ
    int animCnt_;

    // 移動用のカウンタ
    int moveCnt_;

    // 属性管理用
    int fire_;
    int plant_;
    int water_;
    int normal_;

    // HP
    float hp_;
    // 被ダメージ
    float damage_;

    // 生存中判定
    bool isAlive_;
    // 攻撃中判定
    bool isAttack_;
    // 左右判定(trueなら左向き)
    bool isLeft_;
    // 発見中判定(trueなら発見中)
    bool isFind_;
    // プレイヤー攻撃ヒット済み判定
    bool wasHit_;
    // プレイヤーの攻撃とエネミーの衝突判定
    bool collisionDamage_;
    // エネミー(エネミーの攻撃)とプレイヤーの衝突判定
    bool collisionWater_;

};