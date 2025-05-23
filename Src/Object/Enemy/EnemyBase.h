#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class Camera;

class EnemyBase {
public:

    void Init();
    void Update();
    void Draw();

protected:
    
    // ˆÚ“®ˆ—
    void Move();
    // UŒ‚ˆ—
    void Attack();

    Vector2F pos_;
    int img_;
    int attackCnt_;
    bool isAlive_;
    bool isAttack_;

};