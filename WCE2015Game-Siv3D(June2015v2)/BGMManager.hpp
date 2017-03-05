#pragma once
#include<Siv3D.hpp>
#include"SimpleState.hpp"

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
		if (m_state.m_state == 1) return;

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

	void update()
	{
		switch (m_state.m_state)
		{
		case 0:
			break;
		case 1:
			if (m_state.isFinished())
			{
				m_bgmTag = m_nextBGMTag;
				SoundAsset(m_bgmTag).play(1500);
				m_state.reset(50);
			}
			break;
		default:
			break;
		}

		m_state.update();
	}

	void changeBGMAtBoss(const String& tag)
	{
		if (!SoundAsset::IsRegistered(tag))
		{
			LOG_ERROR(L"BGMManager:アセットがありません:" + tag);
			return;
		}

		if (!m_bgmTag.isEmpty)
		{
			SoundAsset(m_bgmTag).stop(1500);
			m_nextBGMTag = tag;
			m_state.nextState(120);
		}
	}

	void stopBGM(double fade = 3000)
	{
		SoundAsset(m_bgmTag).stop(fade);
	}

private:

	SimpleState m_state;

	String m_nextBGMTag = L"";

	String m_bgmTag = L"";

	BGMManager()
	{
	}
};