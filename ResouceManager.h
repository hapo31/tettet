#pragma once
#include <DxLib.h>
#include <unordered_map>
#include <string>

class ResouceManager {
public:
	static ResouceManager& get_instance() {
		static ResouceManager instance;
		return instance;
	}

	bool load(int id, const std::string& path) {
		int handle = LoadGraph(("data/" + path).c_str());
		if (handle != -1) {
			handles.emplace(id, handle);
			return true;
		}
		else {
			return false;
		}
	}

	int operator[](int id) const {
		return handles.at(id);
	}

private:
	ResouceManager() {}
	ResouceManager(const ResouceManager& rValue) = delete;
	void operator=(const ResouceManager& rValue) = delete;

	std::unordered_map<int, int> handles;

};