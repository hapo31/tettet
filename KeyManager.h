#pragma once
#include <array>

class KeyManager {
public:
	static KeyManager& get_instance() {
		static KeyManager instance;
		return instance;
	}
	void update();
	int get_key_frames(int key);
private:
	std::array<char, 256> keybuf;
	std::array<int, 256> keyframes;

	KeyManager() {
		keyframes.fill(0);
	}
	KeyManager(const KeyManager&) = delete;
	KeyManager operator=(const KeyManager&) = delete;
};