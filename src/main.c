#include <raylib.h>

#include "ui.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define META_STATE_TRANSITION_DURATION_SECONDS 0.5

typedef enum {
	TITLE_SCREEN,
	GAME,
} MetaState;

typedef struct {
	Button play_button;
	Button exit_button;

	Color background_color;
} TitleScreen;

typedef struct { // combine with TitleScreen into union?
	Color background_color;
} Game;

int main(void)
{
	MetaState meta_state = TITLE_SCREEN;

	TitleScreen title_screen = {
		.play_button = {
			.text = "PLAY",

			.center_position_x = WINDOW_WIDTH / 2,
			.center_position_y = WINDOW_HEIGHT / 2,
			.width = 200,
			.height = 100,

			.background_color = RED,
			.text_color = WHITE,
		},
		.exit_button = {
			.text = "EXIT",

			.center_position_x = WINDOW_WIDTH / 2,
			.center_position_y = WINDOW_HEIGHT / 2 + 150,
			.width = 200,
			.height = 100,

			.background_color = RED,
			.text_color = WHITE,
		},

		.background_color = BLUE,
	};

	Game game = {
		.background_color = GREEN,
	};

	SetConfigFlags(FLAG_MSAA_4X_HINT); // antialiasing (needs to be called before InitWindow())

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Iron Siege");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		switch (meta_state) {
		case TITLE_SCREEN:
			if (buttonIsReleased(title_screen.play_button))
				meta_state = GAME;

			if (buttonIsReleased(title_screen.exit_button))
				goto exit;

			ClearBackground(title_screen.background_color);
			buttonDraw(title_screen.play_button);
			buttonDraw(title_screen.exit_button);

			break;

		case GAME:
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				meta_state = TITLE_SCREEN;

			ClearBackground(game.background_color);

			break;
		}

		EndDrawing();
	}

exit:
	CloseWindow();
	return 0;
}
