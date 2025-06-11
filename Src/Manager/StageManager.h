#pragma once
class StageManager
{
public:
	enum class STAGE_TYPE
	{
		NONE,
		STAGE1,
		STAGE2,
		STAGE3,

	};


private:


	STAGE_TYPE stageType;

public:

	StageManager();
	~StageManager();
	void Init();
	void Update();
	void Draw();

	void ChangeStage(STAGE_TYPE id);


};

