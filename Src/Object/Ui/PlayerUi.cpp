
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
	ResourceManager& res = ResourceManager::GetInstance();
	hpUi_= res.Load(ResourceManager::SRC::HPUI).handleId_;

	uiPos_.x = HP_UI_HALFSIZE_X;
	uiPos_.y = HP_UI_HALFSIZE_Y;

}
void PlayerUi::Update()
{
	
}
void PlayerUi::Draw()
{
	DrawBox(0, 0, 64 * 120, 64 * 2, 0x000000, true);
	DrawRotaGraph(uiPos_.x, uiPos_.y, 1.0f, 0.0f, hpUi_, true);
}