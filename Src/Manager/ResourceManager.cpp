#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	std::unique_ptr<Resource> res;

	res= std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Player/Player1.png",6,2,64,64);
	resourcesMap_.emplace(SRC::PLAYERS, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Player/PlayerArm.png",4,1,64,64);
	resourcesMap_.emplace(SRC::PLAYERARM, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/Map3.png", 11, 1, 64, 64);
	resourcesMap_.emplace(SRC::MAPCHIP, std::move(res));

	res = std::make_unique<RES>(RES_T::IMG, PATH_IMG + "gimick/Pwall.png");
	resourcesMap_.emplace(SRC::PWALL, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "gimick/Fwall.png",3,1,64,64*3);
	resourcesMap_.emplace(SRC::FWALL, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "gimick/Wwall.png", 5, 1, 64, 64*3);
	resourcesMap_.emplace(SRC::WWALL, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "gimick/WSphere.png", 2, 1, 64, 64);
	resourcesMap_.emplace(SRC::WSPHERE, std::move(res));

	res = std::make_unique<RES>(RES_T::IMG, PATH_IMG + "Player/Ui.png");
	resourcesMap_.emplace(SRC::HPUI, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/NC.png", 3, 1, 320, 192);
	resourcesMap_.emplace(SRC::N, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/BC.png", 3, 1, 320, 192);
	resourcesMap_.emplace(SRC::B, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/GC.png", 3, 1, 320, 192);
	resourcesMap_.emplace(SRC::P, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/RC.png", 3, 1, 320, 192);
	resourcesMap_.emplace(SRC::F, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/MoveDC.png",8,1,320,192 );
	resourcesMap_.emplace(SRC::MOVE, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/MoveD+C.png", 8, 1, 320, 192);
	resourcesMap_.emplace(SRC::MOVES, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/KC.png", 8, 1, 320, 192);
	resourcesMap_.emplace(SRC::K, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/WBGR.png", 8, 1, 320, 192);
	resourcesMap_.emplace(SRC::NBPF, std::move(res));

	res = std::make_unique<RES>(RES_T::IMGS, PATH_IMG + "Stage/JANPC.png", 8, 1, 320, 192);
	resourcesMap_.emplace(SRC::JANP, std::move(res));

	

	//画像の読み込み
	//ブロック	
	//res = std::make_unique<RES>(RES_T::IMG, PATH_IMG + "LineBlock.png");
	//resourcesMap_.emplace(SRC::BLOCK, std::move(res));
	
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
