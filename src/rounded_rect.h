#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"

namespace arsuhinars
{
	// Функция для создания прямоугольника с закругленными углами
	sf::ConvexShape createRoundedRect(
		sf::Vector2f size,
		float radius,
		size_t circlePointsCount=ROUNDED_RECT_CIRCLE_POINTS_COUNT
	);
}
