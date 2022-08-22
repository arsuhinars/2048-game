#include <memory>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "game.h"
#include "rounded_rect.h"
#include "button.h"
#include "ui.h"
#include "utils.h"

using namespace std;
using namespace sf;
using namespace arsuhinars;

static RoundedRectShape loseMenuOverlay;
static Text loseMenuText;
static unique_ptr<Button> loseMenuButton;
static bool isLoseMenuShowed = false;
static float animFactor = 0.0f;

static RoundedRectShape leftBarPanel;
static RoundedRectShape rightBarPanel;
static Text scoreLabel;
static Text scoreText;
static Text recordLabel;
static Text recordText;

//static Text popUpText;
//static float popUpAnimFactor = 0.0f;

void arsuhinars::ui::init()
{
	leftBarPanel.setFillColor(game::theme.topBarColor);
	rightBarPanel.setFillColor(game::theme.topBarColor);

	scoreLabel.setFillColor(game::theme.topBarTextColor);
	scoreLabel.setFont(*game::font);
	scoreLabel.setString("Score");
	scoreLabel.setStyle(Text::Bold);

	recordLabel = scoreLabel;
	recordLabel.setString("Best");

	scoreText.setFillColor(game::theme.topBarTextColor);
	scoreText.setFont(*game::font);
	scoreText.setStyle(Text::Bold);

	recordText = scoreText;

	loseMenuText.setFillColor(game::theme.textColor);
	loseMenuText.setFont(*game::font);
	loseMenuText.setString("You lose!");
	loseMenuText.setStyle(Text::Bold);

	loseMenuButton = make_unique<Button>();
	loseMenuButton->setText("Restart (R)");

	updateSize();
}

void arsuhinars::ui::render()
{
	if (isLoseMenuShowed) {
		if (animFactor < 1.0f) {
			auto bgColor = game::theme.overlayColor;
			bgColor.a = static_cast<unsigned int>(bgColor.a * animFactor);

			loseMenuOverlay.setFillColor(bgColor);

			float scale = utils::lerp(0.9f, 1.0f, animFactor);

			auto textColor = game::theme.textColor;
			textColor.a = static_cast<unsigned int>(textColor.a * animFactor);

			loseMenuText.setScale(scale, scale);
			loseMenuText.setFillColor(textColor);

			loseMenuButton->setScale(scale, scale);
			loseMenuButton->setOpacity(
				static_cast<Uint8>(255.0f * animFactor)
			);
		}
		else {
			loseMenuOverlay.setFillColor(game::theme.overlayColor);

			loseMenuText.setScale(1.0f, 1.0f);
			loseMenuText.setFillColor(game::theme.textColor);

			loseMenuButton->setScale(1.0f, 1.0f);
			loseMenuButton->setOpacity(255);
		}

		loseMenuButton->update();
		if (loseMenuButton->isClicked()) {
			game::reset();
		}

		game::window->draw(loseMenuOverlay);
		game::window->draw(loseMenuText);
		game::window->draw(*loseMenuButton);

		animFactor += game::getTimeDelta() / LOSE_MENU_ANIMATION_DURATION;
	}

	game::window->draw(leftBarPanel);
	game::window->draw(scoreLabel);
	game::window->draw(scoreText);

	game::window->draw(rightBarPanel);
	game::window->draw(recordLabel);
	game::window->draw(recordText);
}

void arsuhinars::ui::updateSize()
{
	// Устанавливаем размер оверлея

	loseMenuOverlay.setSize(
		game::fieldRect.width * (1.0f - game::theme.panelMargin * 2.0f) * Vector2f(1.0f, 1.0f)
	);
	loseMenuOverlay.setRadius(
		loseMenuOverlay.getSize().x * game::theme.panelRounding
	);
	loseMenuOverlay.setPosition(Vector2f(
		static_cast<float>(game::fieldRect.left),
		static_cast<float>(game::fieldRect.top)
	) + Vector2f(1.0f, 1.0f) * (game::theme.panelMargin * game::fieldRect.width));

	loseMenuText.setCharacterSize(
		static_cast<unsigned int>(game::fieldRect.width * game::theme.labelSize)
	);

	auto overlayBounds = loseMenuOverlay.getLocalBounds();
	auto textBounds = loseMenuText.getLocalBounds();

	loseMenuText.setOrigin(Vector2f(
		textBounds.width * 0.5f + textBounds.left,
		textBounds.height * 0.5f + textBounds.top
	));
	loseMenuText.setPosition(Vector2f(
		overlayBounds.width * 0.5f,
		overlayBounds.height * 0.25f
	) + loseMenuOverlay.getPosition());

	loseMenuButton->setSize(Vector2f(
		game::fieldRect.width * 0.4f,
		game::fieldRect.width * 0.125f
	));
	loseMenuButton->setOrigin(loseMenuButton->getSize() / 2.0f);
	loseMenuButton->setPosition(Vector2f(
		overlayBounds.width * 0.5f,
		overlayBounds.height * 0.6f
	) + loseMenuOverlay.getPosition());

	// Устанавливаем размер верхней панели

	auto topBarPanelSize = Vector2f(
		game::topBarRect.width * (0.5f - game::theme.topBarSpacing * 0.5f - game::theme.panelMargin),
		game::topBarRect.height - game::topBarRect.width * game::theme.topBarPadding
	);

	leftBarPanel.setSize(topBarPanelSize);
	leftBarPanel.setRadius(game::topBarRect.width * game::theme.topBarRounding);
	leftBarPanel.setPosition(Vector2f(
		game::topBarRect.left + game::topBarRect.width * game::theme.panelMargin,
		game::topBarRect.top + game::topBarRect.width * game::theme.topBarPadding
	));

	rightBarPanel.setSize(topBarPanelSize);
	rightBarPanel.setRadius(leftBarPanel.getRadius());
	rightBarPanel.setPosition(Vector2f(
		leftBarPanel.getPosition().x + topBarPanelSize.x + game::topBarRect.width * game::theme.topBarSpacing,
		leftBarPanel.getPosition().y
	));

	scoreLabel.setCharacterSize(
		static_cast<unsigned int>(game::topBarRect.width * game::theme.textSize)
	);

	auto labelBounds = scoreLabel.getLocalBounds();
	scoreLabel.setScale(
		Vector2f(1.0f, 1.0f) * (leftBarPanel.getSize().y * 0.3f / (labelBounds.height + labelBounds.top))
	);
	scoreLabel.setOrigin(Vector2f(
		labelBounds.width * 0.5f + labelBounds.left,
		0.0f
	));
	scoreLabel.setPosition(Vector2f(
		leftBarPanel.getPosition().x + topBarPanelSize.x * 0.5f,
		leftBarPanel.getPosition().y
	));

	recordLabel.setCharacterSize(scoreLabel.getCharacterSize());

	labelBounds = recordLabel.getLocalBounds();
	recordLabel.setScale(scoreLabel.getScale());
	recordLabel.setOrigin(Vector2f(
		labelBounds.width * 0.5f + labelBounds.left,
		0.0f
	));
	recordLabel.setPosition(Vector2f(
		rightBarPanel.getPosition().x + topBarPanelSize.x * 0.5f,
		rightBarPanel.getPosition().y
	));

	updateText();
}

void arsuhinars::ui::updateText()
{
	scoreText.setCharacterSize(scoreLabel.getCharacterSize());
	scoreText.setString(to_string(game::state.score));

	auto textBounds = scoreText.getLocalBounds();
	scoreText.setScale(
		Vector2f(1.0f, 1.0f) * (leftBarPanel.getSize().y * 0.7f / (textBounds.height + textBounds.top * 2.0f))
	);
	scoreText.setOrigin(Vector2f(
		textBounds.width * 0.5f + textBounds.left,
		textBounds.top * 2.0f + textBounds.height
	));
	scoreText.setPosition(Vector2f(
		scoreLabel.getPosition().x,
		leftBarPanel.getPosition().y + leftBarPanel.getSize().y
	));

	recordText.setCharacterSize(scoreText.getCharacterSize());
	recordText.setString(to_string(game::state.record));

	textBounds = recordText.getLocalBounds();
	recordText.setScale(scoreText.getScale());
	recordText.setOrigin(Vector2f(
		textBounds.width * 0.5f + textBounds.left,
		textBounds.top * 2.0f + textBounds.height
	));
	recordText.setPosition(Vector2f(
		recordLabel.getPosition().x,
		rightBarPanel.getPosition().y + rightBarPanel.getSize().y
	));
}

void arsuhinars::ui::showScoresPopUp(unsigned int value)
{
}

void arsuhinars::ui::showLoseMenu()
{
	isLoseMenuShowed = true;
	animFactor = 0.0f;
}

void arsuhinars::ui::hideLoseMenu()
{
	isLoseMenuShowed = false;
}
