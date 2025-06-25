
#include <DxLib.h>
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "../Player/Player.h"
#include "PlayerUi.h"


PlayerUi::PlayerUi()
{
	
}
PlayerUi::~PlayerUi()
{

}

void PlayerUi::Init(Player*player)
{
	player_ = player;

	stageSize_ = player_->GetStageSize();
	ResourceManager& res = ResourceManager::GetInstance();
	hpUi_= res.Load(ResourceManager::SRC::HPUI).handleId_;

	uiPos_.x = HP_UI_HALFSIZE_X;
	uiPos_.y = HP_UI_HALFSIZE_Y;

	crPos_.x = uiPos_.x + stageSize_ * 2;
	crPos_.y = uiPos_.y + stageSize_ * 2;

	hpPos_.x = uiPos_.x + stageSize_ * 3;
	hpPos_.y = uiPos_.y + stageSize_ * 2;

	mpPos_.x = uiPos_.x + stageSize_ * 4;
	mpPos_.y = uiPos_.y + stageSize_ * 2;



}
void PlayerUi::Update()
{
	
}
void PlayerUi::Draw()
{
	

	
	float hpS_ = 0.0f;

	hpS_ = static_cast<float>(player_->GetHp()) / static_cast<float>(player_->MAX_HP);

	float hpDrawS_ = 0.0f;
	hpDrawS_ = static_cast<float>(stageSize_*6) * hpS_;

	float mpS_ = 0.0f;

	mpS_ = static_cast<float>(player_->GetMp()) / static_cast<float>(player_->MAX_MP);

	float mpDrawS_ = 0.0f;
	mpDrawS_ = static_cast<float>(stageSize_ * 6) * mpS_;

	
	
	DrawBox(0, 0, stageSize_ * 120, stageSize_ * 2, 0x000000, true);
	DrawCircle(52, stageSize_, 50, player_->GetCr(), true);
	DrawRotaGraph(uiPos_.x, uiPos_.y, 1.0f, 0.0f, hpUi_, true);
	DrawBox(stageSize_*2-10, 16, static_cast<int>(hpDrawS_)+(stageSize_ * 2 - 10), 50, 0xFF0000, true);
	DrawBox(stageSize_ * 2 - 10, 56, static_cast<int>(mpDrawS_) + (stageSize_ * 2 - 10), 90, 0x0000FF, true);
	

	
}