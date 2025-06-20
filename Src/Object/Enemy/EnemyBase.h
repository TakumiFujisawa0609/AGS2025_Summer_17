#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class Camera;
class EnemyFire;
class Player;
class Stage;

class EnemyBase {
public:

    void Init(Player* player, Camera* camera, Stage* stage);
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

    Player* player_;
    Camera* camera_;
    Stage* stage_;
    EnemyFire* enemyFire_;

};