#include <DxLib.h>
#include "../../Application.h"
#include "../../Scene/GameScene.h"
#include "../Player/Player.h"
#include "Camera.h"

Camera::Camera()
{

}
Camera::~Camera()
{

}
void Camera::Init(Player*player)
{
	player_ = player;
	cameraPos_.x = Application::SCREEN_SIZE_X / 2;
	cameraPos_.y = Application::SCREEN_SIZE_Y / 2;
	
}
void Camera::Update()
{
	cameraPos_.x= static_cast<int>(player_->GetPlayerPos().x);
	
}
void Camera::Draw()
{

}

Vector2 Camera::GetCameraPos(void)
{
	return cameraPos_;
}
