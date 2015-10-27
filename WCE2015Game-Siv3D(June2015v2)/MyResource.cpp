#include"MyResource.hpp"

void shimi::ResourceRegister()
{
	const FilePath ResourcePath = L"Resource/";
	const FilePath HeroPath = L"Hero/";

	const FilePath HeroRegister = ResourcePath + HeroPath;
	TextureAsset::Register(L"Hero", HeroRegister + L"Stein.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"ballet1", HeroRegister + L"Ballet/RedBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"redBallet", HeroRegister + L"Ballet/RedBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"blueBallet", HeroRegister + L"Ballet/BlueBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"orangeBallet", HeroRegister + L"Ballet/OrangeBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"purpleBallet", HeroRegister + L"Ballet/PurpleBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"whiteBallet", HeroRegister + L"Ballet/WhiteBallet.png", {}, AssetFlag::Default);

	TextureAsset::Register(L"enemyBallet1", L"Resource/Enemy/Ballet/enemyBallet1.png", {}, AssetFlag::Default);

	TextureAsset::Register(L"re", L"ballet.png", {}, AssetFlag::Default);

	const FilePath EnemyRegister = ResourcePath + L"Enemy/";
	TextureAsset::Register(L"enemy1", EnemyRegister + L"shimi_enemy_01.png");
	TextureAsset::Register(L"enemy2", EnemyRegister + L"shimi_enemy_02.png");
	TextureAsset::Register(L"enemy3", EnemyRegister + L"shimi_enemy_03.png");
	TextureAsset::Register(L"redDia", EnemyRegister + L"shimi_enemy_07.png");
	/*
	ImageAsset::inst()->assetRegister(L"ballet1", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet2", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet3", L"ballet.png");
	*/

	SoundAsset::Register(L"NormalStage", ResourcePath + L"BGM/" + L"Wake_Myself.mp3");
	SoundAsset(L"NormalStage").setLoop(true);
	SoundAsset::Register(L"BossBattle", ResourcePath + L"BGM/" + L"Boss_Battle.mp3");
	SoundAsset(L"BossBattle").setLoop(true);


	SoundAsset::Register(L"MyBallet", ResourcePath + L"SE/" + L"tissue.mp3");
	SoundAsset::Register(L"EnemyVanish", ResourcePath + L"SE/" + L"button05.mp3");
	SoundAsset::Register(L"Select", ResourcePath + L"SE/" + L"sel8.mp3");

	SoundAsset::Register(L"Boss1Voice1", ResourcePath + L"SE/" + L"mushi.wav");

	FontAsset::Register(L"Debug", 12, Typeface::Default);

	AnimeAsset::I()->Register(L"blueFly", MyAnime(L"enemy1", 6, 2));
	AnimeAsset::I()->Register(L"green-mushi", MyAnime(L"enemy2", 13, 2));
	AnimeAsset::I()->Register(L"mossEye", MyAnime(L"enemy3", 8, 4));
	AnimeAsset::I()->Register(L"redDia", MyAnime(L"redDia", 12, 5));

}