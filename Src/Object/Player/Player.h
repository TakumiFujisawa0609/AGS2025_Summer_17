#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
#include "../../Utility/AsoUtility.h"
class Stage;
class Camera;
class Wall;
class Blast;
class Water;
class Plants;

class Player
{
public:

	enum class MOVE_TYPE
	{
		NONE,
		STOP,
		MOVE,
	};

	enum class ELEMENT_TYPE
	{
		NONE,
		NORMAL,
		WATER,
		PLANT,
		FIRE,
	};


	//定数
	// 当たり判定サイズ
	static constexpr int COL_SIZE_X = 58;						// 横
	static constexpr int COL_SIZE_Y = 58;						// 縦
	static constexpr int HALF_COL_SIZE_X = COL_SIZE_X / 2;	//横半分
	static constexpr int HALF_COL_SIZE_Y = COL_SIZE_Y / 2;	//縦半分
	static constexpr int COL_OFFSET = 1;						//補正値
	// 移動速度
	static constexpr float MOVE_SPEED = 2.0f;
	static constexpr float MOVE_POWER = 5.0f;

	//重力
	static constexpr float GRAVITY = 0.3f;

	//重力最大値
	static constexpr float MAX_GRAVITY = 8.5f;

	//ジャンプ力
	static constexpr float JUMP_POW = -9.5f;

	//加速度
	static constexpr float MOVE_ACC_POW = 0.5f;

	//減速度
	static constexpr float MOVE_DEC_POW = 0.05f;

	//移動速度最大値
	static constexpr float MAX_MOVE_SPEED = 2.0f;

	//MAX HP
	static constexpr int MAX_HP = 100;
	//MAX MP
	static constexpr int MAX_MP = 100;
private:
	//変数
	int* img_;
	int* armImg_;
	int sordImg_;
	int invCnt_;
	bool isAlive_;

	int stageSize_;

	unsigned int cr_;

	//属性
	ELEMENT_TYPE elementType_;//属性タイプ

	//アニメーション
	float armAngle_;
	float animationTime_;
	int animationCount_;
	int animaAem_;
	MOVE_TYPE moveType_;//移動タイプ
	
	Vector2F pos_;//位置

	//移動量
	float movePosX_;
	float movePosY_;
	float speed_;
	float maxSpeed_;
	bool isJump_;//ジャンプ中かどうか

	//ATTACK//==================================================================================================================
	//攻撃中かどうか
	bool isAttack_;//攻撃中かどうか
	bool isPoint_;
	bool eF_;
	bool dirChange_;
	bool isSotd_;
	int upCnt;
	Vector2 attackPos_;

	float armPower;
	float movePos;
	
	//==========================================================================================================================

	//ヒットポイント・マジックポイント
	int hp_;
	int mp_;

	int regeneCnt_;
	int mpRegene_;

	int radius_;

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
	//壁
	Wall* wall_;

	Blast* blast_;

	Water* water_;

	Plants* plants_;

	AsoUtility::DIR dir_;

	
	Vector2 cameraPos_;


	//デバック表示==============================================================================
	Vector2F attckPoint_;
	Vector2F attckAnglePoint_;

	int id_;


public:
	
	//プロトタイプ宣言
	Player();
	~Player();
	void Init(Camera*camera,Stage*stage,Wall*wall,Blast*blast,Water* water,Plants*plants);
	void Update();
	void Draw();

	//関数
	void Move();
	void Anime();
	void Attack();
	void Hp();
	void DownHp(int Down);
	void Mp();
	void DownMp(int Down);
	void ReSpawn();


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


	bool IsWaterHitRightPos(void);
	bool IsWaterHitLeftPos(void);

	
	bool IsFlareHitRightPos(void);
	bool IsFlareHitLeftPos(void);


	bool IsPlantsHitRightPos(void);
	bool IsPlantsHitLeftPos(void);

	bool IsWaterHitRightPos2(void);
	bool IsWaterHitLeftPos2(void);


	bool IsFlareHitRightPos2(void);
	bool IsFlareHitLeftPos2(void);


	bool IsPlantsHitRightPos2(void);
	bool IsPlantsHitLeftPos2(void);

	bool IsWaterHitRightPos3(void);
	bool IsWaterHitLeftPos3(void);


	bool IsFlareHitRightPos3(void);
	bool IsFlareHitLeftPos3(void);


	bool IsPlantsHitRightPos3(void);
	bool IsPlantsHitLeftPos3(void);

	

	//衝突判定
	void CollisionFoot(void);
	void CollisionHead(void);
	void CollisionRightSide(void);
	void CollisionLeftSide(void);

	
	void CollisionWaterRightSide(void);
	void CollisionWaterLeftSide(void);

	
	void CollisionFlareRightSide(void);
	void CollisionFlareLeftSide(void);

	
	void CollisionPlantsRightSide(void);
	void CollisionPlantsLeftSide(void);

	void CollisionWaterRightSide2(void);
	void CollisionWaterLeftSide2(void);


	void CollisionFlareRightSide2(void);
	void CollisionFlareLeftSide2(void);


	void CollisionPlantsRightSide2(void);
	void CollisionPlantsLeftSide2(void);

	void CollisionWaterRightSide3(void);
	void CollisionWaterLeftSide3(void);


	void CollisionFlareRightSide3(void);
	void CollisionFlareLeftSide3(void);


	void CollisionPlantsRightSide3(void);
	void CollisionPlantsLeftSide3(void);
	

	//衝突判定描画
	void DrawHitCollision(void);

	
	Vector2 World2MapPos(Vector2 worldPos);

	//プレイヤーの位置を取得
	Vector2F GetPlayerPos(void);
	void SetPlayerPos(Vector2F pos);

	//移動状態管理
	void MoveChange(void);

	//属性管理
	void ElementChange(void);

	void AttackChange(void);

	int GetHp(void);
	void SetHp(int hp);

	int GetMp(void);
	void SetMp(int mp);

	unsigned int GetCr(void);
	void SetCr(int cr);

	bool GetIsAlive();
	void SetIsAlive(bool is);

	int GetStageSize();
	void SetStageSize(int size);

	bool GetIsEF();
	void SetIsEF(bool is);

	Vector2 GetCamera();

};

