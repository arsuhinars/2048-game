#include <sstream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "field.h"
#include "game_state.h"
#include "utils.h"

using namespace std;
using namespace sf;

void arsuhinars::GameState::save()
{
	utils::IniFile file;

	file["fieldSize"] = to_string(fieldSize);
	
	stringstream tilemapStream;
	for (auto& tile : tilemap) {
		tilemapStream << (tile ? tile->getValue() : 0U) << " ";
	}
	file["tilemap"] = tilemapStream.str();

	utils::saveIni(SAVE_FILE_NAME, file);
}

void arsuhinars::GameState::load()
{
	auto file = utils::readIni(SAVE_FILE_NAME);

	if (file.find("fieldSize") == file.end() ||
		file.find("tilemap") == file.end()) {
		return;
	}

	int fieldSize = stoi(file["fieldSize"]);
	if (fieldSize <= 0) {
		return;
	}

	GameState::fieldSize = static_cast<unsigned int>(fieldSize);

	tilemap.clear();
	tilemap.reserve(static_cast<size_t>(fieldSize * fieldSize));

	stringstream tilemapStream(file["tilemap"]);
	while (tilemapStream) {
		unsigned int tileValue;
		tilemapStream >> tileValue;
		if (tilemapStream.fail()) {
			break;
		}

		auto tilePos = Vector2f(
			static_cast<float>(tilemap.size() % fieldSize),
			static_cast<float>(tilemap.size() / fieldSize)
		);

		tilemap.push_back(
			tileValue > 0 ?
			make_unique<Tile>(tilePos, tileValue) :
			unique_ptr<Tile>()
		);
	}
}
