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
	TextureAsset::Register(L"blueDia", EnemyRegister + L"shimi_enemy_01.png");
	TextureAsset::Register(L"greenMushi", EnemyRegister + L"shimi_enemy_02.png");
	TextureAsset::Register(L"mossEye", EnemyRegister + L"shimi_enemy_03.png");
	TextureAsset::Register(L"blueLotus", EnemyRegister + L"shimi_enemy_04.png");
	TextureAsset::Register(L"purpleCutter", EnemyRegister + L"shimi_enemy_05.png");
	TextureAsset::Register(L"orangeCircle", EnemyRegister + L"shimi_enemy_06.png");
	TextureAsset::Register(L"redDia", EnemyRegister + L"shimi_enemy_07.png");
	TextureAsset::Register(L"sunFlower", EnemyRegister + L"shimi_enemy_08.png");
	TextureAsset::Register(L"heartFish", EnemyRegister + L"shimi_enemy_09.png");
	TextureAsset::Register(L"ikachan", EnemyRegister + L"shimi_enemy_10.png");
	TextureAsset::Register(L"sunsetTentou", EnemyRegister + L"shimi_enemy_11.png");
	TextureAsset::Register(L"shadowCircle", EnemyRegister + L"shimi_enemy_12.png");
	TextureAsset::Register(L"darkAmeba", EnemyRegister + L"shimi_enemy_13.png");
	TextureAsset::Register(L"flightBee", EnemyRegister + L"shimi_enemy_90.png");
	/*
	ImageAsset::inst()->assetRegister(L"ballet1", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet2", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet3", L"ballet.png");
	*/

	SoundAsset::Register(L"NormalStage", ResourcePath + L"BGM/" + L"Wake_Myself.mp3");
	SoundAsset(L"NormalStage").setLoop(true);
	SoundAsset::Register(L"BossBattle", ResourcePath + L"BGM/" + L"Boss_Battle.mp3");
	SoundAsset(L"BossBattle").setLoop(true);


	/***SE‚Ì“o˜^***/
	SoundAsset::Register(L"MyBallet", ResourcePath + L"SE/" + L"tissue.mp3");
	SoundAsset::Register(L"EnemyVanish", ResourcePath + L"SE/" + L"button03b.mp3");
	SoundAsset::Register(L"Select", ResourcePath + L"SE/" + L"button40.mp3");
	SoundAsset::Register(L"Start", ResourcePath + L"SE/" + L"decision4.mp3");

	SoundAsset::Register(L"Boss1Voice1", ResourcePath + L"SE/" + L"mushi.wav");

	FontAsset::Register(L"Debug", 12, Typeface::Default);

	AnimeAsset::I()->Register(L"blueDia", MyAnime(L"blueDia", 6, 2));
	AnimeAsset::I()->Register(L"greenMushi", MyAnime(L"greenMushi", 13, 7));
	AnimeAsset::I()->Register(L"mossEye", MyAnime(L"mossEye", 8, 12));
	AnimeAsset::I()->Register(L"blueLotus", MyAnime(L"blueLotus", 8, 5));
	AnimeAsset::I()->Register(L"purpleCutter", MyAnime(L"purpleCutter", 16, 22));
	AnimeAsset::I()->Register(L"orangeCircle", MyAnime(L"orangeCircle", 4, 20));
	AnimeAsset::I()->Register(L"redDia", MyAnime(L"redDia", 12, 4));
	AnimeAsset::I()->Register(L"sunFlower", MyAnime(L"sunFlower", 8, 4));
	AnimeAsset::I()->Register(L"heartFish", MyAnime(L"heartFish", 8, 6));
	AnimeAsset::I()->Register(L"ikachan", MyAnime(L"ikachan", 6, 4));
	AnimeAsset::I()->Register(L"sunsetTentou", MyAnime(L"sunsetTentou", 8, 7));
	AnimeAsset::I()->Register(L"shadowCircle", MyAnime(L"shadowCircle", 11, 2));
	AnimeAsset::I()->Register(L"darkAmeba", MyAnime(L"darkAmeba", 8, 5));
	AnimeAsset::I()->Register(L"flightBee", MyAnime(L"flightBee", 6, 4));

}