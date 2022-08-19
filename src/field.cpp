#include <algorithm>
#include "game.h"
#include "field.h"
#include "rounded_rect.h"
#include "utils.h"

using namespace std;
using namespace sf;
using namespace arsuhinars;

static ConvexShape panel;						// ��������
static vector<Tile> emptyTiles;					// ������ ������ ������
static vector<unique_ptr<Tile>> deletingTiles;	// �����, ������� ������ ����� ���� ��������

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
		// ������������� ����
		game::state.tilemap.clear();
		game::state.tilemap.resize(tilesCount);

		// ������� ��� ����� � ������ ����
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

	// ������� ��������
	auto panelSize = game::fieldRect.width * (1.0f - game::theme.panelMargin * 2);

	panel = createRoundedRect(
		Vector2f(panelSize, panelSize),
		panelSize * game::theme.panelRounding
	);
	panel.setPosition(
		Vector2f(
			static_cast<float>(game::fieldRect.left), 
			static_cast<float>(game::fieldRect.top)) +
		static_cast<float>(game::theme.panelMargin * game::fieldRect.width) * Vector2f(1.0f, 1.0f)
	);
	panel.setFillColor(game::theme.panelColor);
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
			// ���������� ����
			tile->wasAlreadySummed = false;
		}
	}
}

void arsuhinars::field::spawnTile()
{
	static vector<unsigned int> freeTilesIndexes;

	freeTilesIndexes.clear();

	// ������� ��������� ������� ��� ������
	for (size_t i = 0; i < game::state.tilemap.size(); i++) {
		if (!game::state.tilemap[i]) {
			freeTilesIndexes.push_back(static_cast<unsigned int>(i));
		}
	}

	if (freeTilesIndexes.size() == 0) {
		return;
	}

	// �������� ��������� ������
	unsigned int nextTileIndex = freeTilesIndexes[
		static_cast<size_t>(utils::randomRange(0, static_cast<int>(freeTilesIndexes.size())))
	];

	auto tilePos = getTilePos(nextTileIndex);

	// ������� ����
	game::state.tilemap[nextTileIndex] = make_unique<Tile>(
		Vector2f(
			static_cast<float>(tilePos.x),
			static_cast<float>(tilePos.y)
		),
		utils::random() < 0.9f ? 1 : 2	// ���� ������ ������ - 90%, �������� - 10%
	);
	game::state.tilemap[nextTileIndex]->
		playAnimation(Tile::Animation::Appear);
}

void arsuhinars::field::moveTilesUp()
{
	bool hasAnyTileMoved = false;

	// ���������� ��� ����� ����� �����
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

	// ���������� ��� ����� ����� �������
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

	// ���������� ��� ����� ����� �����
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

	// ���������� ��� ����� ������ ������
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

	// ���� ���� ������ ������
	if (!nextTile) {
		// ���������� ������� ����
		currTile->moveTo(nextPos);

		// ������ �� �������
		swap(
			nextTile,
			currTile
		);

		return true;
	}
	// ���� ������ ������ ���������
	else if (!nextTile->wasAlreadySummed && !currTile->wasAlreadySummed && nextTile->getValue() == currTile->getValue()) {
		// ���������� ������� ����
		currTile->moveTo(nextPos);

		// ����������� ����� ����� � 2 ����
		nextTile->setValue(nextTile->getValue() + 1);
		// ������������� ����
		nextTile->wasAlreadySummed = true;
		// ����������� ��������
		nextTile->playAnimation(Tile::Animation::ChangeValue);

		deletingTiles.push_back(unique_ptr<Tile>());

		// ��������� ������� ���� � ������ ��� ��������
		swap(
			game::state.tilemap[currTileIndex],
			deletingTiles.back()
		);

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
