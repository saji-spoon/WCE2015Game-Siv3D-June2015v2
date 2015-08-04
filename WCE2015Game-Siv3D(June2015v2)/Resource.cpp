#include"MyResource.hpp"
#include"ImageAsset.hpp"

using namespace shimi;

void shimi::ResourceRegister()
{
	const FilePath ResourcePath = L"Resource/";
	const FilePath HeroPath = L"Hero/";

	const FilePath HeroRegister = ResourcePath + HeroPath;
	TextureAsset::Register(L"Hero", HeroRegister + L"Stein.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"ballet1", L"ballet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"ballet2", L"ballet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"ballet3", L"ballet.png", {}, AssetFlag::Default);

	const FilePath EnemyRegister = ResourcePath + L"Enemy/";
	TextureAsset::Register(L"enemy1", EnemyRegister + L"enemy_01Test.png");
	TextureAsset::Register(L"enemy2", EnemyRegister + L"enemy_02Test.png");

	ImageAsset::inst()->assetRegister(L"ballet1", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet2", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet3", L"ballet.png");

	FontAsset::Register(L"Debug", 12, Typeface::Default);
}