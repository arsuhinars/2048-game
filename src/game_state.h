#pragma once
#include <memory>
#include <vector>
#include "tile.h"
#include "config.h"

namespace arsuhinars
{
	// ��������� ��������� ����
	struct GameState
	{
		// ������ ���� ����
		unsigned int fieldSize = DEFAULT_FIELD_SIZE;

		// ������ ���� ������ �� ����, ��� ���� - ������� ������
		std::vector<std::unique_ptr<Tile>> tilemap;

		// ����� ���������� ���������
		void save();
		// ����� �������� ��������� �� �����
		void load();
	};
}
