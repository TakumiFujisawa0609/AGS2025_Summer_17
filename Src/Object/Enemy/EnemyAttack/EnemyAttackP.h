#pragma once
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include <DxLib.h>
class EnemyPlant;
class Player;
class Camera;

class EnemyAttackP
{
public:

    // サイズ
    static constexpr int SIZE_X = 96;
    static constexpr int SIZE_Y = 96;

    // アニメーション
    static constexpr int ANIM_X = 1;
    static constexpr int ANIM_Y = 9;
    static constexpr int ANIM_MAX = ANIM_X * ANIM_Y;
    static constexpr int ANIM_INTERVAL = 8;

    // 攻撃
    static constexpr int ATTACK_INTERVAL = 110;

    // 初期化
    void Init(EnemyPlant* enemyPlant, Player* player, Camera* camera);
    // 更新
    void Update();
    // 描画
    void Draw();

    // 座標の取得・更新
    Vector2F GetPos();
    void SetPos(Vector2F pos);

    // サイズ
    int GetSizeX();
    int GetSizeY();

    // 再生中判定の取得・更新
    bool GetAttack();
    void SetAttack(bool isAttack);

    // 再生中判定の取得・更新
    bool GetAlive();
    void SetAlive(bool isAlive);

private:

    EnemyPlant* enemyPlant_;
    Player* player_;
    Camera* camera_;

    // 座標
    Vector2F pos_;

    float leftPos_;
    float rightPos_;
    float topPos_;
    float bottomPos_;

    // 画像のハンドルID
    int img_;

    // アニメーション数
    int Array_[ANIM_MAX];
    // アニメーションフレーム数カウント
    int animFrame_;
    // アニメーションのカウンタ
    int animCnt_;

    // 攻撃用のカウンタ
    int attackCnt_;

    // 攻撃中判定
    bool isAttack_;

    // 再生中判定
    bool isAlive_;

    // 再生折り返し判定
    bool isCntUp_;

};

