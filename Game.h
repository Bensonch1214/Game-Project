#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro.h>
#include "UI.h"

/**
 * @brief Main class that runs the whole game.
 * @details All game procedures must be processed through this class.
 */
class Game
{
public:
	void execute();
public:
	Game();
	~Game();
	void game_init();
	bool game_update();
	void game_draw();
private:
	/**
	 * @brief States of the game process in game_update.
	 * @see Game::game_update()
	 */
	enum class STATE {
		START, // -> LEVEL
		LEVEL, // -> PAUSE, END
		PAUSE, // -> LEVEL
		END,
		MENU, // ->start
		GUIDE,
		STORY,
		SETTING
	};
	enum class MENU_SELECT_MODE {
		MIN_BOUND,
		START, // -> LEVEL
		GUIDE, // -> MENU
		STORY, // -> MENU
		SETTING,
		QUIT, // 
		MAX_BOUND
	};
	int mode; //for setting easy/hard
	STATE state;
	MENU_SELECT_MODE select;
	ALLEGRO_EVENT event;
	ALLEGRO_BITMAP *game_icon;
	ALLEGRO_BITMAP *background;

	// ALLEGRO_BITMAP *select_box; //1 no, 2 choose
	ALLEGRO_BITMAP *start_box0, *start_box1;
	ALLEGRO_BITMAP *guide_box0, *guide_box1;
	ALLEGRO_BITMAP *story_box0, *story_box1;
	ALLEGRO_BITMAP *setting_box0, *setting_box1;
	ALLEGRO_BITMAP *quit_box0,  *quit_box1;


private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *event_queue;
	UI *ui;
};

#endif
