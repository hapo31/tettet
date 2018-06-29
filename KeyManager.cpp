#include <DxLib.h>
#include "KeyManager.h"

void KeyManager::update() {
	GetHitKeyStateAll(keybuf.data());

	for (int key = 0; key < keybuf.size(); ++key) {
		if (keybuf[key] == 1) {
			keyframes[key] += 1;
		}
		else {
			keyframes[key] = 0;
		}
	}
}

int KeyManager::get_key_frames(int key) {
	return keyframes[key];
}
