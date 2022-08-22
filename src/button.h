#pragma once
#include <SFML/Graphics.hpp>
#include "rounded_rect.h"

namespace arsuhinars
{
	// Класс наэкранной кнопки
	class Button : public sf::Transformable, public sf::Drawable
	{
	public:
		// Конструктор
		Button(const sf::String& text = "", const sf::Vector2f& size = sf::Vector2f(0.0f, 0.0f));

		// Метод изменения текста кнопки
		void setText(const sf::String& string);
		// Получить текст кнопки
		const sf::String& getText();

		// Метод изменения размера кнопки
		void setSize(const sf::Vector2f& size);
		// Получить размер кнопки
		sf::Vector2f getSize();

		// Метод изменения прозрачности
		void setOpacity(sf::Uint8 opacity);
		// Получить прозрачность кнопки
		sf::Uint8 getOpacity();

		// Метод обновления стиля кнопки из текущей темы
		void updateStyle();

		// Метод обновления кнопки. Должен вызываться перед отрисовкой
		void update();

		// Была ли нажата кнопка
		bool isClicked();

		// Метод отрисовки кнопки
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
