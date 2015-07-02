#include"Resource.hpp"

void ResourceRegister()
{
	const FilePath ResourcePath = L"Resource/";
	const FilePath HeroPath = L"Hero/";

	const FilePath HeroRegister = ResourcePath + HeroPath;

	TextureAsset::Register(L"Hero", HeroRegister + L"Stein.png", {}, AssetFlag::Default);

}