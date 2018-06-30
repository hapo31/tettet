#include "Game.h"
#include "ResouceManager.h"
#include "Draw.h"

void Game::init()
{

	auto& resource = ResouceManager::get_instance();
	resource.load((int)FieldType::O, "yellow.png");
	resource.load((int)FieldType::J, "blue.png");
	resource.load((int)FieldType::L, "orange.png");
	resource.load((int)FieldType::S, "green.png");
	resource.load((int)FieldType::Z, "red.png");
	resource.load((int)FieldType::T, "purple.png");
	resource.load((int)FieldType::I, "skyblue.png");
	resource.load((int)FieldType::WALL, "gray.png");

	activeBlock = Block(BlockType::NONE);

	drawField = field;
}


void Game::update() {
	if (activeBlock == BlockType::NONE) {
		block_x = 2;
		block_y = 0;
		activeBlock = Block((BlockType)GetRand(1 + int(BlockType::MAX) - 2));
	}

	key_process();

	if (frames != 0 && frames % 30 == 0) {
		if (field.put_block_check(block_x, block_y + 1, activeBlock)) {
			drawField = std::move(Field(field.get_width(), field.get_height(), field.put_block(block_x, block_y + 1, activeBlock)));
			++block_y;
		}
		else {
			// çsÇè¡Ç∑
			const auto should_erase = drawField.check_should_erase_lines();
			if (!should_erase.empty()) {
				auto new_field = drawField.erase_line(should_erase);
				field.update_field(std::move(new_field));
				field.update_field(std::move(field.move_line(should_erase)));
			}
			else {
				field.update_field(std::move(drawField.get_field_data()));
			}


			activeBlock = Block(BlockType::NONE);
		}
	}


	DrawField(200, 64, drawField);

	++frames;
}

void Game::key_process() {
	key.update();

	int result_x = block_x;
	int result_y = block_y;
	bool hasInput = false;

	if (key.get_key_frames(KEY_INPUT_RIGHT) == 1) {
		if (field.put_block_check(block_x + 1, block_y, activeBlock)) {
			result_x = block_x + 1;
			hasInput = true;
		}
	}
	if (key.get_key_frames(KEY_INPUT_LEFT) == 1) {
		if (field.put_block_check(block_x - 1, block_y, activeBlock)) {
			result_x = block_x - 1;
			hasInput = true;
		}
	}

	if (key.get_key_frames(KEY_INPUT_Z) == 1) {
		Block block(std::move(activeBlock.rotate(RotateDir::LEFT)));
		if (field.put_block_check(block_x, block_y, block)) {
			activeBlock = std::move(block);
			hasInput = true;
		}
	}

	if (key.get_key_frames(KEY_INPUT_X) == 1) {
		Block block(std::move(activeBlock.rotate(RotateDir::RIGHT)));
		if (field.put_block_check(block_x, block_y, block)) {
			activeBlock = std::move(block);
			hasInput = true;
		}
	}

	if (key.get_key_frames(KEY_INPUT_DOWN) == 1) {
		++result_y;
		hasInput = true;
	}

	if (hasInput) {
		block_x = result_x;
		block_y = result_y;
		drawField = std::move(Field(field.get_width(), field.get_height(), field.put_block(result_x, result_y, activeBlock)));
	}
}
