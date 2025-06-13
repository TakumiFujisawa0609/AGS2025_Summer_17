#pragma once
#include <vector>
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../../Common/Vector2.h"
class EnemyBase;
class EnemyFire;
class Camera;
//class EnemyWater;
//class EnemyPlant;

class EnemyManager {
public:

    void Init(Camera*camera);
    void Update(void);
    void Draw(void);

private:

    Camera* camera_;
    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    //EnemyWater* enemyWater_;
    //EnemyPlant* enemyPlant_;

};