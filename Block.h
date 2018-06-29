#pragma once
#include <array>

enum class BlockType {
	NONE,
	O,
	T,
	S,
	Z,
	L,
	J,
	I,

	MAX
};

enum class RotateDir {
	RIGHT, LEFT
};

class Block {

public:
	static constexpr int block_size = 4;
	static constexpr int block_data_size = Block::block_size * Block::block_size;

	using block_array = std::array<BlockType, block_data_size>;

	Block(BlockType type);
	Block(block_array&& data);
	block_array rotate(RotateDir dir) const;
	void updateBlock(block_array&& data) {
		blockData = std::move(data);
	}

	BlockType operator[](int pos) const { return blockData[pos]; }
	block_array decode_block(BlockType type);

	bool operator==(BlockType type) const { return myType == type; }

private:
	BlockType myType;

	block_array blockData;

};
