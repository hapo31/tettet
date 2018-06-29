
#include "Field.h";

Field::Field(int width, int height) : width(width), height(height) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			// �ǂ����
			if (x == 0 || x == width - 1 || y == height - 1) {
				fieldData.emplace_back(FieldType::WALL);
			}
			else {
				fieldData.emplace_back(FieldType::SPACE);
			}
		}
	}
}

Field::Field(int width, int height, field_vector&& fieldData): width(width), height(height), fieldData(std::move(fieldData)) {
}

// ������s���L�^����
std::vector<int> Field::check_should_erase_lines() {
	std::vector<int> eraseLines;
	for (int y = 0; y < height - 1; ++y) {
		bool isRowFilled = true;
		for (int x = 1; x < width - 1; ++x) {
			if (fieldData[pos(x, y)] == FieldType::SPACE) {
				isRowFilled = false;
				break;
			}
		}

		if (isRowFilled) {
			eraseLines.emplace_back(y);
		}
	}

	return eraseLines;
}

field_vector Field::erase_line(const std::vector<int>& lines) {
	auto tempField = fieldData;
	for (auto&& erase_y : lines) {
		// �w��s������
		for (int x = 1; x < width - 1; ++x) {
			tempField[pos(x, erase_y)] = FieldType::SPACE;
		}
	}

	return tempField;
}

field_vector Field::move_line(const std::vector<int>& lines) {
	auto tempField = fieldData;
	int moved = 0;
	for (auto&& erase_y : lines) {
		// �������s�����炷
		for (int y = erase_y; y > 1; --y) {
			for (int x = 1; x < width - 1; ++x) {
				tempField[pos(x, y)] = tempField[pos(x, y - 1)];
			}
		}
		for (int x = 0; x < width; ++x) {
			if (x == 0 || x == width - 1) {
				tempField[x] = FieldType::WALL;
			}
			else {
				tempField[x] = FieldType::SPACE;
			}
		}
		++moved;
	}


	return tempField;
}

bool Field::put_block_check(int posx, int posy, const Block& block) {
	for (int origin_y = 0, y = posy; y < posy + Block::block_size && y < height; ++y, ++origin_y) {
		for (int origin_x = 0, x = posx; x < posx + Block::block_size && x < width; ++x, ++origin_x) {
			if (x < 0 || y < 0) {
				continue;
			}
			// �t�B�[���h��(x, y)���󔒂łȂ��A�u���b�N��(origin_x, origin_y)���󔒂łȂ��Ƃ��A�u���b�N�͒u���Ȃ�
			if (fieldData[pos(x, y)] != FieldType::SPACE && block[origin_y * 4 + origin_x] != BlockType::NONE) {
				return false;
			}
		}
	}
	return true;
}

field_vector Field::put_block(int posx, int posy, const Block& block) {
	auto tempField = fieldData;
	for (int origin_y = 0, y = posy; y < posy + Block::block_size && y < height; ++y, ++origin_y) {
		for (int origin_x = 0, x = posx; x < posx + Block::block_size && x < width; ++x, ++origin_x) {
			if (x < 0 || y < 0 || block[origin_y * Block::block_size + origin_x] == BlockType::NONE) {
				continue;
			}
			// �`�F�b�N�͏I����Ă���̂Ƃ��Ēu��
			tempField[pos(x, y)] = block_to_field(block[origin_y * Block::block_size + origin_x]);
		}
	}

	return tempField;
}
