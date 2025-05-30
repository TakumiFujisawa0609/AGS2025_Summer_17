#pragma once
#include "EnemyBase.h"
#include <DxLib.h>

class EnemyFire
{
public:

    // サイズ
    static constexpr int SIZE_X = 64;
    static constexpr int SIZE_Y = 64;

    // 移動速度
    static constexpr float MOVE_SPEED = 1.0f;

    // アニメーション
    static constexpr int ANIM_X = 4;
    static constexpr int ANIM_Y = 1;
    static constexpr int ANIM_MAX = ANIM_X * ANIM_Y;
    static constexpr int ANIM_INTERVAL = 13;

    void Init();
    void Update();
    void Draw();

private:

    Vector2F pos_;

    int img_;

    int Array_[ANIM_MAX];
    int animFrame_;
    int animCounter_;
    int animInterval_;
    
    int attackCnt_;
    bool isAlive_;
    bool isAttack_;

};