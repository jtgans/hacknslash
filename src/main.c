#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <slang.h>

#include "hacknslash.h"
#include "map.h"
#include "monster.h"
#include "player.h"
#include "screen.h"
#include "slangfun.h"
#include "utils.h"
#include "menu.h"

int g_game_mode = MODE_MAINMENU;
char *g_last_message = NULL;

void main_menu(void)
{
	int valid_selection = 0;
	int num_chars = 0;
	char buf[2];
	
	draw_borders();
	draw_main_menu();
	SLsmg_refresh();

	do {
		do {
			num_chars = get_input(10, 23, buf, 1);
		} while (num_chars == 0);
		
		switch (buf[0]) {
		case '1':
			g_game_mode = MODE_CREATENEW;
			valid_selection = 1;
			break;
			
		case '2':
			// Not a valid selection until we can actually play a game. =op
			break;
			
		case '3':
			g_game_mode = MODE_QUIT;
			valid_selection = 1;
			break;
		}
	} while (!valid_selection);
	
	return;
}

int main(void)
{
	int ch;
	player p;
	
	// Initialization
	initialize_slang();

	// Game mode
	while (g_game_mode != MODE_QUIT) {
		switch (g_game_mode) {
		case MODE_MAINMENU:
			main_menu();
			break;
			
		case MODE_PLAYGAME:
			draw_borders();
			update_status(p);
            			
			do {
				update_screen(p);
				SLsmg_refresh();
				
				ch = SLkp_getkey();
				
				switch (ch) {
                    case SL_KEY_UP:
                        if (can_move_to(p.x, p.y - 1)) p.y--;
                        break;
                        
                    case SL_KEY_DOWN:
                        if (can_move_to(p.x, p.y + 1)) p.y++;
                        break;
					
                    case SL_KEY_LEFT:
                        if (can_move_to(p.x - 1, p.y)) p.x--;
                        break;
                        
                    case SL_KEY_RIGHT:
                        if (can_move_to(p.x + 1, p.y)) p.x++;
                        break;
                        
                    case 'q':
                    case 'Q':
                        g_game_mode = MODE_QUIT;
                        break;
				}
			} while (g_game_mode != MODE_QUIT);
			break;
			
		case MODE_CREATENEW:
			create_new_player(&p);
			create_new_map("The Dungeons of Moria", 102, 102);
			create_room(25, 25, 50, 50);
			
			p.x = 50;
			p.y = 50;

            init_monsters(1);
			
			g_game_mode = MODE_PLAYGAME;
			break;
			
		case MODE_QUIT:
			destroy_map();
			break;
		}
	}
		
	return 0;
}
