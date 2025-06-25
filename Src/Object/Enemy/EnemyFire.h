#pragma once
#include "EnemyBase.h"
#include <DxLib.h>
class EnemyManager;
class EnemyAttack;
class EnemyFire;
class Player;
class Camera;
class Stage;

class EnemyFire
{
public:

    // サイズ
    static constexpr int SIZE_X = 64;
    static constexpr int SIZE_Y = 64;

    // 移動処理
    static constexpr float MOVE_SPEED = 1.5f;
    static constexpr int MOVE_MAX = 240;

    // アニメーション
    static constexpr int ANIM_X = 4;
    static constexpr int ANIM_Y = 1;
    static constexpr int ANIM_MAX = ANIM_X * ANIM_Y;
    static constexpr int ANIM_INTERVAL = 13;

    // 索敵範囲
    static constexpr float FIND_SIZE = 160.0f;

    // 初期化
    void Init(EnemyAttack* enemyAttack, EnemyFire* enemyFire, Player* player, Camera* camera, Stage* stage);
    // 更新
    void Update();
    // 描画
    void Draw();

    // 攻撃
    void Attack();
    // 移動
    void Move();
    // 被ダメージ
    void Damage();

    // サイズ
    int GetSizeX();

    // 座標
    Vector2F GetPos();

    // 生存中判定
    bool GetAlive();

    // 左右判定の取得(trueなら左向き)
    bool GetLeft();

    // 発見中判定(trueなら発見中)
    bool GetFind();

private:

    // エネミー
    EnemyManager* enemyManager_;
    EnemyAttack* enemyAttack_;
    EnemyFire* enemyFire_;
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
    // プレイヤー攻撃ヒット判定
    bool wasHit_;
};