#pragma once
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	namespace field
	{
		// Метод получения индекса тайла по его координате
		size_t getTileIndex(unsigned int x, unsigned int y);

		// Метод поиска позиции тайла по его индексу
		sf::Vector2u getTilePos(size_t index);

		// Метод инициализации поля
		void init();

		// Метод отрисовки поля игры
		void render();

		// Метод создания новой случайной плитки
		void spawnTile();

		// Функции перемещения всех тайлов в соотвествующую сторону
		void moveTilesUp();
		void moveTilesRight();
		void moveTilesDown();
		void moveTilesLeft();

		// Переместить тайл из одной позиции в другую
		// Возвращает истину, если тайл был успешно передвинут, иначе - ложь
		bool moveTile(sf::Vector2u from, sf::Vector2u to);

		// Двигается ли какой-нибудь тайл
		bool isAnyTileMoving();
	}
}
