#pragma once
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	class Tile
	{
	public:
		// ���� �������� � �����
		enum Animation {
			None, Appear, ChangeValue
		};

		Tile(sf::Vector2f position, unsigned int value=0);

		// ��� �� ��� ���� ������������� � ������
		bool wasAlreadySummed = false;
		
		// ��������� ������������� ������ �����
		static float calcRelativeTileSize();
		// ����� ���������� ������� ������ �����
		static unsigned int calcTileSize();
		// ����� ��� ���������� ������� ����� �� ������
		static sf::Vector2f calcTileScreenPos(sf::Vector2f position);

		// ����� ��������� ������
		void render();

		// ����� ��� ��������� ������� ������
		// ���������� ������ ��������� � ������� �� 0 �� n - 1, ��� n - ������ ����
		void setPosition(sf::Vector2f position);
		// ����� ��� ��������� ������� ������
		sf::Vector2f getPosition();

		// ����� ��������� �������� � �����
		// �������� - ��� ������� ������
		void setValue(unsigned int value);
		// ����� ��� ��������� �������� �����
		unsigned int getValue();

		// ������������ �� ������ � ������ ������
		bool isMoving();
		// ����������� ������ ������ � ������ �������
		void moveTo(sf::Vector2f position);

		// ��������� ��������
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
