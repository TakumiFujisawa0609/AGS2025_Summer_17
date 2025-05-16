#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Scene/GameScene.h"
#include "../Player/Player.h"
#include "Camera.h"

Camera::Camera()
{

}
Camera::~Camera()
{

}
void Camera::Init(Player*player,GameScene*gameScene)
{
	
	gameScene_ = gameScene;
	player_ = player;
	cameraPos_.x = Application::SCREEN_SIZE_X / 2;
	cameraPos_.y = Application::SCREEN_SIZE_Y / 2;
	
}
void Camera::Update()
{
	//移動スピード
	constexpr int SPEED_CAMERA = 8;

	/*カメラ座標を移動させる
	if (CheckHitKey(KEY_INPUT_I))
	{
		cameraPos_.y -= SPEED_CAMERA;
	}
	
	if (CheckHitKey(KEY_INPUT_K))
	{
		cameraPos_.y += SPEED_CAMERA;
	}
	
	if (CheckHitKey(KEY_INPUT_J))
	{
		cameraPos_.x -= SPEED_CAMERA;
	}
	
	if (CheckHitKey(KEY_INPUT_L))
	{
		cameraPos_.x += SPEED_CAMERA;
	}*/
	






	//プレイヤー座標
	Vector2 playerPos = AsoUtility::Raund(player_->GetPlayerPos());
	//カメラの左枠処理
	//カメラ左側よりプレイヤーが左に進んだら
	if (playerPos.x < cameraPos_.x + FOCAS_X)
	{
		cameraPos_.x = playerPos.x - FOCAS_X;
		if (cameraPos_.x < 0)
		{
			cameraPos_.x = 0;
		}
	}

	//カメラに映る範囲の右側座標
	int cameraRightSidePosX = cameraPos_.x + Application::SCREEN_SIZE_X;

	//カメラの右枠処理
	//カメラの右側よりプレイヤーが→に行ったらカメラを動かす
	
	if (cameraPos_.x + Application::SCREEN_SIZE_X - FOCAS_X < playerPos.x)
	{
		cameraPos_.x = (playerPos.x - Application::SCREEN_SIZE_X) + FOCAS_X;
		if (cameraPos_.x + Application::SCREEN_SIZE_X > (32 * 30))
		{
			cameraPos_.x= (32 * 30)-Application::SCREEN_SIZE_X;
		}
	}
	if (cameraRightSidePosX - FOCAS_X < playerPos.x)
	{
		cameraPos_.x = (playerPos.x - Application::SCREEN_SIZE_X) + FOCAS_X;
		if (cameraRightSidePosX > (32 * 30))
		{
			cameraPos_.x = (32 * 30) - Application::SCREEN_SIZE_X;
		}
	}

	//カメラの上側処理
	//カメラの上側座標よりプレイヤーが上に行っていたら
	//if (playerPos.y < cameraPos_.y + FOCAS_Y)
	//{
	//	//カメラ座標をプレイヤーの座標にする
	//	cameraPos_.y = playerPos.y - FOCAS_Y;
	//	if (cameraPos_.y < 0)
	//	{
	//		cameraPos_.y = 0;
	//	}
	//}
	////カメラに移る範囲の右枠X座標
	//int cameraDownSidePosY = cameraPos_.y + Application::SCREEN_SIZE_Y;

	////カメラの下枠処理
	//
	//if (cameraPos_.y + Application::SCREEN_SIZE_Y - FOCAS_Y < playerPos.y)
	//{
	//	cameraPos_.y = (playerPos.y - Application::SCREEN_SIZE_Y) + FOCAS_Y;
	//	if (cameraPos_.y + Application::SCREEN_SIZE_Y > (32 * 30))
	//	{
	//		cameraPos_.y = (32 * 30)- Application::SCREEN_SIZE_Y;
	//	}
	//}

	//if (cameraDownSidePosY - FOCAS_Y < playerPos.y)
	//{
	//	cameraPos_.y = (playerPos.y - Application::SCREEN_SIZE_Y) + FOCAS_Y;
	//	if (cameraDownSidePosY > (32 * 30))
	//	{
	//		cameraPos_.y = (32 * 30) - Application::SCREEN_SIZE_Y;
	//	}
	//}
	GetCameraPos();
}
void Camera::Draw()
{

}

Vector2 Camera::GetCameraPos(void)
{
	return cameraPos_;
}
