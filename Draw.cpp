#include <DxLib.h>
#include "Draw.h"
#include "ResouceManager.h"

constexpr int GRAPHIC_SIZE = 32;

void DrawField(int draw_origin_x, int draw_origin_y, const Field& field) {

	ClearDrawScreen();

	const auto fieldData = field.get_field_data();
	const int width = field.get_width();
	const int height = field.get_height();
	const auto& res = ResouceManager::get_instance();

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			const auto data = fieldData[y * width + x];
			if (data == FieldType::SPACE) {
				continue;
			}
			DrawRectGraph(draw_origin_x + x * GRAPHIC_SIZE, draw_origin_y + y * GRAPHIC_SIZE,0, 0, GRAPHIC_SIZE, GRAPHIC_SIZE, res[(int)data], false);
		}
	}

	ScreenFlip();
}