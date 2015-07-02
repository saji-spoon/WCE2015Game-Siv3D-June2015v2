#pragma once
#include<Siv3D.hpp>

namespace shimi
{

//for Debug
struct taggedImage
{
	taggedImage(){}

	taggedImage(const String& t, const FilePath& path) :image(new Image(path)), tag(t)
	{}

	std::shared_ptr<Image> image;

	String tag;
};

class ImageAsset
{
public:
	std::vector <taggedImage> images;

	taggedImage errorImage;

private:
	ImageAsset() :errorImage(L"Error", L"Resource/Error.png")
	{}

public:
	ImageAsset(const ImageAsset& ia) = delete;
	ImageAsset& operator=(const ImageAsset& ia) = delete;

	static ImageAsset* inst()
	{
		static ImageAsset ia;
		return &ia;
	}

	bool assetRegister(const String& tag, const FilePath& path)
	{
		const bool exists = FileSystem::Exists(path);

		if (!exists)
		{
			LOG_ERROR(L"ImageAsset:No Such File:", path);
			return exists;
		}

		images.emplace_back(tag, path);

		return exists;
	}

	const Image& access(const String& tag)
	{
		const std::vector<taggedImage>::iterator it = std::find_if(images.begin(), images.end(), [&](const taggedImage& target){return target.tag == tag; });

		if (it != images.end())
		{
			return *((*it).image);
		}
		else
		{
			return *errorImage.image;
		}
	}

};

}