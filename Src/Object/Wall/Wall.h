#pragma once
class Wall
{
public:
	//植物壁サイズ
	static constexpr int PLANTS_SIZE_X = 96;
	static constexpr int PLANTS_SIZE_Y = 96*3;
	static constexpr int PLANTS_HALF_SIZE_X = PLANTS_SIZE_X / 2;
	static constexpr int PLANTS_HALF_SIZE_Y = PLANTS_SIZE_Y / 2;

	//フレア壁サイズ
	static constexpr int FLARE_SIZE_X = 96;
	static constexpr int FLARE_SIZE_Y = 96*3;
	static constexpr int FLARE_HALF_SIZE_X = FLARE_SIZE_X / 2;
	static constexpr int FLARE_HALF_SIZE_Y = FLARE_SIZE_Y / 2;

	//水壁サイズ
	static constexpr int WATER_SIZE_X = 96;
	static constexpr int WATER_SIZE_Y = 96 * 5;
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

	//画像の数
	int flareNo_;
	int waterNo_;

	//座標
	Vector2F plantsPos_;
	Vector2F flarePos_;
	Vector2F waterPos_;

	//生存フラグ
	bool isPlantsAlive_;
	bool isFlareAlive_;
	bool isWaterAlive_;

	//アニメーションカウント
	int flareAnimCount_;
	int waterAnimCount_;



public:
	Wall();
	~Wall();
	void Init();
	void Update();
	void Draw();

	void AnimUpdate();




	Vector2F GetPlantsPos() const;
	Vector2F GetFlarePos() const;
	Vector2F GetWaterPos() const;
	bool IsPlantsAlive() const;
	bool IsFlareAlive() const;
	bool IsWaterAlive() const;
	void SetPlantsPos(const Vector2F& pos);
	void SetFlarePos(const Vector2F& pos);
	void SetWaterPos(const Vector2F& pos);

};

