#pragma once
#include<Siv3D.hpp>
#include"AscAnime.hpp"

namespace shimi
{
	using namespace asc;

//for Debug
struct taggedAnime
{
	taggedAnime(){}

	taggedAnime(const String& t, const FilePath& path) :m_anime(), tag(t)
	{}

	std::shared_ptr<Anime> m_anime;

	String tag;
};

class AnimeAsset
{
public:
	std::unordered_map<String, Anime> m_animes;

	taggedAnime errorAnime;

private:
	AnimeAsset() :errorAnime(L"Error", L"Resource/Error.png")
	{}

public:
	AnimeAsset(const AnimeAsset& ia) = delete;
	AnimeAsset& operator=(const AnimeAsset& ia) = delete;

	static AnimeAsset* I()
	{
		static AnimeAsset ia;
		return &ia;
	}

	bool assetRegister(const String& tag, const Anime& anime)
	{
		m_animes[tag] = anime;

		return exists;
	}

	const Anime& access(const String& tag)
	{
		const std::vector<taggedAnime>::iterator it = std::find_if(Animes.begin(), Animes.end(), [&](const taggedAnime& target){return target.tag == tag; });

		if (it != Animes.end())
		{
			return *((*it).Anime);
		}
		else
		{
			return *errorAnime.Anime;
		}
	}

};

}