# include <Siv3D.hpp>
#include<HamFramework.hpp>
#include<algorithm>
#include"MyResource.hpp"
#include"GameBase.hpp"
#include"Title.hpp"
#include"GamePadCheck.hpp"
#include"Config.hpp"
#include"Ending.hpp"
#include"Save.hpp"

using namespace shimi;
struct GameData
{
	Title ti;
	GameBase gb;
	Ending ed;
};

using MyApp = SceneManager<String, GameData>;

struct TitleScene : MyApp::Scene
{
	void init() override
	{

	}

	void update() override
	{
		m_data->ti.update();

		if (m_data->ti.getSelect() == TitleSelect::NewGame ||
			m_data->ti.getSelect() == TitleSelect::Continue)
		{
			changeScene(L"GameScene", 3000);
		}
	}

	void draw() const override
	{
		m_data->ti.draw();
	}
};

struct GameScene : MyApp::Scene
{
	void init()override
	{
		m_data->gb.init();
		m_data->gb.update();

		if (m_data->ti.getSelect() == TitleSelect::Continue)
		{
			Save::I()->load(m_data->gb);
			m_data->gb.update();
		}

	}

	void update() override
	{
		m_data->gb.update();

		if (m_data->gb.m_isCleared)
		{
			changeScene(L"EndingScene", 3000);
		}
	}

	void draw() const override
	{
		m_data->gb.draw();
	}
};


struct EndingScene : MyApp::Scene
{
	void init()override
	{
		m_data->ed = Ending(m_data->gb.m_obstacles);
	}

	void update() override
	{
		m_data->ed.update();
	}

	void draw() const override
	{
		m_data->ed.draw();
	}
};

#undef _DEBUG

void Main()
{
	ResourceRegister();

	MyApp manager;

	manager.add<TitleScene>(L"TitleScene");
	manager.add<GameScene>(L"GameScene");
	manager.add<EndingScene>(L"EndingScene");

#ifdef _DEBUG
	manager.init(L"GameScene");
#else
	manager.init(L"TitleScene");
#endif
	Window::Resize(1280, 800);

	manager.setFadeColor(Palette::Black);

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		manager.draw();

		if (!manager.update())
			break;

		GamepadCheck::I()->update();
	}
}