#pragma once
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"
class Camera;

class Wall
{
public:
	//植物壁サイズ
	static constexpr int PLANTS_SIZE_X = 64;
	static constexpr int PLANTS_SIZE_Y = 64 * 3;
	static constexpr int PLANTS_HALF_SIZE_X = PLANTS_SIZE_X / 2;
	static constexpr int PLANTS_HALF_SIZE_Y = PLANTS_SIZE_Y / 2;

	//フレア壁サイズ
	static constexpr int FLARE_SIZE_X = 64;
	static constexpr int FLARE_SIZE_Y = 64 * 3;
	static constexpr int FLARE_HALF_SIZE_X = FLARE_SIZE_X / 2;
	static constexpr int FLARE_HALF_SIZE_Y = FLARE_SIZE_Y / 2;

	//水壁サイズ
	static constexpr int WATER_SIZE_X = 64;
	static constexpr int WATER_SIZE_Y = 64 * 3;
	static constexpr int WATER_HALF_SIZE_X = WATER_SIZE_X / 2;
	static constexpr int WATER_HALF_SIZE_Y = WATER_SIZE_Y / 2;

	//フレアのアニメーションフレーム数
	static constexpr int FLARE_ANIM_FRAME = 3;

	//水のアニメーションフレーム数
	static constexpr int WATER_ANIM_FRAME = 5;

private:
	//画像
	int plantsImg_;
	int* flareImg_;
	int*waterImg_;
	int* wSphereImg_;

	int stageSize_;

	int reWallF_;
	int reWallP_;
	int reWallS_;

	int reWallF2_;
	int reWallP2_;
	int reWallS2_;

	int reWallF3_;
	int reWallP3_;
	int reWallS3_;

	//画像の数
	int flareNo_;
	int waterNo_;
	int sphereNo_;

	//座標
	Vector2F plantsPos_;
	Vector2F flarePos_;
	Vector2F waterPos_;
	Vector2F spherePos_;

	//生存フラグ
	bool isPlantsAlive_;
	bool isFlareAlive_;
	bool isWaterAlive_;
	bool isSphereAlive_;

	//座標
	Vector2F plantsPos2_;
	Vector2F flarePos2_;
	Vector2F waterPos2_;
	Vector2F spherePos2_;

	//生存フラグ
	bool isPlantsAlive2_;
	bool isFlareAlive2_;
	bool isWaterAlive2_;
	bool isSphereAlive2_;

	//座標
	Vector2F plantsPos3_;
	Vector2F flarePos3_;
	Vector2F waterPos3_;
	Vector2F spherePos3_;

	//生存フラグ
	bool isPlantsAlive3_;
	bool isFlareAlive3_;
	bool isWaterAlive3_;
	bool isSphereAlive3_;

	//アニメーションカウント
	int flareAnimCount_;
	int waterAnimCount_;

	Camera* camera_;


public:
	Wall();
	~Wall();
	void Init(Camera*camera);
	void Update();
	void Draw();
	void Init1();
	void Update1();
	void Draw1();
	void Init2();
	void Update2();
	void Draw2();
	void AnimUpdate();




	Vector2F GetPlantsPos();
	Vector2F GetFlarePos();
	Vector2F GetWaterPos();

	Vector2F GetPlantsPos2();
	Vector2F GetFlarePos2();
	Vector2F GetWaterPos2();

	Vector2F GetPlantsPos3();
	Vector2F GetFlarePos3();
	Vector2F GetWaterPos3();

	bool IsPlantsAlive();
	bool IsFlareAlive();
	bool IsWaterAlive();

	void SetPlantsPos(Vector2F pos);
	void SetFlarePos(Vector2F pos);
	void SetWaterPos(Vector2F pos);
	
	void SetIsPlants(bool isAlive);
	void SetIsFlare(bool isAlive);
	void SetIsWater(bool isAlive);
	void SetIsSphere(bool isAlive);

	void SetIsPlants2(bool isAlive);
	void SetIsFlare2(bool isAlive);
	void SetIsWater2(bool isAlive);
	void SetIsSphere2(bool isAlive);
	
	void SetIsPlants3(bool isAlive);
	void SetIsFlare3(bool isAlive);
	void SetIsWater3(bool isAlive);
	void SetIsSphere3(bool isAlive);

	
	bool IsWaterCollision(Vector2 pos);
	bool IsFlaereCollision(Vector2 pos);
	bool IsPlantsCollision(Vector2 pos);
	bool IsSphereCollision(Vector2 pos);

	bool IsWaterCollision2(Vector2 pos);
	bool IsFlaereCollision2(Vector2 pos);
	bool IsPlantsCollision2(Vector2 pos);
	bool IsSphereCollision2(Vector2 pos);

	bool IsWaterCollision3(Vector2 pos);
	bool IsFlaereCollision3(Vector2 pos);
	bool IsPlantsCollision3(Vector2 pos);
	bool IsSphereCollision3(Vector2 pos);
};

