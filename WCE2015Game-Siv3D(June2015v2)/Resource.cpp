#include"Resource.hpp"
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

	ImageAsset::inst()->assetRegister(L"ballet1", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet2", L"ballet.png");
	ImageAsset::inst()->assetRegister(L"ballet3", L"ballet.png");
}