#include <algorithm>
#include <SFML/System.hpp>
#include "config.h"
#include "game.h"
#include "field.h"
#include "roboto.h"

using namespace std;
using namespace sf;
using namespace arsuhinars;

unique_ptr<RenderWindow> game::window;
unique_ptr<Font> game::font = make_unique<Font>();
Theme		game::theme = defaultTheme;
IntRect		game::fieldRect;
GameState	game::state;

static bool isRunning = false;	// �������� �� ����
static Clock gameClock;			// ������� ����
static float timeDelta;			// ����� � ��������, ��������� � ���������� �����

void arsuhinars::game::run()
{
	// ������� ���� ����
	window = make_unique<RenderWindow>(
		VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE,
		Style::Close | Style::Titlebar,
		ContextSettings(
			0U, 0U, ANTIALIAZING_LEVEL
		)
	);
	window->setFramerateLimit(FRAMERATE_LIMIT);

	// ��������� �����
	font->loadFromMemory(Roboto_Regular_ttf, Roboto_Regular_ttf_len);

	// ������� ������� �������� ���� �� ������
	fieldRect.width = min(WINDOW_WIDTH, WINDOW_HEIGHT);
	fieldRect.height = fieldRect.width;
	if (WINDOW_WIDTH > WINDOW_HEIGHT) {
		fieldRect.left = static_cast<int>((WINDOW_WIDTH - WINDOW_HEIGHT) / 2.0f);
		fieldRect.top = 0;
	}
	else {
		fieldRect.left = 0;
		fieldRect.top = static_cast<int>((WINDOW_HEIGHT - WINDOW_WIDTH) / 2.0f);
	}

	// ��������� ������� ����
	state.load();
	field::init();

	gameClock.restart();

	// ������� �������� ���� ����
	isRunning = true;
	while (isRunning) {
		update();
		render();
	}

	// ����������� ������, ������� �������
	font.release();

	// ��������� ����
	state.save();
	// � ��������� ����
	window->close();
}

void arsuhinars::game::reset()
{
	state.tilemap.clear();
	field::init();
}

void arsuhinars::game::update()
{
	Event ev;
	while (window->pollEvent(ev)) {
		// ������������ ������� ����
		switch (ev.type) {
		case Event::KeyPressed:
			// ������� ������
			handleInput(ev.key);
			break;
		case Event::Closed:
			// ���� ���� �������
			isRunning = false;
			break;
		}
	}

	timeDelta = gameClock.restart().asSeconds();
}

void arsuhinars::game::render()
{
	window->clear(theme.background);

	field::render();

	window->display();
}

void arsuhinars::game::handleInput(sf::Event::KeyEvent& ev)
{
	if (field::isAnyTileMoving()) {
		return;
	}

	switch (ev.code) {
	// ������������ ������ �����������
	case Keyboard::Up:
	case Keyboard::W:
		field::moveTilesUp();
		break;
	case Keyboard::Right:
	case Keyboard::D:
		field::moveTilesRight();
		break;
	case Keyboard::Down:
	case Keyboard::S:
		field::moveTilesDown();
		break;
	case Keyboard::Left:
	case Keyboard::A:
		field::moveTilesLeft();
		break;
	case Keyboard::R:
		// ������ ������ ����
		reset();
		break;
	}
}

float arsuhinars::game::getTimeDelta()
{
	return timeDelta;
}
