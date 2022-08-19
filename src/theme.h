#pragma once
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "config.h"

namespace arsuhinars
{
	// Структура темы. Она используется для определения внешнего вида игры
	struct Theme {
		sf::Color background;		// Цвет фона окна

		sf::Color panelColor;		// Цвет подложки
		float panelMargin;			// Отступ у подложки
		float panelRounding;		// Закругление у подложки

		// Цвета тайлов в зависимости от степени двойки. Первый - цвет фона, второй - цвет шрифта
		std::vector<std::tuple<sf::Color, sf::Color>> tileColors;

		// Расстояние между тайлами в процентах от размера экрана (от 0 до 1)
		float tileSpacing;
		// Отступ от края экрана и тайлами в процентах
		float tilePadding;
		// Размер закруления тайла в процентах от его размера
		float tileRounding;

		// Размер текста внутри тайла в процентах
		float tileTextSize;
		// Отступ от края для текста тайла
		float tileTextMargin;
	};

	// Стандартная тема игры
	const Theme defaultTheme = {
		sf::Color(0xFAF8EFFF),	// background
		sf::Color(0xBBADA0FF),	// panelColor
		0.03125f,				// panelMargin
		0.03125f,				// panelRounding
		{
			// tileColors
			{ sf::Color(0xCDC1B4FF), sf::Color(0xF9F6F2FF) },	// пустой тайл
			{ sf::Color(0xEEE3D9FF), sf::Color(0x776E65FF) },	// 2
			{ sf::Color(0xEEE1C9FF), sf::Color(0x776E65FF) },	// 4
			{ sf::Color(0xF3B27AFF), sf::Color(0xF9F6F2FF) },	// 8
			{ sf::Color(0xF69664FF), sf::Color(0xF9F6F2FF) },	// 16
			{ sf::Color(0xF77C5FFF), sf::Color(0xF9F6F2FF) },	// 32
			{ sf::Color(0xF75F3BFF), sf::Color(0xF9F6F2FF) },	// 64
			{ sf::Color(0xEDD073FF), sf::Color(0xF9F6F2FF) },	// 128
			{ sf::Color(0xEDCC62FF), sf::Color(0xF9F6F2FF) },	// 256
			{ sf::Color(0xEDC950FF), sf::Color(0xF9F6F2FF) },	// 512
			{ sf::Color(0xEDC53FFF), sf::Color(0xF9F6F2FF) },	// 1024
			{ sf::Color(0xEDC22EFF), sf::Color(0xF9F6F2FF) },	// 2048
		},
		0.02f,		// tileSpacing
		0.0625f,	// tilePadding
		0.125f,		// tileRounding
		0.5f,		// tileTextSize		
		0.15f,		// tileTextMargin
	};
}
