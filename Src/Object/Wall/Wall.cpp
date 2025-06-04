


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
	ResourceManager& res = ResourceManager::GetInstance();

	//画像の取得
	plantsImg_ = res.Load(ResourceManager::SRC::PWALL).handleId_;
	flareImg_ = res.Load(ResourceManager::SRC::FWALL).handleIds_;
	waterImg_ = res.Load(ResourceManager::SRC::WWALL).handleIds_;
	wSphereImg_ = res.Load(ResourceManager::SRC::WSPHERE).handleIds_;

	//座標の初期化
	plantsPos_.x = 64*49;
	plantsPos_.y = 64*8;
	flarePos_.x = 64*61;
	flarePos_.y = 64*8;
	waterPos_.x = 64*37;
	waterPos_.y = 64*8;
	spherePos_.x = 64 * 38;
	spherePos_.y = 64 * 7;



	//生存フラグの初期化
	isPlantsAlive_ = true;
	isFlareAlive_ = true;
	isWaterAlive_ = true;
	isSphereAlive_ = true;

	//アニメーションカウントの初期化
	flareAnimCount_ = 0;
	waterAnimCount_ = 0;
	flareNo_ = 0;
	waterNo_ = 0;
	sphereNo_ = 0;
	
	
	
}
void Wall::Update()
{
	
	AnimUpdate();

	
}

void Wall::AnimUpdate()
{
	flareAnimCount_++;
	waterAnimCount_++;


	//植物のアニメーションはなし


	//フレアのアニメーション
	if (isFlareAlive_)
	{
		if (flareAnimCount_ >= 5) // 5フレームごとに切り替え
		{
			flareAnimCount_ = 0;
			flareNo_++;
			if (flareNo_ >= FLARE_ANIM_FRAME)
			{
				flareNo_ = 0; // アニメーションのループ
			}
		}
		
	}

	//水のアニメーション
	if (isWaterAlive_)
	{
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
	if (isSphereAlive_)
	{

	}
	else
	{
		isWaterAlive_ = false;
	}
}

void Wall::Draw()
{
	float cameraPos = camera_->GetCameraPos().x;
	//植物の描画
	if (isPlantsAlive_)
	{
		DrawGraph(plantsPos_.x- cameraPos, plantsPos_.y, plantsImg_, TRUE);


		
	}
	
	if (isFlareAlive_)
	{
		DrawGraph(flarePos_.x- cameraPos, flarePos_.y, flareImg_[flareNo_], TRUE);
	}

	//水の描画
	if (isWaterAlive_)
	{
		DrawGraph(waterPos_.x- cameraPos, waterPos_.y, waterImg_[waterNo_], TRUE);
	}
	//DrawBox(waterPos_.x + cameraPos, waterPos_.y, waterPos_.x + WATER_SIZE_X + cameraPos, waterPos_.y + WATER_SIZE_Y,0x000000,true);
	//水晶
	if (isSphereAlive_) 
	{
		DrawGraph(spherePos_.x - cameraPos, spherePos_.y, wSphereImg_[0], TRUE);
	}
	else
	{
		
		DrawGraph(spherePos_.x - cameraPos, spherePos_.y, wSphereImg_[1], TRUE);
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

bool Wall::IsWaterCollision(Vector2 pos)
{
	Vector2 pPos = pos;
	if (isWaterAlive_)
	{

		if (pPos.x > waterPos_.x && pPos.y > waterPos_.y + WATER_SIZE_X && pPos.x < waterPos_.x + WATER_SIZE_X && pPos.y < waterPos_.y + WATER_SIZE_Y + WATER_SIZE_X)
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
		if (pPos.x > flarePos_.x && pPos.y > flarePos_.y + FLARE_SIZE_X && pPos.x < flarePos_.x + FLARE_SIZE_X && pPos.y < flarePos_.y + FLARE_SIZE_Y + FLARE_SIZE_X)
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
		if (pPos.x > plantsPos_.x && pPos.y > plantsPos_.y + PLANTS_SIZE_X && pPos.x < plantsPos_.x + PLANTS_SIZE_X && pPos.y < plantsPos_.y + PLANTS_SIZE_Y + PLANTS_SIZE_X)
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