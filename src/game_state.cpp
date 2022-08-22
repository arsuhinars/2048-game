#include <sstream>
#include <SFML/Graphics.hpp>
#include "config.h"
#include "game.h"
#include "field.h"
#include "game_state.h"
#include "utils.h"

using namespace std;
using namespace sf;

void arsuhinars::GameState::save()
{
	utils::IniFile file;

	file["windowWidth"] = to_string(game::window->getSize().x);
	file["windowHeight"] = to_string(game::window->getSize().y);
	file["fieldSize"] = to_string(fieldSize);
	file["isGameLost"] = isGameLost ? "true" : "false";
	file["score"] = to_string(score);
	file["record"] = to_string(record);
	
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

	auto widthIt = file.find("windowWidth");
	auto heightIt = file.find("windowHeight");
	if (widthIt != file.end() && heightIt != file.end()) {
		int windowWidth = stoi(widthIt->second);
		int windowHeight = stoi(heightIt->second);

		if (windowWidth > 0 && windowHeight > 0) {
			GameState::windowWidth = static_cast<unsigned int>(windowWidth);
			GameState::windowHeight = static_cast<unsigned int>(windowHeight);
		}
	}

	auto fieldSizeIt = file.find("fieldSize");
	auto tilesIt = file.find("tilemap");

	if (fieldSizeIt == file.end() || tilesIt == file.end()) {
		return;
	}

	int fieldSize = stoi(fieldSizeIt->second);
	if (fieldSize <= 0) {
		return;
	}

	GameState::fieldSize = static_cast<unsigned int>(fieldSize);

	tilemap.clear();
	tilemap.reserve(static_cast<size_t>(fieldSize * fieldSize));

	stringstream tilemapStream(tilesIt->second);
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

	auto isGameLostIt = file.find("isGameLost");
	if (isGameLostIt != file.end()) {
		isGameLost = isGameLostIt->second == "true";
	}

	auto scoreIt = file.find("score");
	if (scoreIt != file.end()) {
		score = static_cast<unsigned int>(stoi(scoreIt->second));
	}

	auto recordIt = file.find("record");
	if (recordIt != file.end()) {
		record = static_cast<unsigned int>(stoi(recordIt->second));
	}
}
