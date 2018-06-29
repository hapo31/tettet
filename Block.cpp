#include "Block.h"


const int block_sources[int(BlockType::MAX)][10][2] = {
	// NONE
	{},
	// O
	{
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 }
	},
	// T
	{
		{ -1, 0 },
		{ 0, -1 },
		{ 1, 0 }
	},
	// S
	{
		{ 0, -1 },
		{ -1, 0 },
		{ 1, -1 }
	},
	// Z
	{
		{ 0, 1 },
		{ 1, 0 },
		{ -1, 1 },
	},
	// L
	{
		{ -1, 0 },
		{ 1, 0 },
		{ -1, 1 }
	},
	// J
	{
		{ -1, 0 },
		{ 1, 0 },
		{ 1, 1 }
	},
	// I
	{
		{ 2, 0 },
		{ -1, 0 },
		{ 1, 0 }
	},
};

Block::Block(BlockType type): myType(type), blockData(std::move(decode_block(type))) {
}

Block::Block(block_array && data): blockData(std::move(data)) {}

Block::block_array Block::rotate(RotateDir dir) const
{
	block_array result;
	const int sin = dir == RotateDir::RIGHT ? -1 : 1;
	for (int y = 0; y < block_size; ++y) {
		for (int x = 0; x < block_size; ++x) {
			// ��]�s��̌v�Z��90�x�܂���-90�x��]�����Ƃ��̍��W�����߂�
			int rotated_x = -y * sin
				+ (dir == RotateDir::LEFT ? block_size - 1 : 0);
			int rotated_y = x * sin
				+ (dir == RotateDir::RIGHT ? block_size - 1: 0);
			// ���Ԃ񂱂�ŉ��񂶂�Ȃ��ł�����
			result[rotated_y * block_size + rotated_x] = blockData[y * block_size + x];
		}
	}

	return result;
}

Block::block_array Block::decode_block(BlockType type) {
	Block::block_array data;
	data.fill(BlockType::NONE);
	for (auto&& point : block_sources[int(type)]) {
		// ���S�_��4*4�̃}�g���b�N�X�̍��W(2,2)�Ƃ���
		int x = 2 - point[0];
		int y = 2 - point[1];
		data[y * Block::block_size + x] = type;
	}

	// ���S�𖄂߂�
	data[Block::block_data_size / 2 + 2] = type;

	return data;
}
