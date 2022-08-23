#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	// Класс для создания эффекта свечения
	class GlowEffect : public sf::Transformable, public sf::Drawable
	{
	public:
		// Конструктор класса
		GlowEffect(
			const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f),
			float radius = 0.0f,
			const sf::Color& glowColor = sf::Color::Black,
			float glowBlur = 0.0f,
			float glowSpread = 0.0f
		);

		// Изменить размер прямоугольника свечения
		void setSize(const sf::Vector2f& size);
		// Получить размер прямоугольника
		const sf::Vector2f& getSize();

		// Изменить радиус закругления прямоугольника
		void setRadius(float radius);
		// Получить радиус закругления
		float getRadius();

		// Изменить цвет свечения
		void setGlowColor(const sf::Color& color);
		// Получить цвет свечения
		const sf::Color& getGlowColor();

		// Изменить размер размытия у свечения
		void setGlowBlur(float blur);
		// Получить размер размытия свечения
		float getGlowBlur();

		// Изменить размер расширения свечения
		void setGlowSpread(float spread);
		// Получить размер расширения свечения
		float getGlowSpread();

		// Метод отрисовки
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
