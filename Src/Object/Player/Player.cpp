#include <DxLib.h>
#include <math.h>
#include "../../Application.h"
#include "../../Scene/GameScene.h"
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
void Player::Init(Camera* camera, Stage* stage, Wall* wall, Blast* blast, Water* water, Plants* plants, GameScene* gameScene)
{

	gameScene_ = gameScene;

	//カメラの取得
	camera_ = camera; // 引数で渡されたカメラを保持

	//ステージの取得
	stage_ = stage; // ステージ情報を保持

	//壁の取得
	wall_ = wall; // 壁オブジェクトを保持

	blast_ = blast; // 爆発（攻撃エフェクトなど）を保持

	water_ = water; // 水エフェクト（攻撃判定等）を保持

	plants_ = plants; // 植物オブジェクト（当たり判定等）を保持

	// 画像の読み込み
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネージャのインスタンス取得

	img_ = res.Load(ResourceManager::SRC::PLAYERS).handleIds_; // プレイヤー画像の読み込み（分割画像）

	armImg_ = res.Load(ResourceManager::SRC::PLAYERARM).handleIds_; // プレイヤーの腕画像の読み込み

	sordImg_ = LoadGraph("Data/Image/Player/Sord.png"); // 剣の画像を読み込み（単体）

	swingSoundHandle_ = LoadSoundMem("Data/Sound/SE/Swing.mp3");

	stageSize_ = stage_->CHIP_SIZE_X; // ステージの1マスの幅を取得（横チップサイズ）

	// 初期位置設定
	pos_.x = stageSize_ * INITIAL_POS_CHIP_X; // X座標を設定
	pos_.y = stageSize_ * INITIAL_POS_CHIP_Y; // Y座標を設定

	invCnt_ = 0; // 無敵時間カウンタを初期化
	isAlive_ = true; // 生存フラグをtrueに設定

	//アニメーション初期化
	armAngle_ = AsoUtility::Deg2RadF(0.0f); // 腕の初期角度を0度に設定（ラジアン）
	animationTime_ = 0.0f; // アニメーション経過時間を初期化
	animationCount_ = 0; // アニメーションカウントを初期化

	//移動タイプ
	moveType_ = MOVE_TYPE::STOP; // プレイヤーの移動状態を停止に設定

	//属性タイプ
	elementType_ = ELEMENT_TYPE::NORMAL; // 属性タイプをノーマルに設定
	cr_ = COLOR_WHITE; // プレイヤーの色（白）を設定（RGB）

	cameraPos_ = camera_->GetCameraPos(); // 現在のカメラ位置を取得して保持

	//攻撃
	isAttack_ = true; // 攻撃状態をtrueに設定（初期値としては注意が必要）
	isPoint_ = false; // 攻撃ポイント判定を無効に
	dirChange_ = true; // 向き変更フラグをtrueに
	isSword_ = false; // 剣の表示・使用フラグをfalseに

	attackPos_.x = 0; // 攻撃座標Xを初期化
	attackPos_.y = 0; // 攻撃座標Yを初期化
	movePos = 0.0f; // 移動距離（方向ベクトルの倍率など）を初期化

	//攻撃ポイント(Init)
	attckAnglePoint_.x = 0; // 攻撃角度に対応するX座標を初期化
	attckAnglePoint_.y = 0; // 攻撃角度に対応するY座標を初期化

	id_ = 0; // プレイヤーの識別IDを0に初期化

	hp_ = MAX_HP; // HPを最大値に設定
	mp_ = MAX_MP; // MPを最大値に設定

	regeneCnt_ = REGENE_INTERVAL; // 自動回復用のカウント間隔を設定
	mpRegene_ = REGENE_MP_AMOUNT; // MPの自動回復量を設定

}
void Player::Update()
{


	// プレイヤーの再出現処理
	if (isAlive_ == false) // プレイヤーが死亡状態なら
	{
		isAlive_ = true; // 生存状態に戻す（復活）
		// 無敵時間
		invCnt_ = RESPAWN_INVINCIBLE_TIME; // 復活直後の無敵時間
	}
	//無敵時間処理
	if (invCnt_ > 0) // 無敵時間が残っていれば
	{
		invCnt_--; // フレームごとにカウントを減らす
	}

	id_ = stage_->GetStageId(); // 現在のステージIDを取得して保持

	MoveChange(); // プレイヤーの移動タイプ変更処理

	Move(); // プレイヤーの移動処理

	Anime(); // アニメーション更新処理（フレームに応じた画像の切り替え）

	Attack(); // 攻撃処理

	ElementChange(); // 属性変更処理

	ReSpawn(); // 再出現処理

	Hp(); // HPに関する処理

	Mp(); // MPに関する処理
}
void Player::Draw()
{
	// 画像の描画
	Vector2 cpos = camera_->GetCameraPos();
	if (isAlive_)
	{
		// 半透明フラグ
		bool isTrans = false;
		if (invCnt_ > 0)
		{
			if (invCnt_ % 2 == 0)
			{
				isTrans = true;
			}
		}

		constexpr int HALF_ALPHA = 255 / 2;

		if (isTrans)
		{
			// 被ダメ時の自機の描画
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, HALF_ALPHA);
			DrawRotaGraphF((pos_.x) - cpos.x, (pos_.y) - cpos.y, 1.0f, 0.0f, img_[animationCount_], TRUE, dir_ == AsoUtility::DIR::LEFT);
			DrawRotaGraphF((pos_.x) - cpos.x, (pos_.y) - cpos.y, 1.0f, armAngle_, armImg_[animaAem_], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
		{
			// 自機の描画
			DrawRotaGraphF((pos_.x) - cpos.x, (pos_.y) - cpos.y, 1.0f, 0.0f, img_[animationCount_], TRUE, dir_ == AsoUtility::DIR::LEFT);
			DrawRotaGraphF((pos_.x) - cpos.x, (pos_.y) - cpos.y, 1.0f, armAngle_, armImg_[animaAem_], TRUE);
		}

	}
	if (isSword_ == true)
	{
		DrawRotaGraphF(attckAnglePoint_.x - cpos.x, attckAnglePoint_.y - cpos.y, 1.0f, armAngle_ + AsoUtility::Deg2RadF(SWORD_DRAW_ANGLE_OFFSET), sordImg_, true);
	}

	constexpr int ATTACK_POINT_MARKER_RADIUS = 5;
	DrawCircle(attckPoint_.x - cpos.x, attckPoint_.y - cpos.y, ATTACK_POINT_MARKER_RADIUS, cr_);

	if (isPoint_)
	{
		// 段階的な半透明リングの描画
		constexpr int ALPHA_DIVISORS[] = { 12, 10, 8, 6, 4, 2 };
		constexpr int CIRCLE_RADII[] = { 12, 10, 8, 6, 4, 2 };
		constexpr int ARRAY_SIZE = sizeof(CIRCLE_RADII) / sizeof(CIRCLE_RADII[0]);

		for (int i = 0; i < ARRAY_SIZE; ++i)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / ALPHA_DIVISORS[i]);
			DrawCircle(attackPos_.x - cpos.x, attackPos_.y - cpos.y, CIRCLE_RADII[i], cr_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		DrawCircle(attackPos_.x - cpos.x, attackPos_.y - cpos.y, 1, cr_);
	}
	if (GetIsEF() == true)
	{
		radius_ += static_cast<int>(EF_RADIUS_ADD);
		//属性変更時のエフェクト
		for (int offset = 0; offset <= 4; ++offset)
		{
			DrawCircle(pos_.x - cpos.x, pos_.y - cpos.y, radius_ + offset, GetCr(), false);
		}

		if (radius_ >= static_cast<int>(EF_MAX_RADIUS))
		{
			radius_ = 0;
			SetIsEF(false);
		}
	}
#ifdef _DEBUG
	//当たり判定の可視化
	DrawHitCollision();
	DrawCircle(attckAnglePoint_.x - cpos.x, attckAnglePoint_.y - cpos.y, static_cast<int>(EF_SPHERE_DEBUG_RADIUS), cr_, false);

#endif // DEBUG

}

//プレイヤーの機能処理==========================================================================================================================================================================

//移動処理
void Player::Move()
{
	//移動処理
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsNew(KEY_INPUT_LSHIFT) || ins.IsNew(KEY_INPUT_RSHIFT))
	{
		speed_ = MOVE_ACC_POW * DASH_SPEED_MULTIPLIER;
		maxSpeed_ = MAX_MOVE_SPEED * DASH_SPEED_MULTIPLIER;
	}
	else
	{
		speed_ = MOVE_SPEED;
		maxSpeed_ = MAX_MOVE_SPEED;
	}

	if (ins.IsTrgDown(KEY_INPUT_D) || ins.IsTrgDown(KEY_INPUT_A))
	{
		animationCount_ = ANIME_MOVE_FRAME_START;
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
	CalcHeadPos();
	isHitHead_ = IsHitHeadPos();

	//上に移動していたら頭と衝突判定
	if (prePos.y > pos_.y) CollisionHead();

	//下への移動処理
	CalcFootPos();
	isHitFoot_ = IsHitFootPos();

	//下に移動していたら足元と衝突判定
	if (prePos.y < pos_.y) CollisionFoot();

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
	}

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

	CalcLeftSidePos();
	isHitLeftSide_ = IsHitLeftPos();

	//左に移動していたら左と衝突判定
	if (prePos.x > pos_.x)CollisionLeftSide();
	if (prePos.x > pos_.x)CollisionWaterLeftSide();
	if (prePos.x > pos_.x)CollisionFlareLeftSide();
	if (prePos.x > pos_.x)CollisionPlantsLeftSide();
	if (id_ == STAGE_ID_3)
	{
		if (prePos.x > pos_.x)CollisionWaterLeftSide2();
		if (prePos.x > pos_.x)CollisionFlareLeftSide2();
		if (prePos.x > pos_.x)CollisionPlantsLeftSide2();
		if (prePos.x > pos_.x)CollisionWaterLeftSide3();
		if (prePos.x > pos_.x)CollisionFlareLeftSide3();
		if (prePos.x > pos_.x)CollisionPlantsLeftSide3();
	}
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
	}

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

	CalcRightSidePos();
	isHitRightSide_ = IsHitRightPos();


	//右に移動していたら右と衝突判定
	if (prePos.x < pos_.x)CollisionRightSide();
	if (prePos.x < pos_.x)CollisionWaterRightSide();
	if (prePos.x < pos_.x)CollisionFlareRightSide();
	if (prePos.x < pos_.x)CollisionPlantsRightSide();
	if (id_ == STAGE_ID_3)
	{
		if (prePos.x < pos_.x)CollisionWaterRightSide2();
		if (prePos.x < pos_.x)CollisionFlareRightSide2();
		if (prePos.x < pos_.x)CollisionPlantsRightSide2();
		if (prePos.x < pos_.x)CollisionWaterRightSide3();
		if (prePos.x < pos_.x)CollisionFlareRightSide3();
		if (prePos.x < pos_.x)CollisionPlantsRightSide3();
	}

	if (!ins.IsNew(KEY_INPUT_D) && !ins.IsNew(KEY_INPUT_A))
	{
		moveType_ = MOVE_TYPE::STOP;
	}
}

//アニメーション処理
void Player::Anime()
{
	if (moveType_ == MOVE_TYPE::MOVE)
	{
		animationTime_ += ANIME_SPEED_MOVE;
		if (animationTime_ >= 1.0f)
		{
			animationCount_++;
			//アニメーションのカウントが画像の枚数を超えたら
			if (animationCount_ > ANIME_MOVE_FRAME_MAX)
			{
				//アニメーションのカウントを初期位置に戻す
				animationCount_ = ANIME_MOVE_FRAME_START;
			}
			//アニメーションの時間をリセット
			animationTime_ = 0.0f;
		}
	}
	if (moveType_ == MOVE_TYPE::STOP)
	{
		regeneCnt_--;
		if (regeneCnt_ < 0)
		{
			regeneCnt_ = REGENE_INTERVAL;
			SetMp(GetMp() + REGENE_MP_AMOUNT);
			if (GetMp() >= MAX_MP)
			{
				SetMp(MAX_MP);
			}
		}
		animationTime_ += ANIME_SPEED_STOP;
		if (animationTime_ >= 1.0f)
		{
			animationCount_++;
			//アニメーションのカウントが画像の枚数を超えたら
			if (animationCount_ >= ANIME_IDLE_FRAME_MAX)
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
	isSword_ = false; // 剣を振っていない状態に初期化

	// 属性変更のキー入力処理
	UpdateElementSelectInputs();

	// 属性ごとの攻撃処理
	switch (elementType_)
	{
	case ELEMENT_TYPE::FIRE:
		HandleFireAttack();
		break;

	case ELEMENT_TYPE::WATER:
		HandleWaterAttack();
		break;

	case ELEMENT_TYPE::PLANT:
		HandlePlantAttack();
		break;

	case ELEMENT_TYPE::NORMAL:
		HandleNormalAttack();
		break;

	default:
		break;
	}
}


// 属性切り替えキー入力
void Player::UpdateElementSelectInputs()
{
	if (!isAttack_ || GetIsEF()) return;

	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_1))
	{
		SetIsEF(true);
		elementType_ = ELEMENT_TYPE::PLANT;
	}
	else if (ins.IsTrgDown(KEY_INPUT_2))
	{
		SetIsEF(true);
		elementType_ = ELEMENT_TYPE::WATER;
	}
	else if (ins.IsTrgDown(KEY_INPUT_3))
	{
		SetIsEF(true);
		elementType_ = ELEMENT_TYPE::FIRE;
	}
	else if (ins.IsTrgDown(KEY_INPUT_4))
	{
		SetIsEF(true);
		elementType_ = ELEMENT_TYPE::NORMAL;
	}
	else if (ins.IsTrgDown(KEY_INPUT_T))
	{
		SetIsEF(true);
		if (elementType_ == ELEMENT_TYPE::FIRE)
		{
			elementType_ = ELEMENT_TYPE::NORMAL;
		}
		else
		{
			elementType_ = static_cast<ELEMENT_TYPE>(static_cast<int>(elementType_) + 1);
		}
	}
}

// 火属性攻撃処理
void Player::HandleFireAttack()
{
	AttackChange();
	if (!isPoint_) return;

	if (id_ == STAGE_ID_3)
	{
		if (wall_->IsWaterCollision(attackPos_) || wall_->IsFlaereCollision(attackPos_) ||
			wall_->IsWaterCollision2(attackPos_) || wall_->IsFlaereCollision2(attackPos_) ||
			wall_->IsWaterCollision3(attackPos_) || wall_->IsFlaereCollision3(attackPos_) ||
			stage_->IsCollisionStage3(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsPlantsCollision(attackPos_))
		{
			wall_->SetIsPlants(false);
			isPoint_ = false;
			isAttack_ = true;
			blast_->SetBlastPos(attackPos_);
			blast_->SetIsBlast(true);
		}
		else if (wall_->IsPlantsCollision2(attackPos_))
		{
			wall_->SetIsPlants2(false);
			isPoint_ = false;
			isAttack_ = true;
			blast_->SetBlastPos(attackPos_);
			blast_->SetIsBlast(true);
		}
		else if (wall_->IsPlantsCollision3(attackPos_))
		{
			wall_->SetIsPlants3(false);
			isPoint_ = false;
			isAttack_ = true;
			blast_->SetBlastPos(attackPos_);
			blast_->SetIsBlast(true);
		}
	}
	else if (id_ == 1 || id_ == 2)
	{
		if (wall_->IsWaterCollision(attackPos_) || wall_->IsFlaereCollision(attackPos_) ||
			stage_->IsCollisionStage(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsPlantsCollision(attackPos_))
		{
			wall_->SetIsPlants(false);
			isPoint_ = false;
			isAttack_ = true;
			blast_->SetBlastPos(attackPos_);
			blast_->SetIsBlast(true);
		}
	}
}

// 水属性攻撃処理
void Player::HandleWaterAttack()
{
	AttackChange();
	if (!isPoint_) return;

	if (id_ == STAGE_ID_3)
	{
		if (wall_->IsWaterCollision(attackPos_) || wall_->IsPlantsCollision(attackPos_) ||
			wall_->IsWaterCollision2(attackPos_) || wall_->IsPlantsCollision2(attackPos_) ||
			wall_->IsWaterCollision3(attackPos_) || wall_->IsPlantsCollision3(attackPos_) ||
			stage_->IsCollisionStage3(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsFlaereCollision(attackPos_))
		{
			wall_->SetIsFlare(false);
			isPoint_ = false;
			isAttack_ = true;
			water_->CreateEffect(attackPos_);
		}
		else if (wall_->IsFlaereCollision2(attackPos_))
		{
			wall_->SetIsFlare2(false);
			isPoint_ = false;
			isAttack_ = true;
			water_->CreateEffect(attackPos_);
		}
		else if (wall_->IsFlaereCollision3(attackPos_))
		{
			wall_->SetIsFlare3(false);
			isPoint_ = false;
			isAttack_ = true;
			water_->CreateEffect(attackPos_);
		}
	}
	else if (id_ == 1 || id_ == 2)
	{
		if (wall_->IsWaterCollision(attackPos_) || wall_->IsPlantsCollision(attackPos_) ||
			stage_->IsCollisionStage(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsFlaereCollision(attackPos_))
		{
			wall_->SetIsFlare(false);
			isPoint_ = false;
			isAttack_ = true;
			water_->CreateEffect(attackPos_);
		}
	}
}

// 植物属性攻撃処理
void Player::HandlePlantAttack()
{
	AttackChange();
	if (!isPoint_) return;

	if (id_ == STAGE_ID_3)
	{
		if (wall_->IsPlantsCollision(attackPos_) || wall_->IsFlaereCollision(attackPos_) ||
			wall_->IsWaterCollision(attackPos_) || wall_->IsPlantsCollision2(attackPos_) ||
			wall_->IsFlaereCollision2(attackPos_) || wall_->IsWaterCollision2(attackPos_) ||
			wall_->IsPlantsCollision3(attackPos_) || wall_->IsFlaereCollision3(attackPos_) ||
			wall_->IsWaterCollision3(attackPos_) || stage_->IsCollisionStage3(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsSphereCollision(attackPos_))
		{
			wall_->SetIsSphere(false);
			isPoint_ = false;
			isAttack_ = true;
			plants_->SetPlantsPos(attackPos_);
			plants_->SetIsPlants(true);
		}
		else if (wall_->IsSphereCollision2(attackPos_))
		{
			wall_->SetIsSphere2(false);
			isPoint_ = false;
			isAttack_ = true;
			plants_->SetPlantsPos(attackPos_);
			plants_->SetIsPlants(true);
		}
		else if (wall_->IsSphereCollision3(attackPos_))
		{
			wall_->SetIsSphere3(false);
			isPoint_ = false;
			isAttack_ = true;
			plants_->SetPlantsPos(attackPos_);
			plants_->SetIsPlants(true);
		}
	}
	else if (id_ == 1 || id_ == 2)
	{
		if (wall_->IsPlantsCollision(attackPos_) || wall_->IsFlaereCollision(attackPos_) ||
			wall_->IsWaterCollision(attackPos_) || stage_->IsCollisionStage(attackPos_))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
		else if (wall_->IsSphereCollision(attackPos_))
		{
			wall_->SetIsSphere(false);
			isPoint_ = false;
			isAttack_ = true;
			plants_->SetPlantsPos(attackPos_);
			plants_->SetIsPlants(true);
		}
	}
}

// ノーマル属性（剣）攻撃処理
void Player::HandleNormalAttack()
{
	constexpr float SWORD_START_ANGLE_RIGHT = 180.0f;
	constexpr float SWORD_END_ANGLE_RIGHT = 315.0f;
	constexpr float SWORD_START_ANGLE_LEFT = -180.0f;
	constexpr float SWORD_END_ANGLE_LEFT = -315.0f;

	InputManager& ins = InputManager::GetInstance();

	if (dir_ == AsoUtility::DIR::RIGHT)
	{
		if (ins.IsNew(KEY_INPUT_K))
		{
			isSword_ = true;
			if (armAngle_ <= AsoUtility::Deg2RadF(0.0f))
			{
				armAngle_ = AsoUtility::Deg2RadF(SWORD_START_ANGLE_RIGHT);
				DownMp(SWORD_MP_COST);
				PlaySoundMem(swingSoundHandle_, DX_PLAYTYPE_BACK);
			}
			armAngle_ += AsoUtility::Deg2RadF(SWORD_ROTATION_SPEED);
			if (armAngle_ >= AsoUtility::Deg2RadF(SWORD_END_ANGLE_RIGHT))
			{
				armAngle_ = AsoUtility::Deg2RadF(SWORD_START_ANGLE_RIGHT);
				DownMp(SWORD_MP_COST);
				PlaySoundMem(swingSoundHandle_, DX_PLAYTYPE_BACK);
			}
			attckAnglePoint_.x = pos_.x - sinf(armAngle_) * SWORD_ATTACK_RADIUS;
			attckAnglePoint_.y = pos_.y + cosf(armAngle_) * SWORD_ATTACK_RADIUS;
		}
		else
		{
			armAngle_ = AsoUtility::Deg2RadF(0.0f);
			StopSoundMem(swingSoundHandle_);
		}
	}
	else if (dir_ == AsoUtility::DIR::LEFT)
	{
		if (ins.IsNew(KEY_INPUT_K))
		{
			isSword_ = true;
			if (armAngle_ >= AsoUtility::Deg2RadF(0.0f))
			{
				armAngle_ = AsoUtility::Deg2RadF(SWORD_START_ANGLE_LEFT);
				DownMp(SWORD_MP_COST);
				PlaySoundMem(swingSoundHandle_, DX_PLAYTYPE_BACK);
			}
			armAngle_ -= AsoUtility::Deg2RadF(SWORD_ROTATION_SPEED);
			if (armAngle_ <= AsoUtility::Deg2RadF(SWORD_END_ANGLE_LEFT))
			{
				armAngle_ = AsoUtility::Deg2RadF(SWORD_START_ANGLE_LEFT);
				DownMp(SWORD_MP_COST);
				PlaySoundMem(swingSoundHandle_, DX_PLAYTYPE_BACK);
			}
			attckAnglePoint_.x = pos_.x - sinf(armAngle_) * SWORD_ATTACK_RADIUS;
			attckAnglePoint_.y = pos_.y + cosf(armAngle_) * SWORD_ATTACK_RADIUS;
		}
		else
		{
			armAngle_ = AsoUtility::Deg2RadF(0.0f);
			StopSoundMem(swingSoundHandle_);
		}
	}
}


void Player::Hp()
{
	if (GetHp() < 0)
	{
		SetHp(0);
	}
}

void Player::DownHp(int Down)
{
	if (invCnt_ <= 0)
	{
		SetHp(GetHp() - Down);
		SetIsAlive(false);
	}
}

void Player::Mp()
{
	if (GetMp() <= 0)
	{
		SetMp(0);
	}
}
void Player::DownMp(int Down)
{
	SetMp(GetMp() - Down);
}
void Player::ReSpawn()
{
	if (id_ != STAGE_ID_3)
	{
		if (pos_.y >= stageSize_ * FALL_LIMIT_CHIP_Y_NORMAL)
		{
			pos_.x = stageSize_ * INITIAL_POS_CHIP_X;
			pos_.y = stageSize_ * INITIAL_POS_CHIP_Y;
			SetHp(GetHp() - RESPAWN_FALL_DAMAGE);
			gameScene_->SetHitStop(HIT_STOP_FRAME);
		}
	}
	else
	{

		if (pos_.y >= stageSize_ * FALL_LIMIT_CHIP_Y_STAGE3)
		{
			pos_.x = stageSize_ * INITIAL_POS_CHIP_X;
			pos_.y = stageSize_ * INITIAL_POS_CHIP_Y;
			SetHp(GetHp() - RESPAWN_FALL_DAMAGE);
			gameScene_->SetHitStop(HIT_STOP_FRAME);
		}

	}
}

//属性攻撃処理
void Player::AttackChange(void)
{
	// 入力マネージャのインスタンスを取得
	InputManager& ins = InputManager::GetInstance();

	// 攻撃が可能な状態かどうか
	if (isAttack_)
	{
		// MPが足りていれば攻撃できる
		if (GetMp() >= ATTACK_MP_COST)
		{
			// キーKが離された瞬間（キーアップ）を検出
			if (ins.IsTrgUp(KEY_INPUT_K))
			{
				mp_ -= ATTACK_MP_COST; // 攻撃にMPを消費

				// 攻撃位置を現在の角度から計算されたポイントに設定
				attackPos_.x = attckAnglePoint_.x;
				attackPos_.y = attckAnglePoint_.y;

				movePos = upCnt;     // 上に飛ばす力を設定（溜めた量）
				isPoint_ = true;     // 攻撃の弾が存在している状態
				isAttack_ = false;   // 攻撃待機状態から外れる（次の攻撃準備まで待つ）
			}
		}
	}

	// 弾（攻撃ポイント）が存在している場合の処理
	if (isPoint_) {
		attackPos_.y -= movePos; // 上方向に移動（ジャンプと同じイメージ）
		movePos -= GRAVITY;      // 重力で徐々に落下するように減速
	}

	// ステージIDが1か2の場合（通常の地形マップ）
	if (id_ == 2 || id_ == 1)
	{
		// 攻撃のY座標が画面外（ステージ下部）に出たら弾を消す
		if (attackPos_.y > (stageSize_ * ATTACK_LIMIT_CHIP_Y_NORMAL))
		{
			isPoint_ = false;
			isAttack_ = true; // 攻撃可能状態に戻す
		}
	}
	// ステージIDが3（別レイヤーマップ等）の場合
	else if (id_ == STAGE_ID_3)
	{
		if (attackPos_.y > (stageSize_ * ATTACK_LIMIT_CHIP_Y_STAGE3))
		{
			isPoint_ = false;
			isAttack_ = true;
		}
	}

	// 右向きの処理
	if (dir_ == AsoUtility::DIR::RIGHT)
	{
		// キーKが押されている間（連打ではなく保持）
		if (ins.IsNew(KEY_INPUT_K))
		{
			// 攻撃可能なら、向きを変えたことを記録
			if (isAttack_)
			{
				dirChange_ = true;
			}

			// 腕の角度を下方向に回転（右回転なのでマイナス）
			armAngle_ -= AsoUtility::Deg2RadF(CHARGE_ANGLE_STEP);

			// 角度に応じて溜めカウントを設定（1段階ずつ増える）
			for (int i = 1; i <= CHARGE_LEVEL_MAX; ++i)
			{
				if (armAngle_ <= AsoUtility::Deg2RadF(-CHARGE_CHECK_ANGLE * i))
				{
					upCnt = i;
				}
			}

			// 角度が制限を超えたらリセット
			if (armAngle_ < AsoUtility::Deg2RadF(-CHARGE_ANGLE_LIMIT))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
				upCnt = 0;
			}
		}
		else if (!ins.IsNew(KEY_INPUT_K)) // キーが押されていなければ角度をリセット
		{
			armAngle_ = AsoUtility::Deg2RadF(0.0f);
		}

		// 角度に基づいて攻撃角度ポイントを更新（剣の先端の位置など）
		attckAnglePoint_.x = pos_.x - sinf(armAngle_) * ATTACK_TARGET_RADIUS;
		attckAnglePoint_.y = pos_.y + cosf(armAngle_) * ATTACK_TARGET_RADIUS;
	}
	// 左向きの処理
	else if (dir_ == AsoUtility::DIR::LEFT)
	{
		// 攻撃可能なら向きフラグをfalseに（左）
		if (isAttack_)
		{
			dirChange_ = false;
		}

		// キーKが押されている間
		if (ins.IsNew(KEY_INPUT_K))
		{
			// 腕の角度を左回転（+）
			armAngle_ += AsoUtility::Deg2RadF(CHARGE_ANGLE_STEP);

			// 角度に応じて溜めカウントを増やす
			for (int i = 1; i <= CHARGE_LEVEL_MAX; ++i)
			{
				if (armAngle_ >= AsoUtility::Deg2RadF(CHARGE_CHECK_ANGLE * i))
				{
					upCnt = i;
				}
			}

			// 角度が制限を超えたらリセット
			if (armAngle_ > AsoUtility::Deg2RadF(CHARGE_ANGLE_LIMIT))
			{
				armAngle_ = AsoUtility::Deg2RadF(0.0f);
				upCnt = CHARGE_LEVEL_MAX + 1;
			}
		}
		else if (!ins.IsNew(KEY_INPUT_K)) // 押してないなら角度を戻す
		{
			armAngle_ = AsoUtility::Deg2RadF(0.0f);
		}

		// 左向きの場合の角度から攻撃角度ポイントを算出
		attckAnglePoint_.x = pos_.x - sinf(armAngle_) * ATTACK_TARGET_RADIUS;
		attckAnglePoint_.y = pos_.y + cosf(armAngle_) * ATTACK_TARGET_RADIUS;
	}

	// 攻撃位置のX座標を向きに応じて移動
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

//判定の取得＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//足元
bool Player::IsHitFootPos(void)
{
	if (id_ == STAGE_ID_3)
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
	if (id_ == STAGE_ID_3)
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
	if (id_ == STAGE_ID_3)
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
	if (id_ == STAGE_ID_3)
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
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision(rightPosC_)
			|| wall_->IsWaterCollision(rightPosU_)
			|| wall_->IsWaterCollision(rightPosD_);
	}
	else
	{
		return wall_->IsWaterCollision(rightPosC_)
			|| wall_->IsWaterCollision(rightPosU_)
			|| wall_->IsWaterCollision(rightPosD_);
	}
}
//左側
bool Player::IsWaterHitLeftPos(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision(leftPosC_)
			|| wall_->IsWaterCollision(leftPosU_)
			|| wall_->IsWaterCollision(leftPosD_);

	}
	else
	{
		return wall_->IsWaterCollision(leftPosC_)
			|| wall_->IsWaterCollision(leftPosU_)
			|| wall_->IsWaterCollision(leftPosD_);
	}

}

//炎
//右側
bool Player::IsFlareHitRightPos(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision(rightPosC_)
			|| wall_->IsFlaereCollision(rightPosU_)
			|| wall_->IsFlaereCollision(rightPosD_);
	}
	else
	{
		return wall_->IsFlaereCollision(rightPosC_)
			|| wall_->IsFlaereCollision(rightPosU_)
			|| wall_->IsFlaereCollision(rightPosD_);
	}

}
//左側
bool Player::IsFlareHitLeftPos(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision(leftPosC_)
			|| wall_->IsFlaereCollision(leftPosU_)
			|| wall_->IsFlaereCollision(leftPosD_);

	}
	else
	{
		return wall_->IsFlaereCollision(leftPosC_)
			|| wall_->IsFlaereCollision(leftPosU_)
			|| wall_->IsFlaereCollision(leftPosD_);
	}
}

//植物
//右側
bool Player::IsPlantsHitRightPos(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision(rightPosC_)
			|| wall_->IsPlantsCollision(rightPosU_)
			|| wall_->IsPlantsCollision(rightPosD_);
	}
	else
	{
		return wall_->IsPlantsCollision(rightPosC_)
			|| wall_->IsPlantsCollision(rightPosU_)
			|| wall_->IsPlantsCollision(rightPosD_);
	}
}
//左側
bool Player::IsPlantsHitLeftPos(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision(leftPosC_)
			|| wall_->IsPlantsCollision(leftPosU_)
			|| wall_->IsPlantsCollision(leftPosD_);
	}
	else
	{
		return wall_->IsPlantsCollision(leftPosC_)
			|| wall_->IsPlantsCollision(leftPosU_)
			|| wall_->IsPlantsCollision(leftPosD_);
	}
}

bool Player::IsWaterHitRightPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision2(rightPosC_)
			|| wall_->IsWaterCollision2(rightPosU_)
			|| wall_->IsWaterCollision2(rightPosD_);
	}
	return false;
}

bool Player::IsWaterHitLeftPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision2(leftPosC_)
			|| wall_->IsWaterCollision2(leftPosU_)
			|| wall_->IsWaterCollision2(leftPosD_);
	}
	return false;
}

bool Player::IsFlareHitRightPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision2(rightPosC_)
			|| wall_->IsFlaereCollision2(rightPosU_)
			|| wall_->IsFlaereCollision2(rightPosD_);
	}
	return false;
}

bool Player::IsFlareHitLeftPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision2(leftPosC_)
			|| wall_->IsFlaereCollision2(leftPosU_)
			|| wall_->IsFlaereCollision2(leftPosD_);
	}
	return false;
}

bool Player::IsPlantsHitRightPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision2(rightPosC_)
			|| wall_->IsPlantsCollision2(rightPosU_)
			|| wall_->IsPlantsCollision2(rightPosD_);
	}
	return false;
}

bool Player::IsPlantsHitLeftPos2(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision2(leftPosC_)
			|| wall_->IsPlantsCollision2(leftPosU_)
			|| wall_->IsPlantsCollision2(leftPosD_);
	}
	return false;
}

bool Player::IsWaterHitRightPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision3(rightPosC_)
			|| wall_->IsWaterCollision3(rightPosU_)
			|| wall_->IsWaterCollision3(rightPosD_);
	}
	return false;
}

bool Player::IsWaterHitLeftPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsWaterCollision3(leftPosC_)
			|| wall_->IsWaterCollision3(leftPosU_)
			|| wall_->IsWaterCollision3(leftPosD_);
	}
	return false;
}

bool Player::IsFlareHitRightPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision3(rightPosC_)
			|| wall_->IsFlaereCollision3(rightPosU_)
			|| wall_->IsFlaereCollision3(rightPosD_);
	}
	return false;
}

bool Player::IsFlareHitLeftPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsFlaereCollision3(leftPosC_)
			|| wall_->IsFlaereCollision3(leftPosU_)
			|| wall_->IsFlaereCollision3(leftPosD_);
	}
	return false;
}

bool Player::IsPlantsHitRightPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision3(rightPosC_)
			|| wall_->IsPlantsCollision3(rightPosU_)
			|| wall_->IsPlantsCollision3(rightPosD_);
	}
	return false;
}

bool Player::IsPlantsHitLeftPos3(void)
{
	if (id_ == STAGE_ID_3)
	{
		return wall_->IsPlantsCollision3(leftPosC_)
			|| wall_->IsPlantsCollision3(leftPosU_)
			|| wall_->IsPlantsCollision3(leftPosD_);
	}
	return false;
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
		pos_.y = static_cast<float>(mapChipUpSideY) - HALF_COL_SIZE_Y - COL_OFFSET - COL_POSITION_ADJUST_Y;

		//ジャンプフラグを切る
		if (isJump_)
		{
			isJump_ = false;
		}
	}
	else if (!isJump_)
	{
		//ジャンプフラグを立てる
		isJump_ = true;
		movePosY_ = 0.0f;
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
		//プレイヤーの頭側がマップチップの下側になるように設定する
		pos_.y = static_cast<float>(mapChipDownSideY) + HALF_COL_SIZE_Y + COL_OFFSET + COL_POSITION_ADJUST_Y;

		//頭がぶつかった
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
		//プレイヤーの左側がマップチップの右側になるように設定する
		pos_.x = static_cast<float>(mapChipRightSideX) + HALF_COL_SIZE_X + COL_OFFSET;
		//左に移動量があるときは移動量をなくす
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//壁との当たり判定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//水との当たり判定
//右
void Player::CollisionWaterRightSide(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsWaterHitRightPos();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionWaterLeftSide(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsWaterHitLeftPos();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//水との当たり判定
//右
void Player::CollisionWaterRightSide2(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsWaterHitRightPos2();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos2().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionWaterLeftSide2(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsWaterHitLeftPos2();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos2().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//水との当たり判定
//右
void Player::CollisionWaterRightSide3(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsWaterHitRightPos();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionWaterLeftSide3(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsWaterHitLeftPos3();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetWaterPos3().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}

//炎との当たり判定
//右
void Player::CollisionFlareRightSide(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsFlareHitRightPos();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionFlareLeftSide(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsFlareHitLeftPos();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//炎との当たり判定
//右
void Player::CollisionFlareRightSide2(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsFlareHitRightPos2();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos2().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionFlareLeftSide2(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsFlareHitLeftPos2();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos2().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//炎との当たり判定
//右
void Player::CollisionFlareRightSide3(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsFlareHitRightPos3();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos3().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionFlareLeftSide3(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsFlareHitLeftPos3();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetFlarePos3().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}

//植物との当たり判定
//右
void Player::CollisionPlantsRightSide(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsPlantsHitRightPos();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionPlantsLeftSide(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsPlantsHitLeftPos();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//植物との当たり判定
//右
void Player::CollisionPlantsRightSide2(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsPlantsHitRightPos2();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos2().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionPlantsLeftSide2(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsPlantsHitLeftPos2();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos2().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}
//植物との当たり判定
//右
void Player::CollisionPlantsRightSide3(void)
{
	CalcRightSidePos();

	isHitRightSide_ = IsPlantsHitRightPos3();

	if (isHitRightSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos3().x - wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ > 0.0f)movePosX_ = 0.0f;
	}
}
//左
void Player::CollisionPlantsLeftSide3(void)
{
	CalcLeftSidePos();

	isHitLeftSide_ = IsPlantsHitLeftPos3();

	if (isHitLeftSide_)
	{
		DownHp(DAMAGE_WALL_HP);
		pos_.x = wall_->GetPlantsPos3().x + wall_->FLARE_SIZE_X + wall_->FLARE_HALF_SIZE_X;
		if (movePosX_ < 0.0f)movePosX_ = 0.0f;
	}
}


//判定の可視化＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－－－
void Player::DrawHitCollision(void)
{
	//足元の当たり判定の可視化
	constexpr unsigned int FOOT_HIT_POS_COLOR = COLOR_RED;
	constexpr int CHIRCLE_SIZE = 2;
	DrawCircle(footPosC_.x - camera_->GetCameraPos().x, footPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);
	DrawCircle(footPosL_.x - camera_->GetCameraPos().x, footPosL_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);
	DrawCircle(footPosR_.x - camera_->GetCameraPos().x, footPosR_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, FOOT_HIT_POS_COLOR);

	//頭側の当たり判定の可視化
	constexpr unsigned int HEAD_HIT_POS_COLOR = COLOR_BLACK;
	DrawCircle(headPosC_.x - camera_->GetCameraPos().x, headPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);
	DrawCircle(headPosL_.x - camera_->GetCameraPos().x, headPosL_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);
	DrawCircle(headPosR_.x - camera_->GetCameraPos().x, headPosR_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, HEAD_HIT_POS_COLOR);

	//右側の当たり判定の可視化
	constexpr unsigned int RIGHT_HIT_POS_COLOR = COLOR_BLUE;
	DrawCircle(rightPosC_.x - camera_->GetCameraPos().x, rightPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);
	DrawCircle(rightPosD_.x - camera_->GetCameraPos().x, rightPosD_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);
	DrawCircle(rightPosU_.x - camera_->GetCameraPos().x, rightPosU_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, RIGHT_HIT_POS_COLOR);

	//左側の当たり判定の可視化
	constexpr unsigned int LEFT_HIT_POS_COLOR = COLOR_PURPLE;
	DrawCircle(leftPosC_.x - camera_->GetCameraPos().x, leftPosC_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);
	DrawCircle(leftPosD_.x - camera_->GetCameraPos().x, leftPosD_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);
	DrawCircle(leftPosU_.x - camera_->GetCameraPos().x, leftPosU_.y - camera_->GetCameraPos().y, CHIRCLE_SIZE, LEFT_HIT_POS_COLOR);

	//当たり判定確認用デバッグ文字
	constexpr unsigned int STRING_COLOR = COLOR_BLACK;
	constexpr int DEBUG_TEXT_X = 45;
	if (isHitFoot_) DrawString(DEBUG_TEXT_X, 0, "下側が当たっている", STRING_COLOR);
	if (isHitHead_) DrawString(DEBUG_TEXT_X, 20, "上側が当たっている", STRING_COLOR);
	if (isHitRightSide_) DrawString(DEBUG_TEXT_X, 40, "右側が当たっている", STRING_COLOR);
	if (isHitLeftSide_) DrawString(DEBUG_TEXT_X, 60, "左側が当たっている", STRING_COLOR);
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

bool Player::GetIsAlive()
{
	return isAlive_;
}

void Player::SetIsAlive(bool is)
{
	isAlive_ = is;
}

int Player::GetStageSize()
{
	return stageSize_;
}

void Player::SetStageSize(int size)
{
	stageSize_ = size;
}


Vector2 Player::GetAttackPos()
{
	return attackPos_;
}

void Player::SetAttackPos(Vector2 attackPos)
{
	attackPos_ = attackPos;
}

bool Player::GetAttack()
{
	return isAttack_;
}

void Player::SetAttack(bool isAttack)
{
	isAttack_ = isAttack;
}

bool Player::GetPoint()
{
	return isPoint_;
}

void Player::SetPoint(bool isPoint)
{
	isPoint_ = isPoint;
}

Vector2F Player::GetAttckAnglePoint()
{
	return attckAnglePoint_;
}

void Player::SetAttckAnglePoint(Vector2F attckAnglePoint)
{
	attckAnglePoint_ = attckAnglePoint;
}
bool Player::GetIsEF()
{
	return eF_;
}

void Player::SetIsEF(bool is)
{
	eF_ = is;
}

bool Player::GetHitFoot()
{
	return isHitFoot_;
}

void Player::SetHitFoot(bool isHitFoot)
{
	isHitFoot_ = isHitFoot;
}

bool Player::GetSword()
{
	return isSword_;
}

void Player::SetSword(bool isSword)
{
	isSword_ = isSword;
}

Vector2 Player::GetCamera()
{
	return cameraPos_;

}


//チェンジ関数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Player::MoveChange(void)
{
	switch (moveType_)
	{
	case MOVE_TYPE::STOP:
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
		animaAem_ = ARM_IMG_FIRE;
		cr_ = COLOR_RED;

		break;
	case ELEMENT_TYPE::WATER:
		animaAem_ = ARM_IMG_WATER;
		cr_ = COLOR_BLUE;

		break;
	case ELEMENT_TYPE::PLANT:
		animaAem_ = ARM_IMG_PLANT;
		cr_ = COLOR_GREEN;

		break;
	case ELEMENT_TYPE::NORMAL:
		animaAem_ = ARM_IMG_NORMAL;
		cr_ = COLOR_WHITE;
		break;
	}
}