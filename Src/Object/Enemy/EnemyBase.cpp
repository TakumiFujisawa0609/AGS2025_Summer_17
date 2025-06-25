#include "EnemyBase.h"
#include "EnemyFire.h"
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include <DxLib.h>

void EnemyBase::Init(Player* player, Camera* camera, Stage* stage)
{
	player_ = player;
	camera_ = camera;
	stage_ = stage;

	isFire_ = false;
	isWater_ = false;
	isPlant_ = false;
}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{
}