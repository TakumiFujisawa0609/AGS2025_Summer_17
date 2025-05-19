#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
#include "../../Utility/AsoUtility.h"
class Stage;
class Camera;


class Player
{
public:
	//定数
	// 当たり判定サイズ
	static constexpr int COL_SIZE_X = 32;						// 横
	static constexpr int COL_SIZE_Y = 32;						// 縦
	static constexpr int HALF_COL_SIZE_X = COL_SIZE_X / 2;	//横半分
	static constexpr int HALF_COL_SIZE_Y = COL_SIZE_Y / 2;	//縦半分
	static constexpr int COL_OFFSET = 1;						//補正値
	// 移動速度
	static constexpr float MOVE_SPEED = 1.5f;

	//重力
	static constexpr float GRAVITY = 0.3f;

	//重力最大値
	static constexpr float MAX_GRAVITY = 8.5f;

	//ジャンプ力
	static constexpr float JUMP_POW = -8.5f;

	//加速度
	static constexpr float MOVE_ACC_POW = 0.5f;

	//減速度
	static constexpr float MOVE_DEC_POW = 0.05f;

	//移動速度最大値
	static constexpr float MAX_MOVE_SPEED = 1.5f;

private:
	//変数
	int* img_;

	//アニメーション
	float animationTime_;
	int animationCount_;
	
	Vector2F pos_;//位置

	float movePosX_;
	float movePosY_;

	bool isJump_;//ジャンプ中かどうか

	//足元
	//（デバッグ表示のためメンバー変数化）
	Vector2 footPosC_;//中心
	Vector2 footPosL_;//左側
	Vector2 footPosR_;//右側

	//頭
	//（デバッグ表示のためメンバー変数化）
	Vector2 headPosC_;//中心
	Vector2 headPosL_;//左側
	Vector2 headPosR_;//右側

	//右側
	//（デバッグ表示のためメンバー変数化）
	Vector2 rightPosC_;//中心
	Vector2 rightPosU_;//上側
	Vector2 rightPosD_;//下側

	//左側
	//（デバッグ表示のためメンバー変数化）
	Vector2 leftPosC_;//中心
	Vector2 leftPosU_;//上側
	Vector2 leftPosD_;//下側

	//当たり判定チェック
	//（デバッグ表示のためメンバー変数化）
	bool isHitHead_;
	bool isHitFoot_;
	bool isHitRightSide_;
	bool isHitLeftSide_;

	//カメラ
	Camera* camera_;
	//ステージ
	Stage* stage_;

	AsoUtility::DIR dir_;
public:
	
	//プロトタイプ宣言
	Player();
	~Player();
	void Init(Camera*camera,Stage*stage);
	void Update();
	void Draw();

	//関数
	void Move();
	

	//（デバッグ表紙のために計算処理と衝突判定を別にしておく）
	void CalcFootPos(void);
	void CalcHeadPos(void);
	void CalcRightSidePos(void);
	void CalcLeftSidePos(void);

	//（デバック表示のために計算処理と衝突判定を別にしておく）
	bool IsHitFootPos(void);
	bool IsHitHeadPos(void);
	bool IsHitRightPos(void);
	bool IsHitLeftPos(void);

	//衝突判定
	void CollisionFoot(void);
	void CollisionHead(void);
	void CollisionRightSide(void);
	void CollisionLeftSide(void);

	void DrawHitCollision(void);

	Vector2 World2MapPos(Vector2 worldPos);

	Vector2F GetPlayerPos(void);
};

