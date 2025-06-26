#pragma once
#include <vector>
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "EnemyAttack/EnemyAttack.h"
#include "../../Common/Vector2.h"
class EnemyBase;
class EnemyFire;
class EnemyAttack;
class Camera;
class Player;
class Stage;
//class EnemyWater;
//class EnemyPlant;

class EnemyManager {
public:

    void Init(EnemyAttack* enemyAttack, EnemyFire* enemyFire, Player* player, Camera* camera, Stage* stage);
    void Update();
    void Draw();
    void CollisionAttack();

    bool GetCollisionAttack();
    void SetCollisionAttack(bool collisionAttack);


private:

    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    EnemyAttack* enemyAttack_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;

    bool collisionAttack_;

    //EnemyWater* enemyWater_;
    //EnemyPlant* enemyPlant_;

};