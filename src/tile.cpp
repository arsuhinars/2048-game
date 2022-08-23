#include <algorithm>
#include <string>
#include "config.h"
#include "game.h"
#include "field.h"
#include "tile.h"
#include "utils.h"

using namespace std;
using namespace sf;

arsuhinars::Tile::Tile(sf::Vector2f position, unsigned int value)
{	
	text.setFont(*game::font);
	text.setStyle(Text::Bold);

	updateSize();
	setPosition(position);
	setValue(value);
}

float arsuhinars::Tile::calcRelativeTileSize()
{
	return (1.0f - game::theme.tilePadding * 2 - game::theme.tileSpacing * (game::state.fieldSize - 1)) / game::state.fieldSize;
}

unsigned int arsuhinars::Tile::calcTileSize()
{
	return static_cast<unsigned int>(game::fieldRect.width * calcRelativeTileSize());
}

sf::Vector2f arsuhinars::Tile::calcTileScreenPos(sf::Vector2f position)
{
	auto relTileSize = calcRelativeTileSize();

	auto screenPos = (relTileSize + game::theme.tileSpacing) * position;
	screenPos += (game::theme.tilePadding + relTileSize / 2.0f) * Vector2f(1.0f, 1.0f);
	screenPos *= static_cast<float>(game::fieldRect.width);

	screenPos.x += game::fieldRect.left;
	screenPos.y += game::fieldRect.top;

	return screenPos;
}

void arsuhinars::Tile::render()
{
	// Анимируем перемещение тайла
	if (m_isMoving) {
		moveFactor += game::getTimeDelta() / TILE_TRANSITION_TIME;

		Vector2f pos;
		if (moveFactor >= 1.0f) {
			m_isMoving = false;
			position = targetPosition;
			pos = targetPosition;
		}
		else {
			pos = utils::lerpVector(position, targetPosition, moveFactor);
		}
		
		setPosition(pos);
	}

	if (currAnim != Animation::None) {
		animFactor += animDelta * game::getTimeDelta();
		if (animFactor >= 1.0f) {
			currAnim = Animation::None;
			animFactor = 1.0f;
			scaleFactor = 1.0f;
		}
		else {
			// Анимируем тайл
			switch (currAnim) {
			case Animation::Appear:
				scaleFactor = utils::lerp(0.5f, 1.0f, animFactor);
				break;
			case Animation::ChangeValue:
				scaleFactor = animFactor < 0.5f ? 
					utils::lerp(1.0f, 1.2f, animFactor * 2.0f) :
					utils::lerp(1.2f, 1.0f, animFactor * 2.0f - 1.0f);
				break;
			}
		}

		shape.setScale(Vector2f(scaleFactor, scaleFactor));
		updateTextScale();
	}

	game::window->draw(glow);
	game::window->draw(shape);

	if (value > 0) {
		game::window->draw(text);
	}
}

void arsuhinars::Tile::setPosition(sf::Vector2f position)
{
	Tile::position = position;

	shape.setPosition(calcTileScreenPos(position));
	glow.setPosition(shape.getPosition());
	updateTextPosition();
}

sf::Vector2f arsuhinars::Tile::getPosition()
{
	return position;
}

void arsuhinars::Tile::setValue(unsigned int value)
{
	Tile::value = value;

	text.setString(to_string(utils::findPowerOfTwo(value)));

	updateStyle();
	updateTextScale();
	updateTextPosition();
}

unsigned int arsuhinars::Tile::getValue()
{
	return value;
}

bool arsuhinars::Tile::isMoving()
{
	return m_isMoving;
}

void arsuhinars::Tile::moveTo(sf::Vector2f position)
{
	moveFactor = 0.0f;
	m_isMoving = true;
	targetPosition = position;
}

void arsuhinars::Tile::playAnimation(Animation animation)
{
	currAnim = animation;

	if (animation != Animation::None) {
		animFactor = 0.0f;
		animDelta = 1.0f / TILE_ANIMATION_TIME.at(animation);
	}
}

void arsuhinars::Tile::updateTextPosition()
{
	text.setPosition(
		shape.getPosition()
	);
}

void arsuhinars::Tile::updateTextScale()
{
	auto tileSize = calcTileSize();
	auto bounds = text.getLocalBounds();
	auto maxTextWidth = tileSize * (1.0f - game::theme.tileTextMargin * 2.0f);

	if (bounds.width > maxTextWidth) {
		// Маштабируем текст под границы
		float scale = maxTextWidth / bounds.width * scaleFactor;

		text.setScale(Vector2f(scale, scale));
	}
	else {
		text.setScale(scaleFactor, scaleFactor);
	}

	text.setOrigin(
		Vector2f(bounds.width / 2.0f + bounds.left, bounds.height / 2.0f + bounds.top)
	);
}

void arsuhinars::Tile::updateSize()
{
	auto tileSize = static_cast<float>(calcTileSize());

	shape.setSize(Vector2f(tileSize, tileSize));
	shape.setRadius(tileSize * game::theme.tileRounding);
	shape.setOrigin(Vector2f(0.5f, 0.5f) * tileSize);
	shape.setPosition(calcTileScreenPos(position));

	glow.setSize(shape.getSize());
	glow.setOrigin(shape.getOrigin());
	glow.setRadius(shape.getRadius());
	glow.setPosition(shape.getPosition());
	glow.setGlowBlur(tileSize * game::theme.tileGlowBlur);

	text.setCharacterSize(
		static_cast<unsigned int>(calcTileSize() * game::theme.tileTextSize)
	);

	updateTextPosition();
	updateTextScale();
}

void arsuhinars::Tile::updateStyle()
{
	auto tileColorIndex = min(static_cast<size_t>(value), game::theme.tileColors.size() - 1);

	auto& color1 = get<0>(game::theme.tileColors[tileColorIndex]);
	auto& color2 = get<1>(game::theme.tileColors[tileColorIndex]);
	auto& color3 = get<2>(game::theme.tileColors[tileColorIndex]);

	shape.setFillColor(color1);
	text.setFillColor(color2);
	glow.setGlowColor(color3);
}
