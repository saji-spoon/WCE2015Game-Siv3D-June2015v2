#include"MyResource.hpp"

void shimi::ResourceRegister()
{
	const FilePath ResourcePath = L"Resource/";
	const FilePath HeroPath = L"Hero/";

	const FilePath HeroRegister = ResourcePath + HeroPath;
	TextureAsset::Register(L"Hero", HeroRegister + L"Stein.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"HeroX", HeroRegister + L"SteinX.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"HeroXX", HeroRegister + L"SteinXX.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"HeroXXX", HeroRegister + L"SteinXXX.png", {}, AssetFlag::Default);


	TextureAsset::Register(L"ballet1", HeroRegister + L"Ballet/RedBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"redBallet", HeroRegister + L"Ballet/RedBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"blueBallet", HeroRegister + L"Ballet/BlueBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"orangeBallet", HeroRegister + L"Ballet/OrangeBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"purpleBallet", HeroRegister + L"Ballet/PurpleBallet.png", {}, AssetFlag::Default);
	TextureAsset::Register(L"whiteBallet", HeroRegister + L"Ballet/WhiteBallet.png", {}, AssetFlag::Default);

	TextureAsset::Register(L"enemyBallet1", L"Resource/Enemy/Ballet/enemyBallet1.png", {}, AssetFlag::Default);

	TextureAsset::Register(L"re", L"ballet.png", {}, AssetFlag::Default);

	SoundAsset::Register(L"NormalStage", ResourcePath + L"BGM/" + L"Stage.wav");
	SoundAsset(L"NormalStage").setLoop(true);
	SoundAsset(L"NormalStage").setVolume(0.8);
	SoundAsset::Register(L"BossBattle", ResourcePath + L"BGM/" + L"Boss.wav");
	SoundAsset(L"BossBattle").setLoop(true);
	SoundAsset(L"BossBattle").setVolume(0.7);
	SoundAsset::Register(L"LastBossBGM", ResourcePath + L"BGM/" + L"Boss_Battle.mp3");
	SoundAsset(L"LastBossBGM").setLoop(true);
	SoundAsset(L"LastBossBGM").setLoop(true);
	/***SE‚Ì“o˜^***/
	SoundAsset::Register(L"MyBallet", ResourcePath + L"SE/" + L"01_kami4.wav");
	SoundAsset::Register(L"EnemyVanish", ResourcePath + L"SE/" +  L"button03b.mp3");
	SoundAsset::Register(L"Select", ResourcePath + L"SE/" + L"button40.mp3");
	SoundAsset::Register(L"Start", ResourcePath + L"SE/" + L"decision4.mp3");
	SoundAsset::Register(L"Charge", ResourcePath + L"SE/" + L"02_charge.wav");
	SoundAsset::Register(L"Lazer", ResourcePath + L"SE/" + L"02_laser.wav");
	SoundAsset::Register(L"EnemyBallet", ResourcePath + L"SE/" + L"01_kami4.wav");
	SoundAsset(L"EnemyBallet").setVolume(0.01);
	SoundAsset::Register(L"Damage", ResourcePath + L"SE/" + L"01_kami1.wav");
	SoundAsset::Register(L"BreakObstacle", ResourcePath + L"SE/" + L"06_wall_break1.wav");
	SoundAsset::Register(L"BossDamage", ResourcePath + L"SE/" + L"07_boss_damage2.wav");
	SoundAsset::Register(L"BossNoDamage", ResourcePath + L"SE/" + L"01_kami3.wav");
	SoundAsset::Register(L"BossVanish", ResourcePath + L"SE/" + L"09_boss_vanish1.wav");
	SoundAsset(L"BossVanish").setVolume(0.1);
	SoundAsset::Register(L"ItemGet", ResourcePath + L"SE/" + L"10_item_get.wav");
	SoundAsset::Register(L"GameOver", ResourcePath + L"SE/" + L"12_gameOver.wav");
	SoundAsset::Register(L"FlyBoss", ResourcePath + L"SE/" + L"13_fly.wav");
	SoundAsset::Register(L"SakanaBoss", ResourcePath + L"SE/" + L"15_ani_ge_kujira01.wav");
	SoundAsset::Register(L"LastBoss", ResourcePath + L"SE/" + L"16_boar-child-cry1.wav");
	SoundAsset::Register(L"Warp", ResourcePath + L"SE/" + L"13_ta_ta_maho13.wav");
	SoundAsset::Register(L"Recover", ResourcePath + L"SE/" + L"warp_5.mp3");
	
	SoundAsset::Register(L"Boss1Voice1", ResourcePath + L"SE/" + L"mushi.wav");

	FontManager::Register(L"Resource/Font/UtsukushiMincho-FONT/UtsukushiFONT.otf");

	FontAsset::Register(L"Debug", 12, Typeface::Default);
	FontAsset::Register(L"Notify1", 20, Typeface::Default);
	FontAsset::Register(L"Notify2", 16, L"02‚¤‚Â‚­‚µ–¾’©‘Ì");
	FontAsset::Register(L"Notify2Out", 16, L"02‚¤‚Â‚­‚µ–¾’©‘Ì", FontStyle::Outline);
	FontAsset::Register(L"Ending", 24, L"02‚¤‚Â‚­‚µ–¾’©‘Ì");

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
	TextureAsset::Register(L"bloodEye", EnemyRegister + L"shimi_enemy_14.png");
	TextureAsset::Register(L"nightSun", EnemyRegister + L"shimi_enemy_15.png");
	TextureAsset::Register(L"flightBee", EnemyRegister + L"shimi_enemy_90.png");

	TextureAsset::Register(L"boss2Baby", EnemyRegister + L"baby_1.png");
	

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
	AnimeAsset::I()->Register(L"sunsetTentou", MyAnime(L"sunsetTentou", 8, 3));
	AnimeAsset::I()->Register(L"shadowCircle", MyAnime(L"shadowCircle", 11, 2));
	AnimeAsset::I()->Register(L"darkAmeba", MyAnime(L"darkAmeba", 8, 5));
	AnimeAsset::I()->Register(L"flightBee", MyAnime(L"flightBee", 6, 4));
	AnimeAsset::I()->Register(L"bloodEye", MyAnime(L"bloodEye", 8, 12));
	AnimeAsset::I()->Register(L"nightSun", MyAnime(L"nightSun", 4, 20));

	AnimeAsset::I()->Register(L"boss2Baby", MyAnime(L"boss2Baby", 2, 2));

}