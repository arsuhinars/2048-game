#pragma once
#include <SFML/Graphics.hpp>
#include "rounded_rect.h"

namespace arsuhinars
{
	// ����� ���������� ������
	class Button : public sf::Transformable, public sf::Drawable
	{
	public:
		// �����������
		Button(const sf::String& text = "", const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f));

		// ����� ��������� ������ ������
		void setText(const sf::String& string);
		// �������� ����� ������
		const sf::String& getText();

		// ����� ��������� ������� ������
		void setSize(const sf::Vector2f& size);
		// �������� ������ ������
		sf::Vector2f getSize();

		// ����� ��������� ������������
		void setOpacity(sf::Uint8 opacity);
		// �������� ������������ ������
		sf::Uint8 getOpacity();

		// ����� ���������� ����� ������ �� ������� ����
		void updateStyle();

		// ����� ���������� ������. ������ ���������� ����� ����������
		void update();

		// ���� �� ������ ������
		bool isClicked();

		// ����� ��������� ������
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		
	private:
		RoundedRectShape shape;
		sf::Text text;

		sf::Uint8 opacity;
		float hoverFactor = 0.0f;

		bool m_isClicked = false;

		void updateColors();
		void updateSizes();
	};
}
