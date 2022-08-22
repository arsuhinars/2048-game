#pragma once
#include <memory>
#include <vector>
#include "tile.h"
#include "config.h"

namespace arsuhinars
{
	// Структура состояния игры
	struct GameState
	{
		// Размеры окна
		unsigned int windowWidth = DEFAULT_WINDOW_WIDTH;
		unsigned int windowHeight = DEFAULT_WINDOW_HEIGHT;

		// Размер поля игры
		unsigned int fieldSize = DEFAULT_FIELD_SIZE;

		// Список всех плиток на поле, где ключ - позиция плитки
		std::vector<std::unique_ptr<Tile>> tilemap;

		// Проиграл ли игрок
		bool isGameLost = false;

		// Счет игрока
		unsigned int score = 0;
		
		// Рекорд игрока
		unsigned int record = 0;

		// Метод сохранения состояния
		void save();
		// Метод загрузки состояния из файла
		void load();
	};
}
