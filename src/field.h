#pragma once
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	namespace field
	{
		// ����� ��������� ������� ����� �� ��� ����������
		size_t getTileIndex(unsigned int x, unsigned int y);

		// ����� ������ ������� ����� �� ��� �������
		sf::Vector2u getTilePos(size_t index);

		// ����� ������������� ����
		void init();

		// ����� ��������� ���� ����
		void render();

		// ����� �������� ����� ��������� ������
		void spawnTile();

		// ������� ����������� ���� ������ � �������������� �������
		void moveTilesUp();
		void moveTilesRight();
		void moveTilesDown();
		void moveTilesLeft();

		// ����������� ���� �� ����� ������� � ������
		// ���������� ������, ���� ���� ��� ������� ����������, ����� - ����
		bool moveTile(sf::Vector2u from, sf::Vector2u to);

		// ��������� �� �����-������ ����
		bool isAnyTileMoving();
	}
}
