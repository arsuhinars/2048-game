#pragma once
#include <map>
#include <string>
#include "tile.h"

constexpr auto WINDOW_TITLE = "2048 Game";
const unsigned int WINDOW_WIDTH = 600;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int FRAMERATE_LIMIT = 60;
const unsigned int ANTIALIAZING_LEVEL = 4;

const unsigned int ROUNDED_RECT_CIRCLE_POINTS_COUNT = 6;

const unsigned int DEFAULT_FIELD_SIZE = 4;

const std::string SAVE_FILE_NAME = "save.ini";

const float TILE_TRANSITION_TIME = 0.1f;
const std::map<arsuhinars::Tile::Animation, float> TILE_ANIMATION_TIME = {
	{ arsuhinars::Tile::Animation::None, 0.0f },
	{ arsuhinars::Tile::Animation::Appear, 0.125f },
	{ arsuhinars::Tile::Animation::ChangeValue, 0.15f }
};
