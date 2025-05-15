#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
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
	Move();
}
void Player::Draw()
{
	// ‰æ‘œ‚Ì•`‰æ
	
	DrawGraph(pos_.x, pos_.y, img_[0], TRUE);

}
void Player::Move()
{
	//ˆÚ“®ˆ—
	InputManager& ins = InputManager::GetInstance();

	
	if (ins.IsNew(KEY_INPUT_W))
	{
		pos_.y -= 5;	
	}
	if (ins.IsNew(KEY_INPUT_S))
	{
		pos_.y += 5;
	}
	if (ins.IsNew(KEY_INPUT_A))
	{
		pos_.x -= 5;
	}
	if (ins.IsNew(KEY_INPUT_D))
	{
		pos_.x += 5;
	}

}