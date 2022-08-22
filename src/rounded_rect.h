#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace arsuhinars
{
	// Класс прямоугольника с закругленными углами
	class RoundedRectShape : public sf::Shape
	{
	public:
		// Конструктор класса
		explicit RoundedRectShape(
			const sf::Vector2f& size=sf::Vector2f(0.0f, 0.0f),
			float radius=0.0f,
			size_t radiusPointsCount=6
		);

		// Изменить размер прямоугольника
		void setSize(const sf::Vector2f& size);
		// Получить размер прямоугольника
		const sf::Vector2f& getSize();

		// Метод изменения радиуса закругления
		void setRadius(float radius);
		// Получить радиус закругления
		float getRadius();

		// Метод изменения кол-во точек у закругления
		void setRadiusPointsCount(size_t count);
		// Получить кол-во точек у закругления
		size_t getRadiusPointsCount();

		std::size_t getPointCount() const override;
		sf::Vector2f getPoint(size_t index) const override;

	private:
		sf::Vector2f size;
		float radius;
		size_t radiusPointsCount;

		std::vector<sf::Vector2f> points;

		void updatePointsArray();
		void updatePoints();
	};
}
