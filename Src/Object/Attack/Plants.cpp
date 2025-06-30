
#include <DxLib.h>
#include "../Camera/Camera.h"
#include "Plants.h"

Plants::Plants(void)
{

	for (int i = 0; i < PLANTS_ANIM_FRAME; i++)
	{
		plantsImgs[i] = -1;
	}

	plantsPos.x = 0;
	plantsPos.y = 0;

	isPlants = false;

	plantsImgAnimCount = 0;

}
Plants::~Plants(void)
{

}
void Plants::Init(Camera* camera)
{
	camera_ = camera;

	LoadDivGraph("Data/Image/Attack/AttackP.png", PLANTS_ANIM_FRAME, PLANTS_DIV_X, 1, PLANTS_SIZE, PLANTS_SIZE, plantsImgs);

	isPlants = false;

	plantsImgAnimCount = 0;

	plantsPos.x = 0.0f;
	plantsPos.x = 0.0f;
}

void Plants::Update(void)
{

}
void Plants::Draw(void)
{
	if (isPlants)
	{
		count += 0.3f;
		if (count>2)
		{
			plantsImgAnimCount++;
			count = 0;
		}
		if (plantsImgAnimCount < 9)
		{

			/*DrawBillboard3D(
				plantsPos, plants_SIZE_X, plants_SIZE_Y, plants_Z, 0.0f,
				plantsImgs[plantsImgAnimCount], true);*/
			DrawRotaGraphF(plantsPos.x - camera_->GetCameraPos().x, plantsPos.y - camera_->GetCameraPos().y, 1.0f, 0.0f, plantsImgs[plantsImgAnimCount], TRUE);
		}
		else
		{

			isPlants = false;
			plantsImgAnimCount = 0;
		}
	}
}
void Plants::Release(void)
{

	for (int i = 0; i < PLANTS_ANIM_FRAME; i++)
	{
		DeleteGraph(plantsImgs[i]);
	}
}
bool Plants::GetIsPlants(void)
{

	return isPlants;
}
void Plants::SetIsPlants(bool is)
{

	isPlants = is;
}
Vector2 Plants::GetPlantsPos(void)
{

	return plantsPos;
}
void Plants::SetPlantsPos(Vector2 pos)
{

	plantsPos = pos;
}
