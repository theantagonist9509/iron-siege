#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include <stdint.h>

#include <raylib.h>

typedef struct {
	char *text;

	uint16_t center_position_x;
	uint16_t center_position_y;
	uint16_t width;
	uint16_t height;

	Color background_color;
	Color text_color;

	float transition_fraction; // implement transitions later
} Button;

bool buttonIsReleased(Button button);
bool buttonIsMouseHovering(Button button);
void buttonDraw(Button button);

Color lerpColor(Color initial_color, Color final_color, float fraction);

#endif
