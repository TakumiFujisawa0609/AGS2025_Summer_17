


#include <DxLib.h>
#include "../../Application.h"

#include "../Camera/Camera.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/ResourceManager.h"
#include "../../Scene/GameScene.h"
#include "../Stage/Stage.h"
#include "Wall.h"

Wall::Wall()
{

}
Wall::~Wall()
{

}
void Wall::Init(Camera*camera)
{
	camera_ = camera;

	stageSize_ = Stage::CHIP_SIZE_X;

	ResourceManager& res = ResourceManager::GetInstance();

	//画像の取得
	plantsImg_ = res.Load(ResourceManager::SRC::PWALL).handleId_;
	flareImg_ = res.Load(ResourceManager::SRC::FWALL).handleIds_;
	waterImg_ = res.Load(ResourceManager::SRC::WWALL).handleIds_;
	wSphereImg_ = res.Load(ResourceManager::SRC::WSPHERE).handleIds_;

	
	Init2();

	

	//アニメーションカウントの初期化
	flareAnimCount_ = 0;
	waterAnimCount_ = 0;
	flareNo_ = 0;
	waterNo_ = 0;
	sphereNo_ = 0;
	
	
	
}
void Wall::Update()
{
	
	

	
}

void Wall::AnimUpdate()
{
	flareAnimCount_++;
	waterAnimCount_++;


	//植物のアニメーションはなし


	//フレアのアニメーション

	if (flareAnimCount_ >= 5) // 5フレームごとに切り替え
	{
		flareAnimCount_ = 0;
		flareNo_++;
		if (flareNo_ >= FLARE_ANIM_FRAME)
		{
			flareNo_ = 0; // アニメーションのループ
		}
	}



	//水のアニメーション

	if (waterAnimCount_ >= 5) // 5フレームごとに切り替え
	{
		waterAnimCount_ = 0;
		waterNo_++;
		if (waterNo_ >= WATER_ANIM_FRAME)
		{
			waterNo_ = 0; // アニメーションのループ
		}
	}



}

void Wall::Draw()
{
	
}

void Wall::Init1()
{
	//座標の初期化
	plantsPos_.x = stageSize_ * 49;
	plantsPos_.y = stageSize_ * 8;
	flarePos_.x = stageSize_ * 61;
	flarePos_.y = stageSize_ * 8;
	waterPos_.x = stageSize_ * 37;
	waterPos_.y = stageSize_ * 8;
	spherePos_.x = stageSize_ * 38;
	spherePos_.y = stageSize_ * 7;

	//生存フラグの初期化
	isPlantsAlive_ = true;
	isFlareAlive_ = true;
	isWaterAlive_ = true;
	isSphereAlive_ = true;
}

void Wall::Update1()
{
	AnimUpdate();
	if (isSphereAlive_)
	{

	}
	else
	{
		isWaterAlive_ = false;
	}
}

void Wall::Draw1()
{
	Vector2 cameraPos = camera_->GetCameraPos();
	//植物の描画
	if (isPlantsAlive_)
	{
		DrawGraph(plantsPos_.x - cameraPos.x, plantsPos_.y - cameraPos.y, plantsImg_, TRUE);



	}

	if (isFlareAlive_)
	{
		DrawGraph(flarePos_.x - cameraPos.x, flarePos_.y - cameraPos.y, flareImg_[flareNo_], TRUE);
	}

	//水の描画
	if (isWaterAlive_)
	{
		DrawGraph(waterPos_.x - cameraPos.x, waterPos_.y - cameraPos.y, waterImg_[waterNo_], TRUE);
	}
	//DrawBox(waterPos_.x + cameraPos, waterPos_.y, waterPos_.x + WATER_SIZE_X + cameraPos, waterPos_.y + WATER_SIZE_Y,0x000000,true);
	//水晶
	if (isSphereAlive_)
	{
		DrawGraph(spherePos_.x - cameraPos.x, spherePos_.y - cameraPos.y, wSphereImg_[0], TRUE);
	}
	else
	{

		DrawGraph(spherePos_.x - cameraPos.x, spherePos_.y - cameraPos.y, wSphereImg_[1], TRUE);
	}

}

void Wall::Init2()
{
	//座標の初期化
	plantsPos_.x = stageSize_ * stageSize_;
	plantsPos_.y = stageSize_ * 18;
	flarePos_.x = stageSize_ * 77;
	flarePos_.y = stageSize_ * 12;
	waterPos_.x = stageSize_ * 25;
	waterPos_.y = stageSize_ * 19;
	spherePos_.x = stageSize_ * 62;
	spherePos_.y = stageSize_ * 10;

	//座標の初期化
	plantsPos2_.x = stageSize_ * 74;
	plantsPos2_.y = stageSize_ * 4;
	flarePos2_.x = stageSize_ * 60;
	flarePos2_.y = stageSize_ * 13;
	waterPos2_.x = stageSize_ * 94;
	waterPos2_.y = stageSize_ * 14;
	spherePos2_.x = stageSize_ * 1;
	spherePos2_.y = stageSize_ * 22;

	//座標の初期化
	plantsPos3_.x = stageSize_ * 60;
	plantsPos3_.y = stageSize_ * 8;
	flarePos3_.x = stageSize_ * 32;
	flarePos3_.y = stageSize_ * 8;
	waterPos3_.x = stageSize_ * 76;
	waterPos3_.y = stageSize_ * 20;
	spherePos3_.x = stageSize_ * 98;
	spherePos3_.y = stageSize_ * 22;

	//生存フラグの初期化
	isPlantsAlive_ = true;
	isFlareAlive_ = true;
	isWaterAlive_ = true;
	isSphereAlive_ = true;
	//生存フラグの初期化
	isPlantsAlive2_ = true;
	isFlareAlive2_ = true;
	isWaterAlive2_ = true;
	isSphereAlive2_ = true;
	//生存フラグの初期化
	isPlantsAlive3_ = true;
	isFlareAlive3_ = true;
	isWaterAlive3_ = true;
	isSphereAlive3_ = true;

	reWallF_=180;
	reWallP_=210;
	reWallS_=600;
	reWallF2_ = 180;
	reWallP2_ = 210;
	reWallS2_ = 600;
	reWallF3_ = 180;
	reWallP3_ = 210;
	reWallS3_ = 600;
}

void Wall::Update2()
{
	if (isPlantsAlive_==false)
	{
		reWallP_--;
		if (reWallP_ <= 0)
		{
			isPlantsAlive_ = true;
			reWallP_ = 210;
		}
	}
	if (isPlantsAlive2_ == false)
	{
		reWallP2_--;
		if (reWallP2_ <= 0)
		{
			isPlantsAlive2_ = true;
			reWallP2_ = 210;
		}
	}
	if (isPlantsAlive3_ == false)
	{
		reWallP3_--;
		if (reWallP3_ <= 0)
		{
			isPlantsAlive3_ = true;
			reWallP3_ = 210;
		}
	}
	if (isFlareAlive_ == false)
	{
		reWallF_--;
		if (reWallF_ <= 0)
		{
			isFlareAlive_ = true;
			reWallF_ = 210;
		}
	}
	if (isFlareAlive2_ == false)
	{
		reWallF2_--;
		if (reWallF2_ <= 0)
		{
			isFlareAlive2_ = true;
			reWallF2_ = 210;
		}
	}
	if (isFlareAlive3_ == false)
	{
		reWallF3_--;
		if (reWallF3_ <= 0)
		{
			isFlareAlive3_ = true;
			reWallF3_ = 210;
		}
	}
	if (isSphereAlive_ == false)
	{
		reWallS_--;
		if (reWallS_ <= 0)
		{
			isSphereAlive_ = true;
			reWallS_ = 600;
		}
	}
	if (isSphereAlive2_ == false)
	{
		reWallS2_--;
		if (reWallS2_ <= 0)
		{
			isSphereAlive2_ = true;
			reWallS2_ = 600;
		}
	}
	if (isSphereAlive3_ == false)
	{
		reWallS3_--;
		if (reWallS3_ <= 0)
		{
			isSphereAlive3_ = true;
			reWallS3_ = 600;
		}
	}



	AnimUpdate();
	if (isSphereAlive_)
	{
		isWaterAlive3_ = true;
	}
	else
	{
		isWaterAlive3_ = false;
	}
	if (isSphereAlive2_)
	{
		isWaterAlive_ = true;
	}
	else
	{
		isWaterAlive_ = false;

		
	}
	if (isSphereAlive3_)
	{
		isWaterAlive2_ = true;
	}
	else
	{
		
		isWaterAlive2_ = false;
	}
}

void Wall::Draw2()
{
	Vector2 cameraPos = camera_->GetCameraPos();
	if (isPlantsAlive_ == true)
	{
		DrawGraph(plantsPos_.x - cameraPos.x, plantsPos_.y - cameraPos.y, plantsImg_, TRUE);
	}
	if (isPlantsAlive2_ == true)
	{
		DrawGraph(plantsPos2_.x - cameraPos.x, plantsPos2_.y - cameraPos.y, plantsImg_, TRUE);
	}
	if (isPlantsAlive3_ == true)
	{
		DrawGraph(plantsPos3_.x - cameraPos.x, plantsPos3_.y - cameraPos.y, plantsImg_, TRUE);
	}

	if (isFlareAlive_ == true)
	{
		DrawGraph(flarePos_.x - cameraPos.x, flarePos_.y - cameraPos.y, flareImg_[flareNo_], TRUE);
	}
	if (isFlareAlive2_ == true)
	{
		DrawGraph(flarePos2_.x - cameraPos.x, flarePos2_.y - cameraPos.y, flareImg_[flareNo_], TRUE);
	}
	if (isFlareAlive3_ == true)
	{
		DrawGraph(flarePos3_.x - cameraPos.x, flarePos3_.y - cameraPos.y, flareImg_[flareNo_], TRUE);
	}

	if (isWaterAlive_ == true)
	{
		DrawGraph(waterPos_.x - cameraPos.x, waterPos_.y - cameraPos.y, waterImg_[waterNo_], TRUE);
	}
	if (isWaterAlive2_ == true)
	{
		DrawGraph(waterPos2_.x - cameraPos.x, waterPos2_.y - cameraPos.y, waterImg_[waterNo_], TRUE);
	}
	if (isWaterAlive3_ == true)
	{
		DrawGraph(waterPos3_.x - cameraPos.x, waterPos3_.y - cameraPos.y, waterImg_[waterNo_], TRUE);
	}

	if (isSphereAlive_ == true)
	{
		DrawGraph(spherePos_.x - cameraPos.x, spherePos_.y - cameraPos.y, wSphereImg_[0], TRUE);
	}
	else
	{
		DrawGraph(spherePos_.x - cameraPos.x, spherePos_.y - cameraPos.y, wSphereImg_[1], TRUE);
	}
	if (isSphereAlive2_ == true)
	{
		DrawGraph(spherePos2_.x - cameraPos.x, spherePos2_.y - cameraPos.y, wSphereImg_[0], TRUE);
	}
	else
	{
		DrawGraph(spherePos2_.x - cameraPos.x, spherePos2_.y - cameraPos.y, wSphereImg_[1], TRUE);
	}
	if (isSphereAlive3_ == true)
	{
		DrawGraph(spherePos3_.x - cameraPos.x, spherePos3_.y - cameraPos.y, wSphereImg_[0], TRUE);

	}
	else
	{
		DrawGraph(spherePos3_.x - cameraPos.x, spherePos3_.y - cameraPos.y, wSphereImg_[1], TRUE);
	}
}

//Get,Set
Vector2F Wall::GetPlantsPos() 
{
	return plantsPos_;
}
Vector2F Wall::GetFlarePos() 
{
	return flarePos_;
}
Vector2F Wall::GetWaterPos() 
{
	return waterPos_;
}
Vector2F Wall::GetPlantsPos2()
{
	return plantsPos2_;
}
Vector2F Wall::GetFlarePos2()
{
	return flarePos2_;
}
Vector2F Wall::GetWaterPos2()
{
	return waterPos2_;
}
Vector2F Wall::GetPlantsPos3()
{
	return plantsPos3_;
}
Vector2F Wall::GetFlarePos3()
{
	return flarePos3_;
}
Vector2F Wall::GetWaterPos3()
{
	return waterPos3_;
}
bool Wall::IsPlantsAlive() 
{
	return isPlantsAlive_;
}
bool Wall::IsFlareAlive() 
{
	return isFlareAlive_;
}
bool Wall::IsWaterAlive() 
{
	return isWaterAlive_;
}
void Wall::SetPlantsPos( Vector2F pos)
{
	plantsPos_ = pos;
}
void Wall::SetFlarePos( Vector2F pos)
{
	flarePos_ = pos;
}
void Wall::SetWaterPos( Vector2F pos)
{
	waterPos_ = pos;
}
void Wall::SetIsPlants(bool isAlive)
{
	isPlantsAlive_ = isAlive;
}
void Wall::SetIsFlare(bool isAlive)
{
	isFlareAlive_ = isAlive;
}
void Wall::SetIsWater(bool isAlive)
{
	isWaterAlive_ = isAlive;
}

void Wall::SetIsSphere(bool isAlive)
{
	isSphereAlive_ = isAlive;
}

void Wall::SetIsPlants2(bool isAlive)
{
	isPlantsAlive2_ = isAlive;
}

void Wall::SetIsFlare2(bool isAlive)
{
	isFlareAlive2_ = isAlive;
}

void Wall::SetIsWater2(bool isAlive)
{
	isWaterAlive2_ = isAlive;
}

void Wall::SetIsSphere2(bool isAlive)
{
	isSphereAlive2_ = isAlive;
}

void Wall::SetIsPlants3(bool isAlive)
{
	isPlantsAlive3_ = isAlive;
}

void Wall::SetIsFlare3(bool isAlive)
{
	isFlareAlive3_ = isAlive;
}

void Wall::SetIsWater3(bool isAlive)
{
	isWaterAlive3_ = isAlive;
}

void Wall::SetIsSphere3(bool isAlive)
{
	isSphereAlive3_ = isAlive;
}

bool Wall::IsWaterCollision(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isWaterAlive_)
	{

		if (pPos.x > waterPos_.x && pPos.y > waterPos_.y && pPos.x < waterPos_.x + WATER_SIZE_X && pPos.y < waterPos_.y + WATER_SIZE_Y + WATER_SIZE_X)
		{
			return true;
		}
	}
	return false;
}
bool Wall::IsFlaereCollision(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isFlareAlive_)
	{
		if (pPos.x > flarePos_.x && pPos.y > flarePos_.y && pPos.x < flarePos_.x + FLARE_SIZE_X && pPos.y < flarePos_.y + FLARE_SIZE_Y + FLARE_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsPlantsCollision(Vector2 pos)
{
	Vector2 pPos = pos;

	if(isPlantsAlive_)
	{
		if (pPos.x > plantsPos_.x && pPos.y > plantsPos_.y && pPos.x < plantsPos_.x + PLANTS_SIZE_X && pPos.y < plantsPos_.y + PLANTS_SIZE_Y + PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsSphereCollision(Vector2 pos)
{
	Vector2 pPos = pos;

	if (isSphereAlive_)
	{
		if (pPos.x > spherePos_.x && pPos.y > spherePos_.y && pPos.x < spherePos_.x + PLANTS_SIZE_X && pPos.y < spherePos_.y+PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsWaterCollision2(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isWaterAlive2_)
	{

		if (pPos.x > waterPos2_.x && pPos.y > waterPos2_.y && pPos.x < waterPos2_.x + WATER_SIZE_X && pPos.y < waterPos2_.y + WATER_SIZE_Y + WATER_SIZE_X)
		{
			return true;
		}
	}
	return false;
}
bool Wall::IsFlaereCollision2(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isFlareAlive2_)
	{
		if (pPos.x > flarePos2_.x && pPos.y > flarePos2_.y && pPos.x < flarePos2_.x + FLARE_SIZE_X && pPos.y < flarePos2_.y + FLARE_SIZE_Y + FLARE_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsPlantsCollision2(Vector2 pos)
{
	Vector2 pPos = pos;

	if (isPlantsAlive2_)
	{
		if (pPos.x > plantsPos2_.x && pPos.y > plantsPos2_.y && pPos.x < plantsPos2_.x + PLANTS_SIZE_X && pPos.y < plantsPos2_.y + PLANTS_SIZE_Y + PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsSphereCollision2(Vector2 pos)
{
	Vector2 pPos = pos;

	if (isSphereAlive2_)
	{
		if (pPos.x > spherePos2_.x && pPos.y > spherePos2_.y && pPos.x < spherePos2_.x + PLANTS_SIZE_X && pPos.y < spherePos2_.y + PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsWaterCollision3(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isWaterAlive3_)
	{

		if (pPos.x > waterPos3_.x && pPos.y > waterPos3_.y && pPos.x < waterPos3_.x + WATER_SIZE_X && pPos.y < waterPos3_.y + WATER_SIZE_Y + WATER_SIZE_X)
		{
			return true;
		}
	}
	return false;
}
bool Wall::IsFlaereCollision3(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isFlareAlive3_)
	{
		if (pPos.x > flarePos3_.x && pPos.y > flarePos3_.y && pPos.x < flarePos3_.x + FLARE_SIZE_X && pPos.y < flarePos3_.y + FLARE_SIZE_Y + FLARE_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsPlantsCollision3(Vector2 pos)
{
	Vector2 pPos = pos;

	if (isPlantsAlive3_)
	{
		if (pPos.x > plantsPos3_.x && pPos.y > plantsPos3_.y && pPos.x < plantsPos3_.x + PLANTS_SIZE_X && pPos.y < plantsPos3_.y + PLANTS_SIZE_Y + PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
bool Wall::IsSphereCollision3(Vector2 pos)
{
	Vector2 pPos = pos;

	if (isSphereAlive3_)
	{
		if (pPos.x > spherePos3_.x && pPos.y > spherePos3_.y && pPos.x < spherePos3_.x + PLANTS_SIZE_X && pPos.y < spherePos3_.y + PLANTS_SIZE_X)
		{
			return true;
		}

	}

	return false;
}
