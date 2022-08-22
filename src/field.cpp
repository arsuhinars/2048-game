#include <algorithm>
#include "game.h"
#include "field.h"
#include "rounded_rect.h"
#include "utils.h"

using namespace std;
using namespace sf;
using namespace arsuhinars;

static RoundedRectShape panel;						// Подложка
static vector<Tile> emptyTiles;					// Массив пустых тайлов
static vector<unique_ptr<Tile>> deletingTiles;	// Тайлы, которые должны будут быть удаленны

size_t arsuhinars::field::getTileIndex(unsigned int x, unsigned int y)
{
	return static_cast<size_t>(x + game::state.fieldSize * y);
}

sf::Vector2u arsuhinars::field::getTilePos(size_t index)
{
	return Vector2u(
		static_cast<unsigned int>(index % game::state.fieldSize),
		static_cast<unsigned int>(index / game::state.fieldSize)
	);
}

void arsuhinars::field::init()
{
	auto fieldSize = game::state.fieldSize;
	auto tilesCount = static_cast<size_t>(fieldSize * fieldSize);

	if (game::state.tilemap.size() < tilesCount) {
		// Инитилизируем поле
		game::state.tilemap.clear();
		game::state.tilemap.resize(tilesCount);

		// Создаем два тайла в начале игры
		spawnTile();
		spawnTile();
	}

	emptyTiles.reserve(static_cast<size_t>(fieldSize * fieldSize));

	for (unsigned int x = 0; x < fieldSize; x++) {
		for (unsigned int y = 0; y < fieldSize; y++) {
			auto tilePos = Vector2f(
				static_cast<float>(x), static_cast<float>(y)
			);

			emptyTiles.push_back(Tile(tilePos));
		}
	}

	panel.setFillColor(game::theme.panelColor);

	updateFieldSize();
	updateTilesSizes();
}

void arsuhinars::field::updateFieldSize()
{
	// Обновляем подложку
	auto panelSize = game::fieldRect.width * (1.0f - game::theme.panelMargin * 2);

	panel.setSize(Vector2f(panelSize, panelSize));
	panel.setRadius(panelSize * game::theme.panelRounding);
	panel.setPosition(
		Vector2f(
			static_cast<float>(game::fieldRect.left),
			static_cast<float>(game::fieldRect.top)) +
		static_cast<float>(game::theme.panelMargin * game::fieldRect.width) * Vector2f(1.0f, 1.0f)
	);
}

void arsuhinars::field::updateTilesSizes()
{
	for (auto& tile : emptyTiles) {
		tile.updateSize();
	}
	
	for (auto& tile : deletingTiles) {
		if (tile) {
			tile->updateSize();
		}
	}
	
	for (auto& tile : game::state.tilemap) {
		if (tile) {
			tile->updateSize();
		}
	}
}

void arsuhinars::field::render()
{
	game::window->draw(panel);

	for (auto& emptyTile : emptyTiles) {
		emptyTile.render();
	}

	bool isAnyTileMoving = false;
	for (auto& tile : deletingTiles) {
		tile->render();
		if (tile->isMoving()) {
			isAnyTileMoving = true;
		}
	}
	if (!isAnyTileMoving) {
		deletingTiles.clear();
	}

	for (auto& tile : game::state.tilemap) {
		if (tile) {
			tile->render();
			// Сбрасываем флаг
			tile->wasAlreadySummed = false;
		}
	}
}

void arsuhinars::field::spawnTile()
{
	static vector<unsigned int> freeTilesIndexes;

	freeTilesIndexes.clear();

	// Находим свободные позиции для плиток
	for (size_t i = 0; i < game::state.tilemap.size(); i++) {
		if (!game::state.tilemap[i]) {
			freeTilesIndexes.push_back(static_cast<unsigned int>(i));
		}
	}

	if (freeTilesIndexes.size() == 0) {
		return;
	}

	// Выбираем случайную плитку
	unsigned int nextTileIndex = freeTilesIndexes[
		static_cast<size_t>(utils::randomRange(0, static_cast<int>(freeTilesIndexes.size())))
	];

	auto tilePos = getTilePos(nextTileIndex);

	// Спавним тайл
	game::state.tilemap[nextTileIndex] = make_unique<Tile>(
		Vector2f(
			static_cast<float>(tilePos.x),
			static_cast<float>(tilePos.y)
		),
		utils::random() < 0.9f ? 1 : 2	// Шанс спавна двойки - 90%, четверки - 10%
	);
	game::state.tilemap[nextTileIndex]->
		playAnimation(Tile::Animation::Appear);
}

void arsuhinars::field::handleInput(const sf::Keyboard::Key& key)
{
	if (isAnyTileMoving()) {
		return;
	}

	bool isMoveKey = true;
	switch (key) {
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
	default:
		isMoveKey = false;
		break;
	}

	if (isMoveKey && !isThereAnyMove()) {
		// Проигрыш, если у игрока нет возможности ходить
		game::lose();
	}
}

void arsuhinars::field::moveTilesUp()
{
	bool hasAnyTileMoved = false;

	// Перемещаем все тайлы снизу вверх
	for (unsigned int y1 = 1; y1 < game::state.fieldSize; y1++) {
		for (unsigned int y = y1; y > 0; y--) {
			for (unsigned int x = 0; x < game::state.fieldSize; x++) {
				hasAnyTileMoved |= moveTile(
					Vector2u(x, y), Vector2u(x, y - 1)
				);
			}
		}
	}

	if (hasAnyTileMoved) {
		spawnTile();
	}
}

void arsuhinars::field::moveTilesRight()
{
	bool hasAnyTileMoved = false;

	// Перемещаем все тайлы слева направо
	for (int x1 = game::state.fieldSize - 1; x1 >= 0; x1--) {
		for (unsigned int x = x1; x < game::state.fieldSize - 1; x++) {
			for (unsigned int y = 0; y < game::state.fieldSize; y++) {
				hasAnyTileMoved |= moveTile(
					Vector2u(x, y), Vector2u(x + 1, y)
				);
			}
		}
	}

	if (hasAnyTileMoved) {
		spawnTile();
	}
}

void arsuhinars::field::moveTilesDown()
{
	bool hasAnyTileMoved = false;

	// Перемещаем все тайлы снизу вверх
	for (int y1 = game::state.fieldSize - 1; y1 >= 0; y1--) {
		for (unsigned int y = y1; y < game::state.fieldSize - 1; y++) {
			for (unsigned int x = 0; x < game::state.fieldSize; x++) {
				hasAnyTileMoved |= moveTile(
					Vector2u(x, y), Vector2u(x, y + 1)
				);
			}
		}
	}

	if (hasAnyTileMoved) {
		spawnTile();
	}
}

void arsuhinars::field::moveTilesLeft()
{
	bool hasAnyTileMoved = false;

	// Перемещаем все тайлы справо налево
	for (unsigned int x1 = 1; x1 < game::state.fieldSize; x1++) {
		for (unsigned int x = x1; x > 0; x--) {
			for (unsigned int y = 0; y < game::state.fieldSize; y++) {
				hasAnyTileMoved |= moveTile(
					Vector2u(x, y), Vector2u(x - 1, y)
				);
			}
		}
	}

	if (hasAnyTileMoved) {
		spawnTile();
	}
}

bool arsuhinars::field::moveTile(sf::Vector2u from, sf::Vector2u to)
{
	auto nextPos = Vector2f(
		static_cast<float>(to.x),
		static_cast<float>(to.y)
	);
	auto nextTileIndex = getTileIndex(to.x, to.y);
	auto currTileIndex = getTileIndex(from.x, from.y);

	auto& nextTile = game::state.tilemap[nextTileIndex];
	auto& currTile = game::state.tilemap[currTileIndex];

	if (!currTile) {
		return false;
	}

	// Если тайл сверху пустой
	if (!nextTile) {
		// Перемещаем текущий тайл
		currTile->moveTo(nextPos);

		// Меняем их местами
		swap(
			nextTile,
			currTile
		);

		return true;
	}
	// Если номера тайлов совпадают
	else if (!nextTile->wasAlreadySummed && !currTile->wasAlreadySummed && nextTile->getValue() == currTile->getValue()) {
		// Перемещаем текущий тайл
		currTile->moveTo(nextPos);

		// Увеличиваем число тайла в 2 раза
		nextTile->setValue(nextTile->getValue() + 1);
		// Устанавливаем флаг
		nextTile->wasAlreadySummed = true;
		// Проигрываем анимацию
		nextTile->playAnimation(Tile::Animation::ChangeValue);

		deletingTiles.push_back(unique_ptr<Tile>());

		// Добавляем текущий тайл в список для удаления
		swap(
			game::state.tilemap[currTileIndex],
			deletingTiles.back()
		);

		// Добавляем игроку очки
		game::state.score += utils::findPowerOfTwo(nextTile->getValue());

		return true;
	}

	return false;
}

bool arsuhinars::field::isAnyTileMoving()
{
	for (auto& tile : game::state.tilemap) {
		if (tile && tile->isMoving()) {
			return true;
		}
	}

	return false;
}

bool arsuhinars::field::isThereAnyMove()
{
	for (unsigned int x = 0; x < game::state.fieldSize; x++) {
		for (unsigned int y = 0; y < game::state.fieldSize; y++) {
			auto& tile = game::state.tilemap[getTileIndex(x, y)];
			if (!tile) {
				// Если данный тайл пустой (игрок может сходить в него)
				return true;
			}

			// Проверяем соседние тайлы.
			// Возвращаем истину если тайл пустой или его число равно числу
			// данного тайла.
			// Тайлы слева и сверху нет смысла проверять, так как
			// они были уже проверенны в предыдущих итерациях

			if (x < game::state.fieldSize - 1) {
				auto& neighbor = game::state.tilemap[getTileIndex(x + 1, y)];
				if (!neighbor || neighbor->getValue() == tile->getValue()) {
					return true;
				}
			}

			if (y < game::state.fieldSize - 1) {
				auto& neighbor = game::state.tilemap[getTileIndex(x, y + 1)];
				if (!neighbor || neighbor->getValue() == tile->getValue()) {
					return true;
				}
			}
		}
	}
	return false;
}
