#pragma once
#include<vector>
#include<tuple>

#include"Block.h"

enum class FieldType {
	SPACE,
	O,
	T,
	S,
	Z,
	L,
	J,
	I,
	WALL
};

using field_vector = std::vector<FieldType>;

class Field {
private:
	int width;
	int height;
	field_vector fieldData;

	int pos(int x, int y) {
		return y * width + x;
	}

public:
	Field() {}
	Field(int width, int height);
	Field(int width, int height, field_vector&& fieldData);
	std::vector<int> check_should_erase_lines();
	field_vector erase_line(const std::vector<int>& lines);
	field_vector move_line(const std::vector<int>& lines);
	bool put_block_check(int x, int y, const Block& block);
	field_vector put_block(int x, int y, const Block& block);

	int get_width() const { return width; }
	int get_height() const { return height; }
	field_vector get_field_data() const { return fieldData; }

	void update_field(field_vector&& data) {
		fieldData = std::move(data);
	}
};

inline FieldType block_to_field(BlockType block) {
	switch (block)
	{
	case BlockType::NONE:
		return FieldType::SPACE;
	case BlockType::O:
		return FieldType::O;
	case BlockType::T:
		return FieldType::T;
	case BlockType::S:
		return FieldType::S;
	case BlockType::Z:
		return FieldType::Z;
	case BlockType::L:
		return FieldType::L;
	case BlockType::J:
		return FieldType::J;
	case BlockType::I:
		return FieldType::I;
	default:
		// 知らないブロックは空白になる
		return FieldType::SPACE;
	}
}
