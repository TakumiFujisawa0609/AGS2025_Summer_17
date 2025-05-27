


#include <DxLib.h>
#include "../../Application.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
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
void Wall::Init()
{
	ResourceManager& res = ResourceManager::GetInstance();

	//画像の取得
	plantsImg_ = res.Load(ResourceManager::SRC::PWALL).handleId_;
	flareImg_ = res.Load(ResourceManager::SRC::FWALL).handleIds_;
	waterImg_ = res.Load(ResourceManager::SRC::WWALL).handleIds_;

	//座標の初期化
	plantsPos_.x = 96.0f;
	plantsPos_.y = 96.0f+48.0f;
	flarePos_.x = 96.0f*2;
	flarePos_.y = 96.0f + 48.0f;
	waterPos_.x = 0.0f;
	waterPos_.y = 96.0f + 48.0f;

	//生存フラグの初期化
	isPlantsAlive_ = true;
	isFlareAlive_ = true;
	isWaterAlive_ = true;

	//アニメーションカウントの初期化
	flareAnimCount_ = 0;
	waterAnimCount_ = 0;
	flareNo_ = 0;
	waterNo_ = 0;
	
	
	
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
}

void Wall::Draw()
{
	//植物の描画
	if (isPlantsAlive_)
	{
		DrawGraph(plantsPos_.x, plantsPos_.y, plantsImg_, TRUE);
	}

	//フレアの描画
	if (isFlareAlive_)
	{
		DrawGraph(flarePos_.x, flarePos_.y, flareImg_[flareNo_], TRUE);
	}

	//水の描画
	if (isWaterAlive_)
	{
		DrawGraph(waterPos_.x, waterPos_.y, waterImg_[waterNo_], TRUE);
	}
	
}

//Get,Set
Vector2F Wall::GetPlantsPos() const
{
	return plantsPos_;
}
Vector2F Wall::GetFlarePos() const
{
	return flarePos_;
}
Vector2F Wall::GetWaterPos() const
{
	return waterPos_;
}
bool Wall::IsPlantsAlive() const
{
	return isPlantsAlive_;
}
bool Wall::IsFlareAlive() const
{
	return isFlareAlive_;
}
bool Wall::IsWaterAlive() const
{
	return isWaterAlive_;
}
void Wall::SetPlantsPos(const Vector2F& pos)
{
	plantsPos_ = pos;
}
void Wall::SetFlarePos(const Vector2F& pos)
{
	flarePos_ = pos;
}
void Wall::SetWaterPos(const Vector2F& pos)
{
	waterPos_ = pos;
}
