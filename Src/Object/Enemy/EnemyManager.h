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
class EnemyWater;
class EnemyAttackF;
class EnemyAttackP;
class EnemyAttackW;
class Camera;
class Player;
class Stage;
class Blast;
class Plants;
class Water;



class EnemyManager {
public:

    // 初期化
    void Init(EnemyFire* enemyFire, EnemyPlant* enemyPlant, EnemyWater* enemyWater,
        EnemyAttackF* enemyAttackF, EnemyAttackP* enemyAttackP, EnemyAttackW* enemyAttackW,
        Player* player, Camera* camera, Stage* stage, Blast* blast, Plants* plants, Water* water);
    // 更新
    void Update();
    // 描画
    void Draw();
    // エネミーの当たり判定
    void CollisionAttack();

    // エネミーの当たり判定管理の取得・更新
    bool GetCollisionEnemy();
    void SetCollisionEnemy(bool collisionEnemy);

private:

    EnemyBase* enemyBase_;
    EnemyFire* enemyFire_;
    EnemyPlant* enemyPlant_;
    EnemyWater* enemyWater_;
    EnemyAttackF* enemyAttackF_;
    EnemyAttackP* enemyAttackP_;
    EnemyAttackW* enemyAttackW_;
    Player* player_;
    Camera* camera_;
    Stage* stage_;
    Blast* blast_;
    Plants* plants_;
    Water* water_;

    // 各種エネミーの当たり判定
    bool fireCollision_;
    bool plantCollision_;
    bool waterCollision_;

    // エネミーの当たり判定管理
    bool collisionEnemy_;

};