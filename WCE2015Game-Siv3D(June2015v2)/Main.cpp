# include <Siv3D.hpp>
#include<HamFramework.hpp>
#include<algorithm>
#include"MyResource.hpp"
#include"GameBase.hpp"
#include"Title.hpp"

using namespace shimi;
struct GameData
{
	Title ti;
	GameBase gb;
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

		if (m_data->ti.getSelect() == TitleSelect::NewGame)
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
	}

	void update() override
	{
		m_data->gb.update();
	}

	void draw() const override
	{
		m_data->gb.draw();
	}
};

void Main()
{
	ResourceRegister();

	MyApp manager;

	manager.add<TitleScene>(L"TitleScene");
	manager.add<GameScene>(L"GameScene");

	manager.changeScene(L"TitleScene", 0, false);

	Window::Resize(1280, 800);

	manager.setFadeColor(Palette::Black);

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		if (!manager.updateAndDraw())
			break;
	}
}