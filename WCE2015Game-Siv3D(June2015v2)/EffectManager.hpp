#pragma once
#include<Siv3D.hpp>

class EffectManager{
public:

	static EffectManager* I()
	{
		static EffectManager instance;
		return &instance;
	}

	EffectManager(const EffectManager& rhs) = delete;

	EffectManager& operator=(const EffectManager& rhs) = delete;

	Effect effect;

private:

	EffectManager()
	{
	}
};