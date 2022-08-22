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
		extern sf::FloatRect fieldRect;

		// Область, в которой находится верхняя панель
		extern sf::FloatRect topBarRect;

		// Текущее состояние игры
		extern GameState state;

		// Текущая позиция курсора в оконном пространстве
		extern sf::Vector2f mousePos;

		// Метод запуска игры. Создает главный цикл
		void run();

		// Метод сброса текущего прогресса игры
		void reset();

		// Функция обработки проигрыша игры
		void lose();

		// Метод обновления игры
		void update();

		// Метод отрисовки игры
		void render();

		// Метод обработки нажатия клавиш
		void handleInput(sf::Event::KeyEvent& ev);

		// Функция-обработчик изменения размера окна
		void handleResize();

		// Получить время, прошедшее с последнего кадра, в секундах
		float getTimeDelta();
	}
}
