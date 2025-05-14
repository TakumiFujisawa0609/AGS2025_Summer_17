#include <DxLib.h>
#include "../../Application.h"
#include "../../Common/Vector2.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "Player.h"


Player::Player()
{

}
Player::~Player()
{

}
void Player::Init()
{
	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	ResourceManager& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::PLAYERS).handleIds_;

	pos_.x = 0;
	pos_.y = 0;
}
void Player::Update()
{

}
void Player::Draw()
{
	// ‰æ‘œ‚Ì•`‰æ
	
	DrawGraph(pos_.x, pos_.y, img_[0], TRUE);

}
