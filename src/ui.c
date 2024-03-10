#include "ui.h"

bool buttonIsReleased(Button button)
{
	return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && buttonIsMouseHovering(button);
}

bool buttonIsMouseHovering(Button button)
{
	return CheckCollisionPointRec(GetMousePosition(), (Rectangle) {
		.x = button.center_position_x - button.width / 2,
		.y = button.center_position_y - button.height / 2,
		.width = button.width,
		.height = button.height,
	});
}

void buttonDraw(Button button)
{
	uint16_t width = button.width;
	uint16_t height = button.height;

	if (buttonIsMouseHovering(button)) {
		width = 4 * width / 3;
		height = 4 * height / 3;
	}

	Color alpha_background_color = button.background_color;
	Color alpha_text_color = button.text_color;

	alpha_background_color.a *= (1 - button.transition_fraction);
	alpha_text_color.a *= (1 - button.transition_fraction);

	DrawRectangle(button.center_position_x - width / 2, button.center_position_y - height / 2, width, height, alpha_background_color);

#define FONT_SIZE (height / 2)
	DrawText(button.text, button.center_position_x - MeasureText(button.text, FONT_SIZE) / 2, button.center_position_y - FONT_SIZE / 2, FONT_SIZE, button.text_color);
#undef FONT_SIZE
}

static float lerpFloat(float initial_float, float final_float, float fraction)
{
	return (1 - fraction) * initial_float + fraction * final_float;
}

Color lerpColor(Color initial_color, Color final_color, float fraction)
{
	return (Color) {
		.r = lerpFloat(initial_color.r, final_color.r, fraction),
		.g = lerpFloat(initial_color.g, final_color.g, fraction),
		.b = lerpFloat(initial_color.b, final_color.b, fraction),
		.a = lerpFloat(initial_color.a, final_color.a, fraction),
	};
}
