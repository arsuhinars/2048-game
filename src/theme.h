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

		// Цвета тайлов в зависимости от степени двойки.
		// Первый - цвет фона, второй - цвет шрифта, третий - цвет свечения
		std::vector<std::tuple<sf::Color, sf::Color, sf::Color>> tileColors;

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

		float tileGlowBlur;			// Размер размытия у свечения спрайта

		sf::Color overlayColor;		// Цвет оверлея

		float labelSize;			// Размер заголовка
		float textSize;				// Размер обычного текста
		sf::Color textColor;		// Цвет текста

		sf::Color buttonColor;		// Цвет кнопки
		sf::Color buttonHoverColor;	// Цвет подсвеченной кнопки
		sf::Color buttonTextColor;	// Цвет текста кнопки
		float buttonRounding;		// Закругление у кнопки
		float buttonTextMargin;		// Размер отступа текста у кнопки

		sf::Color topBarColor;		// Цвет фона верхней панели
		sf::Color topBarTextColor;	// Цвет текста верхней панели

		float topBarSize;			// Размер верхней панели
		float topBarPadding;		// Отступ верхней панели от края
		float topBarSpacing;		// Отступы между верхними панелями
		float topBarRounding;		// Закругление верхней панели
	};

	// Стандартная тема игры
	const Theme defaultTheme = {
		sf::Color(0xFAF8EFFF),	// background
		sf::Color(0xBBADA0FF),	// panelColor
		0.03125f,				// panelMargin
		0.03125f,				// panelRounding
		{
			// tileColors
			{ sf::Color(0xCDC1B4FF), sf::Color(0xF9F6F2FF), sf::Color(0x0) },	// пустой тайл
			{ sf::Color(0xEEE3D9FF), sf::Color(0x776E65FF), sf::Color(0x0) },	// 2
			{ sf::Color(0xEEE1C9FF), sf::Color(0x776E65FF), sf::Color(0x0) },	// 4
			{ sf::Color(0xF3B27AFF), sf::Color(0xF9F6F2FF), sf::Color(0x0) },	// 8
			{ sf::Color(0xF69664FF), sf::Color(0xF9F6F2FF), sf::Color(0x0) },	// 16
			{ sf::Color(0xF77C5FFF), sf::Color(0xF9F6F2FF), sf::Color(0x0) },	// 32
			{ sf::Color(0xF75F3BFF), sf::Color(0xF9F6F2FF), sf::Color(0x0) },	// 64
			{ sf::Color(0xEDD073FF), sf::Color(0xF9F6F2FF), sf::Color(0xF3D7743D) },	// 128
			{ sf::Color(0xEDCC62FF), sf::Color(0xF9F6F2FF), sf::Color(0xF3D77451) },	// 256
			{ sf::Color(0xEDC950FF), sf::Color(0xF9F6F2FF), sf::Color(0xF3D77465) },	// 512
			{ sf::Color(0xEDC53FFF), sf::Color(0xF9F6F2FF), sf::Color(0xF3D77479) },	// 1024
			{ sf::Color(0xEDC22EFF), sf::Color(0xF9F6F2FF), sf::Color(0xF3D7748E) },	// 2048
		},
		0.02f,		// tileSpacing
		0.0625f,	// tilePadding
		0.125f,		// tileRounding
		0.5f,		// tileTextSize		
		0.15f,		// tileTextMargin
		0.125f,		// tileGlowBlur
		sf::Color(0xFBECB096),	// overlayColor
		0.15f,					// labelSize
		0.1f,					// textSize
		sf::Color(0x776E65FF),	// textColor
		sf::Color(0xF3B27AFF),	// buttonColor
		sf::Color(0xDAA06DFF),	// buttonHoverColor
		sf::Color(0xF9F6F2FF),	// buttonTextColor
		0.03125f,				// buttonRounding
		0.125f,					// buttonTextMargin
		sf::Color(0xBBADA0FF),	// topBarColor
		sf::Color(0xF9F6F2FF),	// topBarTextColor
		0.125f,					// topBarSize
		0.02f,					// topBarPadding
		0.125f,					// topBarSpacing
		0.03125f,				// topBarRounding
	};
}
