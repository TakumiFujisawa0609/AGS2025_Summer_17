#pragma once
#include <vector>
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../../Common/Vector2.h"
class EnemyBase;
class EnemyFire;
class Camera;
class Player;
class Stage;
//class EnemyWater;
//class EnemyPlant;

class EnemyManager {
public:

    void Init(Player* player, Camera* camera, Stage* stage);
    void Update(void);
    void Draw(void);

private:

    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;

    //EnemyWater* enemyWater_;
    //EnemyPlant* enemyPlant_;

};