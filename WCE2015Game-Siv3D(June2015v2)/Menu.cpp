#include"Menu.hpp"
#include"GameBase.hpp"
#include"Camera.hpp"
#include"Config.hpp"

using namespace shimi;

Menu::Menu(GameBase* gb, const MyVehicle& mvData) :m_gb(gb), m_mvData(mvData)
{
	m_mvData.m_pos = D2Camera::I()->getGlobalPos(Vec2(520, 307));
	m_mvData.m_v = Vec2(0, -1);

	m_mvData.changeState(std::shared_ptr<shimi::state::myvehicle::MVState>( new shimi::state::myvehicle::Normal()));
	
	for (auto& tempShot : m_mvData.m_shotManager.m_equipShot)
	{
		//���V���b�g�ł͂Ȃ�����������Ă���Ƃ��A���j���[���J���ۂɃC���X�^���X��蒼���i�΂̃`���[�W�Ȃǂ������j
		if (tempShot && tempShot.value()->m_color)
		{
			const ShimiColors targetColor = tempShot.value()->m_color.value();
			const int level = m_mvData.m_shotManager.getLevel(targetColor);
			tempShot = m_mvData.m_shotManager.ShimiColorsToShot(targetColor, level);
		}
	}

	m_mvData.shotList.clear();
	

}

void Menu::update()
{
	//S�L�[���������甲����
	if ((Input::KeyS | Gamepad(0).button(11)).clicked)
	{
		m_gb->changeState(std::shared_ptr<state::GBState>(new state::MainGame()));
	}

	//���̑I���͏㉺�L�[
	const int selectAdd = ConfigParam::KEY_UP_CLICKED() ? -1 : (ConfigParam::KEY_DOWN_CLICKED() ? 1 : 0);

	//�F�̑I���͍��E�L�[
	const int colorAdd = ConfigParam::KEY_RIGHT_CLICKED() ? 1 : (ConfigParam::KEY_LEFT_CLICKED() ? -1 : 0);

	if (selectAdd != 0 || colorAdd != 0) SoundAsset(L"Select").playMulti();

	//�����\���ɑ���Ȃ����͑I���ł��Ȃ�
	if(selectAdd != 0) m_select = (m_select + m_mvData.m_shotManager.m_equipNum + selectAdd) % m_mvData.m_shotManager.m_equipNum;

	if (colorAdd == 0) return;

	//�I�𒆂̑����ɂ���
	const auto& tempShot = m_mvData.m_shotManager.m_equipShot[m_select];

	ShimiColors nextCol;

	//��������A���邢�͔��i�����j�V���b�g�̏ꍇ
	if (!tempShot || !tempShot.value()->m_color)
	{
		nextCol = ShimiColors::Red;
		
	}
	else //�Ȃɂ����łɑ������Ă���ꍇ
	{
		nextCol = (colorAdd == 1) ? NextColor(tempShot.value()->m_color.value()) : PreviousColor(tempShot.value()->m_color.value());
	}

	for (int i = 0; i < static_cast<int>(ShimiColors::ColorNum)+1; ++i)
	{
		//level��1�ȏ�i���g�p�\�j�Ȃ�Z�b�g����
		if ((m_mvData.m_shotManager.getLevel(nextCol) >= 1) && !m_mvData.m_shotManager.isAlreadyEquiped(nextCol))
		{
			m_mvData.m_shotManager.m_equipShot[m_select] = m_mvData.m_shotManager.ShimiColorsToShot(nextCol, m_mvData.m_shotManager.getLevel(nextCol));
			break;
		}

		//�g�p�\�łȂ��Ȃ玟�́i�O�́j�F��T��
		nextCol = (colorAdd == 1) ? NextColor(nextCol) : PreviousColor(nextCol);
	}


}

extern Color defaultFrameColor;
extern Color lightenColor;
extern Color darkenColor;

void Menu::draw()const
{
	Rect(Window::Size()).draw(Color(0, 0, 0, 230));

	m_mvData.draw();
	m_mvData.drawShotEquipAsPreview();


	//�I��UI�`��
	for (int i = 0; i < 3; ++i)
	{
		const Circle cir = Circle(Vec2(874, 240) + Vec2(0, 125) * i, 50);
		cir.drawFrame(15.0, 0.0, defaultFrameColor);

		const Vec2 cursorLTop = Vec2(783, 240) + Vec2(0, 125) * i;

		const Triangle cursorL = Triangle(cursorLTop, cursorLTop + Vec2( 22, -20 ), cursorLTop + Vec2( 22, 20 ));

		const Vec2 cursorRTop = Vec2(965, 240) + Vec2(0, 125) * i;

		const Triangle cursorR = Triangle(cursorRTop, cursorRTop + Vec2(-22, -20), cursorRTop + Vec2(-22, 20));

		cursorL.draw(defaultFrameColor);
		cursorR.draw(defaultFrameColor);

		//�I�����Ă��闓�͖��邭�Ȃ�
		if (i == m_select)
		{
			cir.drawFrame(15.0, 0.0, lightenColor);
			cursorL.draw(lightenColor);
			cursorR.draw(lightenColor);

		}

		//�����\�����傫�����͈Â��Ȃ�
		if (i >= m_mvData.m_shotManager.m_equipNum)
		{
			cir.drawFrame(15.0, 0.0, darkenColor);
			cursorL.draw(darkenColor);
			cursorR.draw(darkenColor);
		}
	}



	//�I��F�`��
	for (int i = 0; i < 3; ++i)
	{
		const Circle cir = Circle(Vec2(874, 240) + Vec2(0, 125) * i, 20);

		if (i >= m_mvData.m_shotManager.m_equipNum) break;

		if (const auto& shot = m_mvData.m_shotManager.m_equipShot[i])
		{
			if (const auto& color = shot.value()->m_color)
			{
				const Color shotColor = ToColor(shot.value()->m_color.value());

				cir.draw(shotColor);				
			}

			
		}
	}


}