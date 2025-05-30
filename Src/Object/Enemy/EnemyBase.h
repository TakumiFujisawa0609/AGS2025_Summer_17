#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class Camera;
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
  
    Camera* camera_;
    EnemyFire* enemyFire_;

};