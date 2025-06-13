#include <DxLib.h>
#include <math.h>
#include "../../Application.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/InputManager.h"
#include "../Wall/Wall.h"
#include "../Attack/Blast.h"
#include "../Attack/Water.h"
#include "../Attack/Plants.h"
#include "Player.h"


Player::Player()
{
	isHitFoot_ = false;
	isHitHead_ = false;
	isHitRightSide_ = false;
	isHitLeftSide_ = false;

}
Player::~Player()
{

}
void Player::Init(Camera* camera, Stage* stage, Wall* wall, Blast* blast, Water* water, Plants* plants)
{

	//カメラの取得
	camera_ = camera;

	//ステージの取得
	stage_ = stage;

	//壁の取得
	wall_ = wall;

	blast_ = blast;

	water_ = water;

	plants_ = plants;

	// 画像の読み込み
	ResourceManager& res = ResourceManager::GetInstance();
	img_ = res.Load(ResourceManager::SRC::PLAYERS).handleIds_;

	armImg_ = res.Load(ResourceManager::SRC::PLAYERARM).handleIds_;


	
	// 初期位置設定
	pos_.x = 64*2;
	pos_.y = 64*8;
	
	//アニメーション初期化
	armAngle_= AsoUtility::Deg2RadF(0.0f);
	animationTime_ = 0.0f;
	animationCount_ = 0;

	//移動タイプ
	moveType_ = MOVE_TYPE::STOP;
	
	//属性タイプ
	elementType_ = ELEMENT_TYPE::NORMAL;
	cr_ = 0xffffff;
	



	//攻撃
	isAttack_ = true;
	isPoint_ = false;
	dirChange_ = true;
	attackPos_.x = 0;
	attackPos_.y = 0;
	movePos = 0.0f;
	//攻撃ポイント(Init)
	attckAnglePoint_.x = 0;
	attckAnglePoint_.y = 0;

	/*attckPoint_.x = pos_.x + cosf(armAngle_) * 100;
	attckPoint_.y = pos_.y + cosf(armAngle_) * 100;*/

	id_ = 0;

	hp_ = MAX_HP;
	mp_ = MAX_MP;

}
void Player::Update()
{
	
	id_=stage_->GetStageId();


	MoveChange();

	Move();

	Anime();

	Attack();

	ElementChange();



}
void Player::Draw()
{
	// 画像の描画
	Vector2 cpos= camera_->GetCameraPos();
	DrawRotaGraphF((pos_.x)-cpos.x, (pos_.y) - cpos.y, 1.0f, 0.0f, img_[animationCount_], TRUE, dir_ == AsoUtility::DIR::LEFT);

	//腕の描画
	//色変更
	//GraphFilter(armImg_, DX_GRAPH_FILTER_HSB, cr, cr,cr,cr);
	
 	DrawRotaGraphF((pos_.x)-cpos.x, (pos_.y) - cpos.y, 1.0f, armAngle_, armImg_[animaAem_], TRUE);
	

	/*DrawGraph((pos_.x-HALF_COL_SIZE_X)-cpos.x, (pos_.y-HALF_COL_SIZE_Y), img_[animationCount_], TRUE,dir_ = AsoUtility::DIR::LEFT);*/
	DrawCircle(attckPoint_.x - cpos.x, attckPoint_.y - cpos.y, 5, cr_);
	DrawCircle(attckAnglePoint_.x - cpos.x, attckAnglePoint_.y - cpos.y, 5, cr_);
	if (isPoint_)
	{
		DrawCircle(attackPos_.x - cpos.x, attackPos_.y - cpos.y, 5, cr_);
	}
#ifdef _DEBUG
	//当たり判定の可視化
	DrawHitCollision();

	

#endif // DEBUG

}



//プレイヤーの機能処理==========================================================================================================================================================================

//移動処理
void Player::Move()
{
	//移動処理
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsNew(KEY_INPUT_LSHIFT))
	{
		speed_ = MOVE_ACC_POW * 3;
		maxSpeed_ = MAX_MOVE_SPEED * 3;
	}
	else
	{
		speed_ = MOVE_SPEED;
		maxSpeed_ = MAX_MOVE_SPEED;
	}

	if (ins.IsTrgDown(KEY_INPUT_D) || ins.IsTrgDown(KEY_INPUT_A))
	{
		animationCount_ = 6;
		moveType_ = MOVE_TYPE::MOVE;

	}

	//前回の座標を持っておく
	Vector2F prePos = pos_;

	// 移動処理
	// ジャンプボタンを押したら
	if (ins.IsNew(KEY_INPUT_SPACE) && !isJump_)
	{
		//ジャンプ力を設定する
		movePosY_ = JUMP_POW;

		//ジャンプフラグ
		isJump_ = true;
		//ジャンプアニメーション再生
		//ChangeAnimState(ANIM_STATE::JUNP, true);
	}
	//上限移動増加量
	pos_.y += movePosY_;

	//重力加算
	movePosY_ += GRAVITY;

	//上下移動量が最大重力にならないようにする
	if (movePosY_ > MAX_GRAVITY)
	{
		movePosY_ = MAX_GRAVITY;
	}

	//上への移動処理
	//デバッグ表示用に一回計算する
	//完成品では消してよし
	CalcHeadPos();
	isHitHead_ = IsHitHeadPos();

	//上に移動していたら頭と衝突判定
	if (prePos.y > pos_.y)CollisionHead();


	//下への移動処理
	//デバッグ表示用に一回計算する
	//完成品では消してよし
	CalcFootPos();
	isHitFoot_ = IsHitFootPos();

	//下に移動していたら足元と衝突判定
	if (prePos.y < pos_.y)CollisionFoot();
	
	//左への移動処理
	if (ins.IsNew(KEY_INPUT_A))
	{
		

		
		//左を向ける
		dir_ = AsoUtility::DIR::LEFT;
		//加速量を加算する
		movePosX_ -= speed_;

		//移動量
		if (movePosX_ < -maxSpeed_)
		{
			movePosX_ = -maxSpeed_;
		}
		pos_.x += movePosX_;
		//地上にいるときは走るアニメモーション再生
		if (!isJump_)
		{
			//ChangeAnimState(ANIM_STATE::RUN, false);
		}
	}


	//地上にいるときに移動ボタンが離されたら待機アニメーション再生
	//if (ins.IsNew(KEY_INPUT_A) && !isJump_)
	//{
		//ChangeAnimState(ANIM_STATE::IDLE, true);
	//}
	//スピードが出ているときは原則も同時に行う
	if (movePosX_ < 0.0f)
	{
		movePosX_ += MOVE_DEC_POW;

		//原則を０以下にはしない
		if (movePosX_ > 0.0f)
		{
			movePosX_ = 0.0f;
		}
		pos_.x += movePosX_;
	}

	//デバッグ表示用に一回計算する
	//完成品では消してよし
	CalcLeftSidePos();
	isHitLeftSide_ = IsHitLeftPos();

	//左に移動していたら左と衝突判定
	if (prePos.x > pos_.x)CollisionLeftSide();
	if (prePos.x > pos_.x)CollisionWaterLeftSide();
	if (prePos.x > pos_.x)CollisionFlareLeftSide();
	if (prePos.x > pos_.x)CollisionPlantsLeftSide();
	//右への移動処理
	if (ins.IsNew(KEY_INPUT_D))
	{

		
		
		//右を向ける
		dir_ = AsoUtility::DIR::RIGHT;

		//加速量を加算する
		movePosX_ += speed_;

		//移動量
		if (movePosX_ > maxSpeed_)
		{
			movePosX_ = maxSpeed_;
		}
		pos_.x += movePosX_;
		//地上にいるときは走るアニメモーション再生
		if (!isJump_)
		{
			//ChangeAnimState(ANIM_STATE::RUN, false);
		}
	}

	//地上にいるときに移動ボタンが離されたら待機アニメーション再生
	/*if (InputManager::GetInstance()->IsTrgUp(KEY_INPUT_D) && !isJump_)
	{
		ChangeAnimState(ANIM_STATE::IDLE, true);
	}*/
	//スピードが出ているときは原則も同時に行う
	

		if (movePosX_ > 0.0f)
		{
			movePosX_ -= MOVE_DEC_POW;

			//原則を０以下にはしない
			if (movePosX_ < 0.0f)
			{
				movePosX_ = 0.0f;
			}
			pos_.x += movePosX_;
		}
	
	//デバッグ表示用に一回計算する
	//完成品では消してよし
	CalcRightSidePos();
	isHitRightSide_ = IsHitRightPos();

	
	//右に移動していたら右と衝突判定
	if (prePos.x < pos_.x)CollisionRightSide();
	if (prePos.x < pos_.x)CollisionWaterRightSide();
	if (prePos.x < pos_.x)CollisionFlareRightSide();
	if (prePos.x < pos_.x)CollisionPlantsRightSide();

	if(!ins.IsNew(KEY_INPUT_D) && !ins.IsNew(KEY_INPUT_A))
	{
		moveType_ = MOVE_TYPE::STOP;
	}
}

//アニメーション処理
void Player::Anime()
{
	if (moveType_ == MOVE_TYPE::MOVE)
	{
		animationTime_ += 0.1f;
		if (animationTime_ >= 1.0f)
		{
			animationCount_++;
			//アニメーションのカウントが画像の枚数を超えたら
			if (animationCount_ > 11)
			{
				//アニメーションのカウントを０に戻す
				animationCount_ = 6;
			}
			//アニメーションの時間をリセット
			animationTime_ = 0.0f;
		}
	}
	if (moveType_ == MOVE_TYPE::STOP)
	{
		animationTime_ += 0.05f;
		if (animationTime_ >= 1.0f)
		{
			animationCount_++;
			//アニメーションのカウントが画像の枚数を超えたら
			if (animationCount_ >= 2)
			{
				//アニメーションのカウントを０に戻す
				animationCount_ = 0;
			}
			//アニメーションの時間をリセット
			animationTime_ = 0.0f;
		}
	}

}

//攻撃タイプ別処理
void Player::Attack()
{
	//攻撃処理
	InputManager& ins = InputManager::GetInstance();
	if (isAttack_)
	{
		if (ins.IsTrgDown(KEY_INPUT_1))
		{
			animaAem_ = 3;
			elementType_ = ELEMENT_TYPE::FIRE;

		}
		if (ins.IsTrgDown(KEY_INPUT_2))
		{
			animaAem_ = 1;
			elementType_ = ELEMENT_TYPE::WATER;

		}
		if (ins.IsTrgDown(KEY_INPUT_3))
		{
			animaAem_ = 2;
			elementType_ = ELEMENT_TYPE::PLANT;

		}
		if (ins.IsTrgDown(KEY_INPUT_4))
		{
			animaAem_ = 0;
			elementType_ = ELEMENT_TYPE::NORMAL;

		}

	}



	if (elementType_ == ELEMENT_TYPE::FIRE)
	{
		AttackChange();
		if (isPoint_)
		{
			if (id_ == 3)
			{
				if (wall_->IsWaterCollision(attackPos_) == true || wall_->IsFlaereCollision(attackPos_) == true || stage_->IsCollisionStage3(attackPos_) == true)
				{
					isPoint_ = false;
					isAttack_ = true;
				}
				else if (wall_->IsPlantsCollision(attackPos_) == true)
				{
					wall_->SetIsPlants(false);
					isPoint_ = false;
					isAttack_ = true;
					blast_->SetBlastPos(attackPos_);
					blast_->SetIsBlast(true);
				}
			}
			else if (id_ == 1 || id_ == 2)
			{
				if (wall_->IsWaterCollision(attackPos_) == true || wall_->IsFlaereCollision(attackPos_) == true || stage_->IsCollisionStage(attackPos_) == true)
				{

					isPoint_ = false;
					isAttack_ = true;

				}
				else if (wall_->IsPlantsCollision(attackPos_) == true)
				{
					wall_->SetIsPlants(false);
					isPoint_ = false;
					isAttack_ = true;
					blast_->SetBlastPos(attackPos_);
					blast_->SetIsBlast(true);
				}

			}
		}
	}

	if (elementType_ == ELEMENT_TYPE::WATER)
	{
		AttackChange();
		if (isPoint_)
		{
			if (id_ == 3)
			{
				if (wall_->IsWaterCollision(attackPos_) == true || wall_->IsPlantsCollision(attackPos_) == true || stage_->IsCollisionStage3(attackPos_) == true)
				{



					isPoint_ = false;
					isAttack_ = true;


				}
				else if (wall_->IsFlaereCollision(attackPos_) == true)
				{
					wall_->SetIsFlare(false);
					isPoint_ = false;
					isAttack_ = true;
					water_->CreateEffect(attackPos_);
				}
			}
			else if(id_ == 1 || id_ == 2)
			{
				if (wall_->IsWaterCollision(attackPos_) == true || wall_->IsPlantsCollision(attackPos_) == true || stage_->IsCollisionStage(attackPos_) == true)
				{

					isPoint_ = false;
					isAttack_ = true;

				}
				else if (wall_->IsFlaereCollision(attackPos_) == true)
				{
					wall_->SetIsFlare(false);
					isPoint_ = false;
					isAttack_ = true;
					water_->CreateEffect(attackPos_);
				}
			}

		}

	}
	if (elementType_ == ELEMENT_TYPE::PLANT)
	{
		AttackChange();
		if (isPoint_)
		{
			if (id_ == 3)
			{
				if (wall_->IsPlantsCollision(attackPos_) == true || wall_->IsFlaereCollision(attackPos_) == true || wall_->IsWaterCollision(attackPos_) == true ||stage_->IsCollisionStage3(attackPos_) == true)
				{



					isPoint_ = false;
					isAttack_ = true;

				}
				else if (wall_->IsSphereCollision(attackPos_) == true)
				{
					wall_->SetIsSphere(false);
					isPoint_ = false;
					isAttack_ = true;
					plants_->SetPlantsPos(attackPos_);
					plants_->SetIsPlants(true);

				}

				
			}
			else if (id_ == 1 || id_ == 2)
			{
				if (wall_->IsPlantsCollision(attackPos_) == true || wall_->IsFlaereCollision(attackPos_) == true || wall_->IsWaterCollision(attackPos_) == true ||stage_->IsCollisionStage(attackPos_) == true)
				{

					isPoint_ = false;
					isAttack_ = true;

				}
				else if (wall_->IsSphereCollision(attackPos_) == true)
				{
					wall_->SetIsSphere(false);
					isPoint_ = false;
					isAttack_ = true;
					plants_->SetPlantsPos(attackPos_);
					plants_->SetIsPlants(true);



				}
			}
		}
	}
	if (elementType_ == ELEMENT_TYPE::NORMAL)
	{
		if (dir_ == AsoUtility::DIR::RIGHT)
		{
			if (ins.IsNew(KEY_INPUT_K))
			{

				if (armAngle_ <= AsoUtility::Deg2RadF(0.0f))
				{
					armAngle_ = AsoUtility::Deg2RadF(180.0f);
				}

				armAngle_ += AsoUtility::Deg2RadF(5.0f);

				if (armAngle_ >= AsoUtility::Deg2RadF(360.0f))
				{
					armAngle_ = AsoUtility::Deg2RadF(180.0f);
				}
				//
				attckAnglePoint_.x = pos_.x - sinf(armAngle_) * 100;
				attckAnglePoint_.y = pos_.y + cosf(armAngle_) * 100;

			}
			else if (!ins.IsNew(KEY_INPUT_K))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
			}
		}
		else if (dir_ == AsoUtility::DIR::LEFT)
		{
			if (ins.IsNew(KEY_INPUT_K))
			{

				if (armAngle_ >= AsoUtility::Deg2RadF(0.0f))
				{
					armAngle_ = AsoUtility::Deg2RadF(-180.0f);
				}

				armAngle_ -= AsoUtility::Deg2RadF(5.0f);

				if (armAngle_ <= AsoUtility::Deg2RadF(-360.0f))
				{
					armAngle_ = AsoUtility::Deg2RadF(-180.0f);
				}
				//
				attckAnglePoint_.x = pos_.x - sinf(armAngle_) * 100;
				attckAnglePoint_.y = pos_.y + cosf(armAngle_) * 100;

			}
			else if (!ins.IsNew(KEY_INPUT_K))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
			}
		}
	}

}

//属性攻撃処理
void Player::AttackChange(void)
{


	InputManager& ins = InputManager::GetInstance();
	if (isAttack_)
	{

		if (ins.IsTrgUp(KEY_INPUT_K))
		{
			mp_ -= 10;
			attackPos_.x = attckAnglePoint_.x;
			attackPos_.y = attckAnglePoint_.y;

			movePos = upCnt;
			isPoint_ = true;
			isAttack_ = false;
		}
	}
	if (isPoint_) {
		attackPos_.y -= movePos;
		movePos -= GRAVITY;
	}
	if (attackPos_.y > (64 * 12))
	{
		attackPos_.y = (64 * 12);
		isPoint_ = false;
		isAttack_ = true;
	}

	if (dir_ == AsoUtility::DIR::RIGHT)
	{

		if (ins.IsNew(KEY_INPUT_K))
		{
			if (isAttack_)
			{
				dirChange_ = true;
			}
			armAngle_ -= AsoUtility::Deg2RadF(5.0f);
			for (int i = 1; i <= 11; ++i)
			{
				if (armAngle_ <= AsoUtility::Deg2RadF(-10.0f * i))
				{
					upCnt = i;
				}
			}

			if (armAngle_ < AsoUtility::Deg2RadF(-120.0f))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
				upCnt = 0;
			}
		}
		else if (!ins.IsNew(KEY_INPUT_K))
		{
			armAngle_ = AsoUtility::Deg2RadF(0.0f);
		}
		attckAnglePoint_.x = pos_.x - sinf(armAngle_) * 30;
		attckAnglePoint_.y = pos_.y + cosf(armAngle_) * 30;

	}
	else if (dir_ == AsoUtility::DIR::LEFT)
	{
		if (isAttack_)
		{
			dirChange_ = false;
		}
		if (ins.IsNew(KEY_INPUT_K))
		{
			armAngle_ += AsoUtility::Deg2RadF(5.0f);
			for (int i = 1; i <= 11; ++i)
			{
				if (armAngle_ >= AsoUtility::Deg2RadF(10.0f * i))
				{
					upCnt = i;
				}
			}
			if (armAngle_ > AsoUtility::Deg2RadF(120.0f))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
				upCnt = 12;
			}

		}
		else if (!ins.IsNew(KEY_INPUT_K))
		{

			armAngle_ = AsoUtility::Deg2RadF(0.0f);

		}
		attckAnglePoint_.x = pos_.x - sinf(armAngle_) * 30;
		attckAnglePoint_.y = pos_.y + cosf(armAngle_) * 30;
	}

	if (dirChange_)
	{
		attackPos_.x += MOVE_POWER;
	}
	else if (!dirChange_)
	{
		attackPos_.x -= MOVE_POWER;
	}
}


//当たり判定--------------------------------------------------------------------------------------------------------------------------------------------------------------

void Player::CalcFootPos(void)
{
	//足元座標を計算（中心
	footPosC_.x = static_cast<int>(pos_.x);
	footPosC_.y = static_cast<int>(pos_.y);
	footPosC_.y += HALF_COL_SIZE_Y;
	footPosC_.y += COL_OFFSET;

	//足元の座標（左
	footPosL_ = footPosC_;
	footPosL_.x -= HALF_COL_SIZE_X;
	footPosL_.x += COL_OFFSET;

	//足元座標（右
	footPosR_ = footPosC_;
	footPosR_.x += HALF_COL_SIZE_X;
	footPosR_.x -= COL_OFFSET;



}

void Player::CalcHeadPos(void)
{
	//頭座標を計算（中心
	headPosC_.x = static_cast<int>(pos_.x);
	headPosC_.y = static_cast<int>(pos_.y);
	headPosC_.y -= HALF_COL_SIZE_Y;
	headPosC_.y -= COL_OFFSET;

	//頭の座標（左
	headPosL_ = headPosC_;
	headPosL_.x -= HALF_COL_SIZE_X;
	headPosL_.x += COL_OFFSET;


	//頭座標（右
	headPosR_ = headPosC_;
	headPosR_.x += HALF_COL_SIZE_X;
	headPosR_.x -= COL_OFFSET;

}

void Player::CalcRightSidePos(void)
{
	//右側座標を計算（中心
	rightPosC_.x = static_cast<int>(pos_.x);
	rightPosC_.y = static_cast<int>(pos_.y);
	rightPosC_.x += HALF_COL_SIZE_Y;
	rightPosC_.x += COL_OFFSET;

	//右側の座標（上
	rightPosU_ = rightPosC_;
	rightPosU_.y -= HALF_COL_SIZE_Y;
	rightPosU_.y += COL_OFFSET;

	//右側座標（下
	rightPosD_ = rightPosC_;
	rightPosD_.y += HALF_COL_SIZE_Y;
	rightPosD_.y -= COL_OFFSET;
}

void Player::CalcLeftSidePos(void)
{
	//左側座標を計算（中心
	leftPosC_.x = static_cast<int>(pos_.x);
	leftPosC_.y = static_cast<int>(pos_.y);
	leftPosC_.x -= HALF_COL_SIZE_Y;
	leftPosC_.x -= COL_OFFSET;

	//左側の座標（上
	leftPosU_ = leftPosC_;
	leftPosU_.y -= HALF_COL_SIZE_Y;
	leftPosU_.y += COL_OFFSET;

	//左側座標(下
	leftPosD_ = leftPosC_;
	leftPosD_.y += HALF_COL_SIZE_Y;
	leftPosD_.y -= COL_OFFSET;
}

//判定の取得＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//足元
bool Player::IsHitFootPos(void)
{
	if (id_ == 3)
	{
		return stage_->IsCollisionStage3(footPosC_)
			|| stage_->IsCollisionStage3(footPosL_)
			|| stage_->IsCollisionStage3(footPosR_);
	}
	else
	{
		return stage_->IsCollisionStage(footPosC_)
			|| stage_->IsCollisionStage(footPosL_)
			|| stage_->IsCollisionStage(footPosR_);
	}


}
//頭上
bool Player::IsHitHeadPos(void)
{
	if (id_ == 3)
	{
		return stage_->IsCollisionStage3(headPosC_)
			|| stage_->IsCollisionStage3(headPosL_)
			|| stage_->IsCollisionStage3(headPosR_);
	}
	else
	{

		return stage_->IsCollisionStage(headPosC_)
			|| stage_->IsCollisionStage(headPosL_)
			|| stage_->IsCollisionStage(headPosR_);
	}
}
//右側
bool Player::IsHitRightPos(void)
{
	if (id_ == 3)
	{
		return stage_->IsCollisionStage3(rightPosC_)
			|| stage_->IsCollisionStage3(rightPosU_)
			|| stage_->IsCollisionStage3(rightPosD_);
	}
	else
	{
		return stage_->IsCollisionStage(rightPosC_)
			|| stage_->IsCollisionStage(rightPosU_)
			|| stage_->IsCollisionStage(rightPosD_);
	}
}
//左側
bool Player::IsHitLeftPos(void)
{
	if (id_ == 3)
	{
		return stage_->IsCollisionStage3(leftPosC_)
			|| stage_->IsCollisionStage3(leftPosU_)
			|| stage_->IsCollisionStage3(leftPosD_);
	}
	else
	{
		return stage_->IsCollisionStage(leftPosC_)
			|| stage_->IsCollisionStage(leftPosU_)
			|| stage_->IsCollisionStage(leftPosD_);
	}
}

//水
//右側
bool Player::IsWaterHitRightPos(void)
{
	return wall_->IsWaterCollision(rightPosC_)
		|| wall_->IsWaterCollision(rightPosU_)
		|| wall_->IsWaterCollision(rightPosD_);

}
//左側
bool Player::IsWaterHitLeftPos(void)
{
	return wall_->IsWaterCollision(leftPosC_)
		|| wall_->IsWaterCollision(leftPosU_)
		|| wall_->IsWaterCollision(leftPosD_);

}

//炎
//右側
bool Player::IsFlareHitRightPos(void)
{
	return wall_->IsFlaereCollision(rightPosC_)
		|| wall_->IsFlaereCollision(rightPosU_)
		|| wall_->IsFlaereCollision(rightPosD_);

}
//左側
bool Player::IsFlareHitLeftPos(void)
{
	return wall_->IsFlaereCollision(leftPosC_)
		|| wall_->IsFlaereCollision(leftPosU_)
		|| wall_->IsFlaereCollision(leftPosD_);
}

//植物
//右側
bool Player::IsPlantsHitRightPos(void)
{
	return wall_->IsPlantsCollision(rightPosC_)
		|| wall_->IsPlantsCollision(rightPosU_)
		|| wall_->IsPlantsCollision(rightPosD_);
}
//左側
bool Player::IsPlantsHitLeftPos(void)
{
	return wall_->IsPlantsCollision(leftPosC_)
		|| wall_->IsPlantsCollision(leftPosU_)
		|| wall_->IsPlantsCollision(leftPosD_);
}

//ブロックとの当たり判定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Player::CollisionFoot(void)
{
	//足元三点の座標
	CalcFootPos();

	//足元三点との当たり判定
	isHitFoot_ = IsHitFootPos();

	//足元三点のどれかが当たっていたら
	if (isHitFoot_)
	{
		//足元のマップ番号をとる
		Vector2 mapPos = World2MapPos(footPosC_);
		//当たっているマップチップの上側の座標を計算する
		int mapChipUpSideY = mapPos.y * Stage::CHIP_SIZE_Y;
		//プレイヤーの足元がマップチップの上側になるように設定する
		pos_.y = static_cast<float>(mapChipUpSideY) - HALF_COL_SIZE_Y - COL_OFFSET- 3;

		//ジャンプフラグを切る
		if (isJump_)
		{
			//着地（待機）アニメーション再生
			//ChangeAnimState(ANIM_STATE::IDLE, true);
			//ジャンプフラグを折る
			isJump_ = false;
		}
	}
	else if (!isJump_)
	{
		//ジャンプフラグを立てる
		isJump_ = true;
		//ジャンプ力を０にする
		//（常にかかっている重力をいったんリセットして
		//自然な落下にする
		movePosY_ = 0.0f;
		//落下（ジャンプ）アニメーション再生
		//ChangeAnimState(ANIM_STATE::JUNP, true);

	}
}
void Player::CollisionHead(void)
{
	//頭側三点の座標
	CalcHeadPos();

	//頭側三点との当たり判定
	isHitHead_ = IsHitHeadPos();

	//頭側三点のどれかが当たっていたら
	if (isHitHead_)
	{
		//頭側のマップ番号をとる
		Vector2 mapPos = World2MapPos(headPosC_);
		//当たっているマップチップの上側の座標を計算する
		int mapChipUpSideY = mapPos.y * Stage::CHIP_SIZE_Y;
		//当たっているマップチップの下側の座標を計算する
		int mapChipDownSideY = mapChipUpSideY + Stage::CHIP_SIZE_Y;
		//プレイヤーの頭側がマップチップの上側になるように設定する
		pos_.y = static_cast<float>(mapChipDownSideY) + HALF_COL_SIZE_Y + COL_OFFSET + 3;

		//頭がぶつかったの
		movePosY_ = 0.0f;
	}
}
void Player::CollisionRightSide(void)
{
	//右側三点の座標
	CalcRightSidePos();

	//右側三点との当たり判定
	isHitRightSide_ = IsHitRightPos();

	//右側三点のどれかが当たっていたら
	if (isHitRightSide_)
	{
		//右側のマップ番号をとる
		Vector2 mapPos = World2MapPos(rightPosC_);
		//当たっているマップチップの左側の座標を計算する
		int mapChipLeftPosX = mapPos.x * Stage::CHIP_SIZE_X;
		//プレイヤーの右側がマップチップの左側になるように設定する
		pos_.x = static_cast<float>(mapChipLeftPosX) - HALF_COL_SIZE_X - COL_OFFSET;
		//右に移動量があるときは移動量をなくす
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
void Player::CollisionLeftSide(void)
{
	//左側三点の座標
	CalcLeftSidePos();

	//左側三点との当たり判定
	isHitLeftSide_ = IsHitLeftPos();

	//左側三点のどれかが当たっていたら
	if (isHitLeftSide_)
	{
		//左側のマップ番号をとる
		Vector2 mapPos = World2MapPos(leftPosC_);
		//当たっているマップチップの左側の座標を計算する
		int mapChipLeftPosX = mapPos.x * Stage::CHIP_SIZE_X;
		//当たっているマップチップの右側の座標を計算する
		int mapChipRightSideX = mapChipLeftPosX + Stage::CHIP_SIZE_X;
		//プレイヤーの左側がマップチップの左側になるように設定する
		pos_.x = static_cast<float>(mapChipRightSideX) + HALF_COL_SIZE_X + COL_OFFSET;
		//左に移動録があるときは移動量をなくす
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//壁との当たり判定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//水との当たり判定
//右
void Player::CollisionWaterRightSide(void)
{
	//右側三点の座標
	CalcRightSidePos();

	//右側三点との当たり判定
	isHitRightSide_ = IsWaterHitRightPos();

	//右側三点のどれかが当たっていたら
	if (isHitRightSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetWaterPos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionWaterLeftSide(void)
{
	CalcLeftSidePos();
	//左側三点との当たり判定
	isHitLeftSide_ = IsWaterHitLeftPos();

	//左側三点のどれかが当たっていたら
	if (isHitLeftSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetWaterPos().x + wall_->FLARE_SIZE_X+wall_->FLARE_HALF_SIZE_X;
		//左に移動録があるときは移動量をなくす
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}

//炎との当たり判定
//右
void Player::CollisionFlareRightSide(void)
{
	CalcRightSidePos();

	//右側三点との当たり判定
	isHitRightSide_ = IsFlareHitRightPos();

	//右側三点のどれかが当たっていたら
	if (isHitRightSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetFlarePos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionFlareLeftSide(void)
{
	CalcLeftSidePos();
	//左側三点との当たり判定
	isHitLeftSide_ = IsFlareHitLeftPos();

	//左側三点のどれかが当たっていたら
	if (isHitLeftSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetFlarePos().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		//左に移動録があるときは移動量をなくす
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}


//植物との当たり判定
//右
void Player::CollisionPlantsRightSide(void)
{
	CalcRightSidePos();

	//右側三点との当たり判定
	isHitRightSide_ = IsPlantsHitRightPos();

	//右側三点のどれかが当たっていたら
	if (isHitRightSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetPlantsPos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionPlantsLeftSide(void)
{
	CalcLeftSidePos();
	//左側三点との当たり判定
	isHitLeftSide_ = IsPlantsHitLeftPos();

	//左側三点のどれかが当たっていたら
	if (isHitLeftSide_)
	{
		SetHp(GetHp() - 50);
		pos_.x = wall_->GetPlantsPos().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		//左に移動録があるときは移動量をなくす
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}


//判定の可視化＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－－－
void Player::DrawHitCollision(void)
{
	//足元の当たり判定の可視化
	constexpr unsigned int FOOT_HIT_POS_COLOR = 0xff0000;
	constexpr int CHIRCLE_SIZE = 2;
	DrawCircle(footPosC_.x - camera_->GetCameraPos().x, footPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);
	DrawCircle(footPosL_.x - camera_->GetCameraPos().x, footPosL_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);
	DrawCircle(footPosR_.x - camera_->GetCameraPos().x, footPosR_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);
	//頭側の当たり判定の可視化
	constexpr unsigned int HEAD_HIT_POS_COLOR = 0x000000;
	DrawCircle(headPosC_.x - camera_->GetCameraPos().x, headPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);
	DrawCircle(headPosL_.x - camera_->GetCameraPos().x, headPosL_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);
	DrawCircle(headPosR_.x - camera_->GetCameraPos().x, headPosR_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);
	//右側の当たり判定の可視化
	constexpr unsigned int RIGHT_HIT_POS_COLOR = 0x0000FF;
	DrawCircle(rightPosC_.x - camera_->GetCameraPos().x, rightPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);
	DrawCircle(rightPosD_.x - camera_->GetCameraPos().x, rightPosD_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);
	DrawCircle(rightPosU_.x - camera_->GetCameraPos().x, rightPosU_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);
	//左側の当たり判定の可視化
	constexpr unsigned int LEFT_HIT_POS_COLOR = 0xFF00FF;
	DrawCircle(leftPosC_.x - camera_->GetCameraPos().x, leftPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);
	DrawCircle(leftPosD_.x - camera_->GetCameraPos().x, leftPosD_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);
	DrawCircle(leftPosU_.x - camera_->GetCameraPos().x, leftPosU_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);
	//当たり判定確認用デバッグ文字
	constexpr unsigned int STRING_COLOR = 0x000000;
	if (isHitFoot_) DrawString(45, 0, "下側が当たっている", STRING_COLOR);
	if (isHitHead_) DrawString(45, 20, "上側が当たっている", STRING_COLOR);
	if (isHitRightSide_) DrawString(45, 40, "右側が当たっている", STRING_COLOR);
	if (isHitLeftSide_) DrawString(45, 60, "左側が当たっている", STRING_COLOR);
}

//ワールド座標からマップ座標への変換
Vector2 Player::World2MapPos(Vector2 worldPos)
{
	Vector2 ret;

	int mapX = worldPos.x / Stage::CHIP_SIZE_X;
	int mapY = worldPos.y / Stage::CHIP_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}


//ゲット・セット＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
Vector2F Player::GetPlayerPos()
{
	return pos_;
}
void Player::SetPlayerPos(Vector2F pos)
{
	pos_ = pos;
}

int Player::GetHp(void)
{
	return hp_;
}
void Player::SetHp(int hp)
{
	hp_ = hp;
}

int Player::GetMp(void)
{
	return mp_;
}
void Player::SetMp(int mp)
{
	mp_ = mp;
}
unsigned int Player::GetCr(void)
{
 	return cr_;
}
void Player::SetCr(int cr)
{
	cr_ = cr;
}




//チェンジ関数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Player::MoveChange(void)
{
	switch (moveType_)
	{
	case MOVE_TYPE::STOP:
		//移動量を０にする

		break;
	case MOVE_TYPE::MOVE:

		break;

	}

}

void Player::ElementChange()
{
	switch (elementType_)
	{

	case ELEMENT_TYPE::FIRE:
		cr_ = 0xff0000;
		
		break;
	case ELEMENT_TYPE::WATER:
		cr_ = 0x0000ff;
		
		break;
	case ELEMENT_TYPE::PLANT:
		cr_ = 0x00ff00;
		
		break;
	case ELEMENT_TYPE::NORMAL:
		cr_ = 0xffffff;
		break;
	}
}