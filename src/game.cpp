#include <algorithm>
#include <SFML/System.hpp>
#include <Windows.h>
#include "../resource.h"
#include "config.h"
#include "game.h"
#include "field.h"
#include "ui.h"
#include "roboto.h"
#include "glow_effect.h"

using namespace std;
using namespace sf;
using namespace arsuhinars;

unique_ptr<RenderWindow> game::window;
unique_ptr<Font> game::font = make_unique<Font>();
Theme		game::theme = defaultTheme;
FloatRect	game::fieldRect;
FloatRect	game::topBarRect;
GameState	game::state;
Vector2f	game::mousePos;

static bool isRunning = false;	// Запущена ли игра
static Clock gameClock;			// Игровые часы
static float timeDelta;			// Время в секундах, прошедшее с последнего кадра
static unsigned int oldScore;	// Предыдущее значение счета

void arsuhinars::game::run()
{
	state.load();
	oldScore = state.score;

	// Создаем окно игры
	window = make_unique<RenderWindow>(
		VideoMode(state.windowWidth, state.windowHeight),
		WINDOW_TITLE,
		Style::Close | Style::Titlebar | Style::Resize,
		ContextSettings(
			0U, 0U, ANTIALIAZING_LEVEL
		)
	);
	window->setFramerateLimit(FRAMERATE_LIMIT);
	
	// Загружаем иконку
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	HWND hwnd = window->getSystemHandle();

	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	// Загружаем шрифт
	font->loadFromMemory(Roboto_Regular_ttf, Roboto_Regular_ttf_len);

	handleResize();

	// Иницилизируем интерфейс
	ui::init();

	// Загружаем игровое поле
	field::init();

	if (state.isGameLost) {
		lose();
	}

	gameClock.restart();

	// Создаем основной цикл игры
	isRunning = true;
	while (isRunning) {
		update();
		render();
	}

	// Освобождаем память, занятую шрифтом
	font.release();

	// Сохраняем игру
	state.save();
	// и закрываем окно
	window->close();
}

void arsuhinars::game::reset()
{
	state.score = 0;
	state.isGameLost = false;

	ui::hideLoseMenu();
	ui::updateText();
	state.tilemap.clear();
	field::init();
}

void arsuhinars::game::lose()
{
	state.isGameLost = true;
	ui::showLoseMenu();
}

void arsuhinars::game::update()
{
	Event ev;
	while (window->pollEvent(ev)) {
		// Обрабатываем события окна
		switch (ev.type) {
			case Event::KeyPressed: {
				// Клавиша нажата
				handleInput(ev.key);
				break;
			}
			case Event::MouseMoved: {
				mousePos = Vector2f(
					static_cast<float>(ev.mouseMove.x),
					static_cast<float>(ev.mouseMove.y)
				);
				break;
			}
			case Event::Resized: {
				// У окна был изменен размер
				FloatRect visibleArea(
					0.0f,
					0.0f,
					static_cast<float>(ev.size.width),
					static_cast<float>(ev.size.height)
				);
				window->setView(View(visibleArea));
				handleResize();
				ui::updateSize();
				field::updateFieldSize();
				field::updateTilesSizes();
				break;
			}
			case Event::Closed: {
				// Окно было закрыто
				isRunning = false;
				break;
			}
		}
	}

	timeDelta = gameClock.restart().asSeconds();

	if (state.score != oldScore) {
		if (state.score > state.record) {
			state.record = state.score;
		}

		if (state.score > oldScore) {
			ui::showScoresPopUp(state.score - oldScore);
		}
		ui::updateText();
	}
}

void arsuhinars::game::render()
{
	window->clear(theme.background);

	field::render();
	ui::render();

	window->display();
}

void arsuhinars::game::handleInput(sf::Event::KeyEvent& ev)
{
	if (!state.isGameLost) {
		field::handleInput(ev.code);
	}

	if (ev.code == Keyboard::R) {
		// Кнопка сброса игры
		reset();
		return;
	}
}

void arsuhinars::game::handleResize()
{
	auto windowSize = window->getSize();

	// Находим область игрового поля на экране
	fieldRect.width = windowSize.x;
	fieldRect.height = fieldRect.width;

	topBarRect.width = fieldRect.width;
	topBarRect.height = game::theme.topBarSize * fieldRect.width;

	float totalHeight = fieldRect.width + topBarRect.height;
	if (totalHeight > windowSize.y) {
		float scale = windowSize.y / totalHeight;

		fieldRect.width *= scale;
		fieldRect.height *= scale;
		topBarRect.width *= scale;
		topBarRect.height *= scale;

		fieldRect.left = (windowSize.x - fieldRect.width) / 2.0f;
		topBarRect.left = fieldRect.left;
		fieldRect.top = topBarRect.height;
		topBarRect.top = 0.0f;
	}
	else {
		topBarRect.left = 0.0f;
		fieldRect.left = 0.0f;
		topBarRect.top = (windowSize.y - totalHeight) / 2.0f;
		fieldRect.top = topBarRect.top + topBarRect.height;
	}

	//if (windowSize.x > windowSize.y) {
	//	fieldRect.left = static_cast<int>((windowSize.x - windowSize.y) / 2.0f);
	//	fieldRect.top = 0;
	//}
	//else {
	//	fieldRect.left = 0;
	//	fieldRect.top = static_cast<int>((windowSize.y - windowSize.x) / 2.0f);
	//}
}

float arsuhinars::game::getTimeDelta()
{
	return timeDelta;
}
