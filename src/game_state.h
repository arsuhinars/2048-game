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
		// Размер поля игры
		unsigned int fieldSize = DEFAULT_FIELD_SIZE;

		// Список всех плиток на поле, где ключ - позиция плитки
		std::vector<std::unique_ptr<Tile>> tilemap;

		// Метод сохранения состояния
		void save();
		// Метод загрузки состояния из файла
		void load();
	};
}
