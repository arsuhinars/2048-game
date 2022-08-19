#pragma once
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	class Tile
	{
	public:
		// Типы анимаций у тайла
		enum Animation {
			None, Appear, ChangeValue
		};

		Tile(sf::Vector2f position, unsigned int value=0);

		// Был ли уже тайл просуммирован с другим
		bool wasAlreadySummed = false;
		
		// Вычислить относительный размер тайла
		static float calcRelativeTileSize();
		// Метод вычисления размера одного тайла
		static unsigned int calcTileSize();
		// Метод для вычисления позиции тайла на экране
		static sf::Vector2f calcTileScreenPos(sf::Vector2f position);

		// Метод отрисовки плитки
		void render();

		// Метод для изменения позиции плитки
		// Координата должна находится в пределе от 0 до n - 1, где n - размер поля
		void setPosition(sf::Vector2f position);
		// Метод для получения позиции плитки
		sf::Vector2f getPosition();

		// Метод изменения значения у тайла
		// Значение - это степень двойки
		void setValue(unsigned int value);
		// Метод для получения значения тайла
		unsigned int getValue();

		// Перемещается ли плитка в данный момент
		bool isMoving();
		// Переместить плитку плавно в другую позицию
		void moveTo(sf::Vector2f position);

		// Проиграть анимацию
		void playAnimation(Animation animation);

	private:
		sf::Text text;
		sf::ConvexShape shape;

		sf::Vector2f position;
		unsigned int value = 0;

		float moveFactor;
		float moveDelta;
		bool m_isMoving = false;
		sf::Vector2f targetPosition;

		Animation currAnim;
		float animFactor;
		float animDelta;

		float scaleFactor = 1.0f;

		void updateColors();
		void updateTextPosition();
		void updateTextScale();
	};
}
