#include "game.h"
#include "button.h"
#include "config.h"
#include "utils.h"

using namespace sf;

arsuhinars::Button::Button(const sf::String& text, const sf::Vector2f& size)
{
    Button::text.setFont(*game::font);
    Button::text.setString(text);
    Button::text.setStyle(Text::Bold);

    Button::shape.setSize(size);

    updateStyle();
}

void arsuhinars::Button::setText(const sf::String& string)
{
    text.setString(string);
    updateSizes();
}

const sf::String& arsuhinars::Button::getText()
{
    return text.getString();
}

void arsuhinars::Button::setSize(const sf::Vector2f& size)
{
    shape.setSize(size);
    updateSizes();
}

sf::Vector2f arsuhinars::Button::getSize()
{
    return shape.getSize();
}

void arsuhinars::Button::setOpacity(sf::Uint8 opacity)
{
    Button::opacity = opacity;

    updateColors();
}

sf::Uint8 arsuhinars::Button::getOpacity()
{
    return opacity;
}

void arsuhinars::Button::updateStyle()
{
    updateColors();
    updateSizes();
}

void arsuhinars::Button::update()
{
    auto bounds = shape.getLocalBounds();
    bounds = getTransform().transformRect(bounds);

    if (bounds.contains(game::mousePos)) {
        // Если курсор находится над кнопкой
        hoverFactor += game::getTimeDelta() / BUTTON_TRANSITION_TIME;
        if (hoverFactor > 1.0f) {
            hoverFactor = 1.0f;
        }

        m_isClicked = Mouse::isButtonPressed(Mouse::Button::Left);
    }
    else {
        hoverFactor -= game::getTimeDelta() / BUTTON_TRANSITION_TIME;
        if (hoverFactor < 0.0f) {
            hoverFactor = 0.0f;
        }
        m_isClicked = false;
    }

    shape.setFillColor(utils::lerpColor(
        game::theme.buttonColor,
        game::theme.buttonHoverColor,
        hoverFactor
    ));
}

bool arsuhinars::Button::isClicked()
{
    return m_isClicked;
}

void arsuhinars::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(shape, states);
    target.draw(text, states);
}

void arsuhinars::Button::updateColors()
{
    auto shapeColor = game::theme.buttonColor;
    auto textColor = game::theme.buttonTextColor;

    shapeColor.a = opacity;
    textColor.a = opacity;

    Button::shape.setFillColor(game::theme.buttonColor);
    Button::text.setFillColor(game::theme.buttonTextColor);
}

void arsuhinars::Button::updateSizes()
{
    shape.setRadius(game::theme.buttonRounding * game::fieldRect.width);

    text.setCharacterSize(
        static_cast<unsigned int>(game::fieldRect.width * game::theme.textSize)
    );

    auto bounds = shape.getLocalBounds();
    auto textBounds = text.getLocalBounds();
    
    auto textMaxWidth = bounds.width * (1.0f - game::theme.buttonTextMargin * 2.0f);
    auto textMaxHeight = bounds.height * (1.0f - game::theme.buttonTextMargin * 2.0f);

    float textScale = 1.0f;
    if (textBounds.width > textMaxWidth) {
        textScale = textMaxWidth / textBounds.width;
    }
    if (textBounds.height * textScale > textMaxHeight) {
        textScale = textMaxHeight / (textBounds.height * textScale);
    }

    textBounds.left *= textScale;
    textBounds.top *= textScale;
    textBounds.width *= textScale;
    textBounds.height *= textScale;

    text.setScale(Vector2f(textScale, textScale));

    text.setPosition(Vector2f(
        (bounds.width - textBounds.width) / 2.0f - textBounds.left,
        (bounds.height - textBounds.height) / 2.0f - textBounds.top
    ));
}
