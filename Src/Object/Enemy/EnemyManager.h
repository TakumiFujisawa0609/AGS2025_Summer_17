#pragma once
#include <vector>
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../../Common/Vector2.h"
class EnemyBase;
class EnemyFire;
//class EnemyWater;
//class EnemyPlant;

class EnemyManager {
public:

    void Init(void);
    void Update(void);
    void Draw(void);

private:

    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    //EnemyWater* enemyWater_;
    //EnemyPlant* enemyPlant_;

};