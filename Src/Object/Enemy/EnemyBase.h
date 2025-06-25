#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class EnemyFire;
class Player;
class Camera;
class Stage;

class EnemyBase {
public:

    void Init(Player* player, Camera* camera, Stage* stage);
    void Update();
    void Draw();

private:

    int imgF_;
    int imgW_;
    int imgP_;

    bool isFire_;
    bool isWater_;
    bool isPlant_;
    
    EnemyFire* enemyFire_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;
    
};