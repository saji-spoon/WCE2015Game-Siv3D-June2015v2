#include"MyResource.hpp"

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
	TextureAsset::Register(L"enemy1", EnemyRegister + L"shimi_enemy_01.png");
	TextureAsset::Register(L"enemy2", EnemyRegister + L"shimi_enemy_02.png");
	TextureAsset::Register(L"enemy3", EnemyRegister + L"shimi_enemy_03.png");

	/*
	ImageAsset::inst()->assetRegister(L"ballet1", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet2", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet3", L"ballet.png");
	*/

	FontAsset::Register(L"Debug", 12, Typeface::Default);

	AnimeAsset::I()->Register(L"blueFly", MyAnime(L"enemy1", 6, 2));
	AnimeAsset::I()->Register(L"green-mushi", MyAnime(L"enemy2", 13, 2));
	AnimeAsset::I()->Register(L"mossEye", MyAnime(L"enemy3", 8, 4));
}