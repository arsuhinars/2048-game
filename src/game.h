#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "theme.h"
#include "game_state.h"

namespace arsuhinars
{
	namespace game
	{
		// ������ �� ���� ����
		extern std::unique_ptr<sf::RenderWindow> window;

		// ����������� �����
		extern std::unique_ptr<sf::Font> font;

		// ������� ���� ����
		extern Theme theme;

		// �������, � ������� ��������� ������� ����
		extern sf::IntRect fieldRect;

		// ������� ��������� ����
		extern GameState state;

		// ����� ������� ����. ������� ������� ����
		void run();

		// ����� ������ �������� ��������� ����
		void reset();

		// ����� ���������� ����
		void update();

		// ����� ��������� ����
		void render();

		// ����� ��������� ������� ������
		void handleInput(sf::Event::KeyEvent& ev);

		// �������� �����, ��������� � ���������� �����, � ��������
		float getTimeDelta();
	}
}
