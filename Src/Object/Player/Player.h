#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
#include "../../Utility/AsoUtility.h"
class Stage;
class GameScene;
class Camera;
class Wall;
class Blast;
class Water;
class Plants;

class Player
{
public:

	// プレイヤーの移動タイプを定義
	enum class MOVE_TYPE
	{
		NONE,  // 未定義 or 使用しない状態
		STOP,  // 静止状態
		MOVE,  // 移動中
	};

	// プレイヤーの属性タイプを定義
	enum class ELEMENT_TYPE
	{
		NONE,    // 未定義
		NORMAL,  // 通常（無属性）
		WATER,   // 水属性
		PLANT,   // 植物属性
		FIRE,    // 火属性
	};

	// ============================= 定数定義 =============================

	// 当たり判定のサイズ（プレイヤーの体の大きさ）
	static constexpr int COL_SIZE_X = 58; // 横幅
	static constexpr int COL_SIZE_Y = 58; // 高さ
	static constexpr int HALF_COL_SIZE_X = COL_SIZE_X / 2; // 横半分（中心基準計算用）
	static constexpr int HALF_COL_SIZE_Y = COL_SIZE_Y / 2; // 縦半分（中心基準計算用）
	static constexpr int COL_OFFSET = 1; // 当たり判定の誤差補正用
	static constexpr float COL_POSITION_ADJUST_Y = 3.0f; // ブロックめり込み補正用Yオフセット

	// 移動に関する定数
	static constexpr float MOVE_SPEED = 2.0f;       // 基本移動速度
	static constexpr float MOVE_POWER = 5.0f;       // 移動時の力（加速初期値）
	static constexpr float DASH_SPEED_MULTIPLIER = 3.0f; // ダッシュ時の速度倍率

	// 重力
	static constexpr float GRAVITY = 0.3f;          // 毎フレーム加算する重力
	static constexpr float MAX_GRAVITY = 8.5f;      // 重力の最大値

	// ジャンプ
	static constexpr float JUMP_POW = -9.5f;        // ジャンプの初期速度（上方向なのでマイナス）

	// 加減速
	static constexpr float MOVE_ACC_POW = 0.5f;     // 加速度
	static constexpr float MOVE_DEC_POW = 0.05f;    // 減速度
	static constexpr float MAX_MOVE_SPEED = 2.0f;   // 最大移動速度

	// HP・MP・ステータス関連
	static constexpr int MAX_HP = 100;              // 最大HP
	static constexpr int MAX_MP = 100;              // 最大MP
	static constexpr int ATTACK_MP_COST = 10;       // 属性攻撃時のMP消費量
	static constexpr int SWORD_MP_COST = 1;         // 剣攻撃時のMP消費量
	static constexpr int DAMAGE_WALL_HP = 50;       // 壁接触時のダメージ量
	static constexpr int RESPAWN_FALL_DAMAGE = 10;  // 落下死亡時の復帰ダメージ量

	// タイマー・フレーム数関連
	static constexpr int RESPAWN_INVINCIBLE_TIME = 60; // 復活時の無敵フレーム数
	static constexpr int REGENE_INTERVAL = 30;         // 自動回復間隔（フレーム）
	static constexpr int REGENE_MP_AMOUNT = 1;         // 自動回復MP量
	static constexpr int HIT_STOP_FRAME = 30;          // ヒットストップ時間

	// ステージマップチップ位置（マス単位）
	static constexpr int INITIAL_POS_CHIP_X = 2;       // 初期位置X（マップチップ単位）
	static constexpr int INITIAL_POS_CHIP_Y = 8;       // 初期位置Y（マップチップ単位）
	static constexpr int FALL_LIMIT_CHIP_Y_NORMAL = 13; // 落下判定限界Y（ステージ1,2）
	static constexpr int FALL_LIMIT_CHIP_Y_STAGE3 = 25; // 落下判定限界Y（ステージ3）
	static constexpr int ATTACK_LIMIT_CHIP_Y_NORMAL = 12; // 攻撃消滅Y判定（ステージ1,2）
	static constexpr int ATTACK_LIMIT_CHIP_Y_STAGE3 = 24; // 攻撃消滅Y判定（ステージ3）

	// アニメーション関連
	static constexpr float ANIME_SPEED_MOVE = 0.1f;    // 移動アニメ更新速度
	static constexpr float ANIME_SPEED_STOP = 0.05f;   // 静止アニメ更新速度
	static constexpr int ANIME_IDLE_FRAME_MAX = 2;     // 待機アニメ枚数
	static constexpr int ANIME_MOVE_FRAME_START = 6;   // 走りアニメ開始インデックス
	static constexpr int ANIME_MOVE_FRAME_MAX = 11;    // 走りアニメ終了インデックス

	// 攻撃・角度関連
	static constexpr float SWORD_ATTACK_RADIUS = 100.0f;  // 剣攻撃の判定距離
	static constexpr float ATTACK_TARGET_RADIUS = 30.0f;  // 属性攻撃ターゲットの距離
	static constexpr float SWORD_ROTATION_SPEED = 7.0f;   // 剣の振り回転速度（度）
	static constexpr float SWORD_DRAW_ANGLE_OFFSET = 130.0f; // 剣描画時の角度オフセット（度）
	static constexpr float CHARGE_ANGLE_STEP = 5.0f;      // 溜め時の腕の回転速度（度）
	static constexpr float CHARGE_ANGLE_LIMIT = 120.0f;   // 溜め角度の最大値（度）
	static constexpr float CHARGE_CHECK_ANGLE = 10.0f;    // 溜めカウント計算時の単位角度（度）
	static constexpr int CHARGE_LEVEL_MAX = 11;           // 溜めカウントの最大レベル

	// エフェクト描画関連
	static constexpr float EF_RADIUS_ADD = 3.0f;         // エフェクト半径の毎フレーム増加量
	static constexpr float EF_MAX_RADIUS = 60.0f;         // エフェクトの最大半径
	static constexpr float EF_SPHERE_DEBUG_RADIUS = 32.0f;// デバッグ用円半径

	// カラー定数
	static constexpr unsigned int COLOR_WHITE = 0xffffff;
	static constexpr unsigned int COLOR_RED = 0xff0000;
	static constexpr unsigned int COLOR_BLUE = 0x0000ff;
	static constexpr unsigned int COLOR_GREEN = 0x00ff00;
	static constexpr unsigned int COLOR_PURPLE = 0xff00ff;
	static constexpr unsigned int COLOR_BLACK = 0x000000;

	// アニメーション用パーツインデックス
	static constexpr int ARM_IMG_NORMAL = 0;
	static constexpr int ARM_IMG_WATER = 1;
	static constexpr int ARM_IMG_PLANT = 2;
	static constexpr int ARM_IMG_FIRE = 3;

	// Stage ID
	static constexpr int STAGE_ID_3 = 3;

	// ============================= メンバ変数 =============================
private:

	// 画像ハンドル類
	int* img_;          // 本体スプライト（配列）
	int* armImg_;       // 腕のスプライト（配列）
	int sordImg_;       // 剣の画像（単体）※スペルミスの可能性: sword？
	int swingSoundHandle_; // 剣を振る音のハンドル

	int invCnt_;        // 無敵時間カウント
	bool isAlive_;      // 生存フラグ

	int stageSize_;     // ステージ1マスのサイズ（描画などに使用）

	unsigned int cr_;   // 色（おそらくARGBまたはRGB）

	// 属性
	ELEMENT_TYPE elementType_; // プレイヤーの属性

	// アニメーション関連
	float armAngle_;       // 腕の角度（ラジアン）
	float animationTime_;  // アニメーション経過時間
	int animationCount_;   // アニメーションフレーム
	int animaAem_;         // 腕の切り替え

	MOVE_TYPE moveType_;   // 現在の移動状態

	Vector2F pos_;         // プレイヤーの位置（小数付き2D）

	// 移動速度・状態
	float movePosX_;       // 横移動量
	float movePosY_;       // 縦移動量
	float speed_;          // 現在速度
	float maxSpeed_;       // 最大速度（移動上限）
	bool isJump_;          // ジャンプ中かどうか

	// ================================= 攻撃関連 =================================
	bool isAttack_;        // 攻撃中かどうか
	bool isPoint_;         // 攻撃ポイント有効フラグ
	bool eF_;              // 属性切り替え中フラグ
	bool dirChange_;       // 向き変更したかどうか
	bool isSword_;          // 剣を振ってるか
	int upCnt;             // 腕の上げ具合カウント（角度段階）

	Vector2 attackPos_;    // 攻撃のターゲット座標

	float armPower;        // 腕の力
	float movePos;         // 移動方向の量

	// ============================= ステータス管理 =============================
	int hp_;               // HP
	int mp_;               // MP
	int regeneCnt_;        // 回復タイミングカウント
	int mpRegene_;         // MP自動回復量
	int radius_;           // 半径

	// ============================= 当たり判定用座標群 =============================
	// 足元（デバッグ表示用）
	Vector2 footPosC_;     // 足中央
	Vector2 footPosL_;     // 足左
	Vector2 footPosR_;     // 足右

	// 頭部（デバッグ表示用）
	Vector2 headPosC_;
	Vector2 headPosL_;
	Vector2 headPosR_;

	// 右側（デバッグ表示用）
	Vector2 rightPosC_;
	Vector2 rightPosU_;
	Vector2 rightPosD_;

	// 左側（デバッグ表示用）
	Vector2 leftPosC_;
	Vector2 leftPosU_;
	Vector2 leftPosD_;

	// 当たり判定ヒットフラグ（デバッグ表示用）
	bool isHitHead_;
	bool isHitFoot_;
	bool isHitRightSide_;
	bool isHitLeftSide_;

	// ============================= ゲームオブジェクト参照 =============================
	Camera* camera_;        // カメラ
	Stage* stage_;          // ステージ
	Wall* wall_;            // 壁
	Blast* blast_;          // 爆発演出
	Water* water_;          // 水エフェクト演出
	Plants* plants_;        // 植物演出
	GameScene* gameScene_;


	AsoUtility::DIR dir_;   // 向き（左 or 右）

	Vector2 cameraPos_;     // カメラ位置の保持

	// ============================= デバッグ表示・管理 =============================
	Vector2F attckPoint_;         // 攻撃点
	Vector2F attckAnglePoint_;    // 攻撃方向から求めた点

	int id_;                      // ステージID

	// ============================= メンバ関数群 =============================
public:

	// コンストラクタ・デストラクタ
	Player();
	~Player();

	// 初期化関数
	void Init(Camera* camera, Stage* stage, Wall* wall, Blast* blast, Water* water, Plants* plants, GameScene* gameScene);

	// 更新・描画
	void Update(); // 毎フレームの更新
	void Draw();   // 描画

	// 基本動作
	void Move();           // 移動処理
	void Anime();          // アニメーション更新
	void Attack();         // 攻撃処理
	void Hp();             // HP処理
	void DownHp(int Down); // HP減少処理
	void Mp();             // MP処理
	void DownMp(int Down); // MP減少処理
	void ReSpawn();        // 復活処理

	// 当たり判定計算（各方向）
	void CalcFootPos(void);
	void CalcHeadPos(void);
	void CalcRightSidePos(void);
	void CalcLeftSidePos(void);

	// 当たり判定判定
	bool IsHitFootPos(void);
	bool IsHitHeadPos(void);
	bool IsHitRightPos(void);
	bool IsHitLeftPos(void);

	// 属性別の左右衝突判定（複数レイヤー）
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

	// 衝突反応処理（左右・上下・属性レイヤー別）
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

	// 衝突判定の描画（デバッグ）
	void DrawHitCollision(void);

	// 座標変換
	Vector2 World2MapPos(Vector2 worldPos); // ワールド座標 → マップ座標変換

	// プレイヤーの位置取得・設定
	Vector2F GetPlayerPos(void);
	void SetPlayerPos(Vector2F pos);

	// 状態管理
	void MoveChange(void);      // 移動状態更新
	void ElementChange(void);   // 属性変更処理
	void AttackChange(void);    // 攻撃ステータス更新処理

	// HP・MP getter/setter
	int GetHp(void);
	void SetHp(int hp);
	int GetMp(void);
	void SetMp(int mp);

	// 色 getter/setter
	unsigned int GetCr(void);
	void SetCr(int cr);

	// 生死フラグ
	bool GetIsAlive();
	void SetIsAlive(bool is);

	// ステージサイズ
	int GetStageSize();
	void SetStageSize(int size);

	// 攻撃用位置など
	Vector2 GetAttackPos();
	void SetAttackPos(Vector2 attackPos);

	bool GetAttack();
	void SetAttack(bool isAttack);

	bool GetPoint();
	void SetPoint(bool isPoint);

	Vector2F GetAttckAnglePoint();
	void SetAttckAnglePoint(Vector2F attckAnglePoint);

	bool GetIsEF();
	void SetIsEF(bool is);

	bool GetHitFoot();
	void SetHitFoot(bool isHitFoot);

	bool GetSword();
	void SetSword(bool isSword);

	// カメラ位置取得
	Vector2 GetCamera();


	void UpdateElementSelectInputs(); // 属性切り替えキー入力の更新
	void HandleFireAttack();          // 火属性攻撃の判定処理
	void HandleWaterAttack();         // 水属性攻撃の判定処理
	void HandlePlantAttack();         // 植物属性攻撃の判定処理
	void HandleNormalAttack();        // ノーマル属性（剣）攻撃処理

};