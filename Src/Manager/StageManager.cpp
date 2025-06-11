#include "StageManager.h"
StageManager::StageManager()
{

}
StageManager::~StageManager()
{

}
void StageManager::Init()
{
	
}
void StageManager::Update()
{
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		break;
	case STAGE_TYPE::STAGE2:
		break;
	case STAGE_TYPE::STAGE3:
		break;

	}
}

void StageManager::Draw()
{
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		break;
	case STAGE_TYPE::STAGE2:
		break;
	case STAGE_TYPE::STAGE3:
		break;

	}

}

void StageManager::ChangeStage(STAGE_TYPE type)
{
	stageType = type;
	switch (stageType)
	{
	case STAGE_TYPE::STAGE1:
		break;
	case STAGE_TYPE::STAGE2:
		break;
	case STAGE_TYPE::STAGE3:
		break;

	}
}