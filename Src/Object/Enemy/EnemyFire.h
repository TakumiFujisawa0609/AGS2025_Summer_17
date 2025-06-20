#pragma once
#include "EnemyBase.h"
#include <DxLib.h>
class EnemyManager;
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
    static constexpr float FIND_SIZE = 256.0f;

    void Init(Player* player, Camera* camera, Stage* stage);
    void Update();
    void Draw();
    void Attack();
    void Move();

private:

    EnemyManager* enemyManager_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;

    Vector2F pos_;

    int img_;

    int Array_[ANIM_MAX];
    int animFrame_;
    int animCnt_;
    int animInterval_;

    int moveCnt_;
    
    int attackCnt_;
    bool isAlive_;
    bool isAttack_;
    bool isLeft_;
    bool isFind_;

};