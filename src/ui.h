#pragma once

namespace arsuhinars
{
	namespace ui
	{
		// Функция иницилизации интерфейса
		void init();

		// Метод отрисовки интерфейса
		void render();

		// Функция обновления размеров элементов
		void updateSize();

		// Функция обновления текстов очков и рекорда
		void updateText();

		// Отобразить очки игрока
		void showScoresPopUp(unsigned int value);

		// Открыть меню проигрыша
		void showLoseMenu();
		// Спрятать меню проигрыша
		void hideLoseMenu();
	}
}
