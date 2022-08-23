#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	// ����� ��� �������� ������� ��������
	class GlowEffect : public sf::Transformable, public sf::Drawable
	{
	public:
		// ����������� ������
		GlowEffect(
			const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f),
			float radius = 0.0f,
			const sf::Color& glowColor = sf::Color::Black,
			float glowBlur = 0.0f,
			float glowSpread = 0.0f
		);

		// �������� ������ �������������� ��������
		void setSize(const sf::Vector2f& size);
		// �������� ������ ��������������
		const sf::Vector2f& getSize();

		// �������� ������ ����������� ��������������
		void setRadius(float radius);
		// �������� ������ �����������
		float getRadius();

		// �������� ���� ��������
		void setGlowColor(const sf::Color& color);
		// �������� ���� ��������
		const sf::Color& getGlowColor();

		// �������� ������ �������� � ��������
		void setGlowBlur(float blur);
		// �������� ������ �������� ��������
		float getGlowBlur();

		// �������� ������ ���������� ��������
		void setGlowSpread(float spread);
		// �������� ������ ���������� ��������
		float getGlowSpread();

		// ����� ���������
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Transform edgeTransform;
		sf::RectangleShape shape;

		sf::Vector2f size;
		float radius;
		sf::Color glowColor;
		float glowBlur;
		float glowSpread;

		void updateSize();
	};
}
