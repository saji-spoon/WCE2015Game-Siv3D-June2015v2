#pragma once
#include<Siv3D.hpp>

class BGMManager{
public:

	static BGMManager* I()
	{
		static BGMManager instance;
		return &instance;
	}

	BGMManager(const BGMManager& rhs) = delete;

	BGMManager& operator=(const BGMManager& rhs) = delete;

	void changeBGM(const String& tag, double fade = 1500)
	{
		if (!SoundAsset::IsRegistered(tag))
		{
			LOG_ERROR(L"BGMManager:アセットがありません:" + tag);
			return;
		}

		if (tag == m_bgmTag) return;


		if (!m_bgmTag.isEmpty)
		{
			SoundAsset(m_bgmTag).stop(fade);
			m_bgmTag = tag;
			SoundAsset(m_bgmTag).play(fade);
		}
		else
		{
			m_bgmTag = tag;
			SoundAsset(m_bgmTag).play();
		}

	}

	void stopBGM(double fade = 3000)
	{
		SoundAsset(m_bgmTag).stop(fade);
	}

private:

	String m_bgmTag = L"";

	BGMManager()
	{
	}
};