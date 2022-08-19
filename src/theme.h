#pragma once
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "config.h"

namespace arsuhinars
{
	// ��������� ����. ��� ������������ ��� ����������� �������� ���� ����
	struct Theme {
		sf::Color background;		// ���� ���� ����

		sf::Color panelColor;		// ���� ��������
		float panelMargin;			// ������ � ��������
		float panelRounding;		// ����������� � ��������

		// ����� ������ � ����������� �� ������� ������. ������ - ���� ����, ������ - ���� ������
		std::vector<std::tuple<sf::Color, sf::Color>> tileColors;

		// ���������� ����� ������� � ��������� �� ������� ������ (�� 0 �� 1)
		float tileSpacing;
		// ������ �� ���� ������ � ������� � ���������
		float tilePadding;
		// ������ ���������� ����� � ��������� �� ��� �������
		float tileRounding;

		// ������ ������ ������ ����� � ���������
		float tileTextSize;
		// ������ �� ���� ��� ������ �����
		float tileTextMargin;
	};

	// ����������� ���� ����
	const Theme defaultTheme = {
		sf::Color(0xFAF8EFFF),	// background
		sf::Color(0xBBADA0FF),	// panelColor
		0.03125f,				// panelMargin
		0.03125f,				// panelRounding
		{
			// tileColors
			{ sf::Color(0xCDC1B4FF), sf::Color(0xF9F6F2FF) },	// ������ ����
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
