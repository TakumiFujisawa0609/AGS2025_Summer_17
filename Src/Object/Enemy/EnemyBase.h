#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class EnemyFire;

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

    int imgF_;
    int imgW_;
    int imgP_;

    bool isFire_;
    bool isWater_;
    bool isPlant_;
  
    EnemyFire* enemyFire_;

};