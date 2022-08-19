#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "theme.h"
#include "game_state.h"

namespace arsuhinars
{
	namespace game
	{
		// Ссылка на окно игры
		extern std::unique_ptr<sf::RenderWindow> window;

		// Стандартный шрифт
		extern std::unique_ptr<sf::Font> font;

		// Текущая тема игры
		extern Theme theme;

		// Область, в которой находится игровое поле
		extern sf::IntRect fieldRect;

		// Текущее состояние игры
		extern GameState state;

		// Метод запуска игры. Создает главный цикл
		void run();

		// Метод сброса текущего прогресса игры
		void reset();

		// Метод обновления игры
		void update();

		// Метод отрисовки игры
		void render();

		// Метод обработки нажатия клавиш
		void handleInput(sf::Event::KeyEvent& ev);

		// Получить время, прошедшее с последнего кадра, в секундах
		float getTimeDelta();
	}
}
