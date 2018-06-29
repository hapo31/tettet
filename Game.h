#pragma once
#include "Field.h"
#include "Block.h"
#include "KeyManager.h"

class Game {
public:
	Game(): field(10, 20), activeBlock(BlockType::NONE), key(KeyManager::get_instance()) {
	}
	void init();
	void update();
private:

	int frames = 0;
	int block_x = 2;
	int block_y = 0;
	
	Field field;
	Field drawField;
	Block activeBlock;

	KeyManager& key;

	void key_process();
};