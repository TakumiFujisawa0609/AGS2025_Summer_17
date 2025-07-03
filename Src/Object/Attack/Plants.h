#pragma once

#include"../../Common/Vector2.h"
class Camera;

class Plants
{

	
	
	public:
		//定数
		// 爆発のアニメーションのフレーム数
		static constexpr int PLANTS_ANIM_FRAME = 9;
		// 爆発分割サイズ
		static constexpr int PLANTS_SIZE = 64;
		// 横切り取り枚数
		static constexpr int PLANTS_DIV_X = PLANTS_ANIM_FRAME;
		
		

	private:
		//変数
		// 爆発画像のロード
		int plantsImgs[9];

		// 爆発判定(trueが爆発)
		bool isPlants;
		// 爆発アニメーション用のカウンタ
		int plantsImgAnimCount;

		float count;
		// 爆発座標
		Vector2 plantsPos;

		Camera* camera_;
	public:
		Plants(void);
		~Plants(void);
		void Init(Camera* camera);
		void Update(void);
		void Draw(void);
		void Release(void);
		bool GetIsPlants(void);
		void SetIsPlants(bool is);
		Vector2 GetPlantsPos(void);
		void SetPlantsPos(Vector2 pos);

	
};

