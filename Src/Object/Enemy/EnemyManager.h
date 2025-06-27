#pragma once
#include <vector>
#include "EnemyBase.h"
#include "EnemyFire.h"
#include "EnemyPlant.h"
#include "EnemyAttack/EnemyAttackF.h"
#include "EnemyAttack/EnemyAttackP.h"
#include "../../Common/Vector2.h"
class EnemyBase;
class EnemyFire;
class EnemyPlant;
//class EnemyWater;
class EnemyAttackF;
class EnemyAttackP;
//class EnemyAttackW;
class Camera;
class Player;
class Stage;



class EnemyManager {
public:

    void Init(EnemyFire* enemyFire, EnemyPlant* enemyPlant, EnemyAttackF* enemyAttackF, EnemyAttackP* enemyAttackP, Player* player, Camera* camera, Stage* stage);
    void Update();
    void Draw();
    void CollisionAttack();

    bool GetCollisionEnemy();
    void SetCollisionEnemy(bool collisionEnemy);

private:

    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    EnemyPlant* enemyPlant_;
    //EnemyWater* enemyWater_;
    EnemyAttackF* enemyAttackF_;
    EnemyAttackP* enemyAttackP_;
    //EnemyAttackW* enemyAttackW_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;

    bool fireCollision_;
    bool waterCollision_;
    bool plantCollision_;

    bool collisionEnemy_;

};