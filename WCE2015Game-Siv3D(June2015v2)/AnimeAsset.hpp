#pragma once
#include<Siv3D.hpp>
#include"MyAnime.hpp"

namespace shimi
{
class AnimeAsset
{
typedef std::pair<String, MyAnime> sa;

public:
	std::unordered_map<String, MyAnime> m_animes;

	MyAnime errorAnime;

private:
	AnimeAsset() :errorAnime(MyAnime(L"Error", 1, 60))
	{}

public:
	AnimeAsset(const AnimeAsset& ia) = delete;
	AnimeAsset& operator=(const AnimeAsset& ia) = delete;

	static AnimeAsset* I()
	{
		static AnimeAsset ia;
		return &ia;
	}

	
	bool Register(const String& tag, const MyAnime& anime)
	{
		auto res = m_animes.insert(sa{ tag, anime });

#ifdef _DEBUG
		LOG_DEBUG(L"AnimeAsset Register:", tag, L" - ", (res.second ? L"Success" : L"Failed" ));
#endif
		return res.second;
	}	

	const MyAnime& Asset(const String& tag)
	{
		const auto it = m_animes.find(tag);

		if (it != m_animes.end())
		{
			return (*it).second;
		}
		else
		{
			LOG_ERROR(L"There's no anime:",tag);

			return errorAnime;
		}
	}

};

}