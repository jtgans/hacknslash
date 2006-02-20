#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <slang.h>

#include "hacknslash.h"
#include "player.h"
#include "map.h"
#include "screen.h"
#include "monster.h"

void draw_borders(void)
{
	SLsmg_cls();

	SLsmg_gotorc(1, 0);
	SLsmg_draw_hline(79);
	
	SLsmg_gotorc(22, 0);
	SLsmg_draw_hline(79);
	
	SLsmg_gotorc(0, 0);
	SLsmg_write_string("Hack 'N Slash");
}

void update_status(player p)
{
	SLsmg_gotorc(22, 2);  SLsmg_printf("[ %s - Normal ]", p.name);
	SLsmg_gotorc(23, 1);  SLsmg_printf("Level <%2d>", p.level);
	SLsmg_gotorc(23, 15); SLsmg_printf("HP <%4d/%4d>", p.hp_cur, p.hp_max);
	SLsmg_gotorc(23, 32); SLsmg_printf("MP <%4d/%4d>", p.mp_cur, p.mp_max);
	
	SLsmg_gotorc(22, 78 - (strlen(g_current_map->name) + 4));
	SLsmg_printf("[ %s ]", g_current_map->name);
}

void update_screen(player p)
{
	int i, x, y;
	int map_x, map_y;
	char ch;

	// First thing's first -- clear off the screen.
	for (i=2; i<22; i++) {
		SLsmg_gotorc(i, 0);
		SLsmg_erase_eol();
	}

	// Now that we know the player is in the middle,
	// we have to use the player's coordinates as a kind of reference point
	// as to how we draw the map.
	// 
	// Our viewport is ((row, column)) (2, 0)-(22, 79), so we'll setup
	// a pair of loops that just loop through the map data
	// checking to see if we're in bounds of the actual map (don't draw
	// anything there at all) before we draw anything (thereby preventing
	// a segfault)
	
	for (x=0; x<=MAPSCREEN_WIDTH; x++) {
		for (y=0; y<=MAPSCREEN_HEIGHT; y++) {
			map_x = x - 39 + p.x;
			map_y = y - 10 + p.y;
			
			if ((map_x < 0) ||
			    (map_x > (g_current_map->width - 1)) ||
			    (map_y < 0) ||
			    (map_y > (g_current_map->height - 1))) {
				ch = '#';
			} else {
				switch (g_current_map->data[map_x + (map_y * g_current_map->width)]) {
				case '#':
					ch = '#';
					break;
						
				case 0:
					ch = ' ';
					break;
						
				case '.':
					ch = '.';
					break;
					
				default:
					ch = '?';
					break;
				}

                // Run through the list of monsters and see if there's
                // one there. If so, draw that instead of the usual
                // space.

                for (i=0; i<MONSTER_COUNT; i++) {
                    if ((g_monsters[i].x == map_x) &&
                        (g_monsters[i].y == map_y)) {
                        ch = g_monsters[i].str;
                    }
                }
			}
			
			SLsmg_gotorc(y + 2, x);
			SLsmg_write_char(ch);
		}
	}

	// Only the map moves -- the player is stationary at the center
	// of the screen. Don't like it? Too bad. I don't like having to
	// redraw parts of the screen in bizarre ways. =op
	SLsmg_gotorc(12, 39); SLsmg_write_char('@');
}

void draw_window(char *title, int x, int y, int w, int h)
{
	SLsmg_draw_box(x, y, w, h);
	
	SLsmg_gotorc(x, y + 2);
	SLsmg_write_string("[ ");
	SLsmg_write_string(title);
	SLsmg_write_string(" ]");
}

void display_message(char *msg, int clear)
{
	char *tok;
	
	if (!msg) return;
	if (strlen(msg) < 1) return;
	if (g_last_message != NULL) free(g_last_message);
	
	g_last_message = strdup(msg);

	tok = strtok(g_last_message, "\n");
	while (tok != NULL) {
		SLsmg_gotorc(0, 0);
		SLsmg_erase_eol();
		SLsmg_write_string(tok);
		SLsmg_gotorc(1, 71);
		SLsmg_write_string("[ More ]");

		SLsmg_refresh();
		
		SLkp_getkey();
		tok = strtok(NULL, "\n");
	}

	if (clear) {
		SLsmg_gotorc(0, 0);
		SLsmg_erase_eol();
	}
	
	SLsmg_gotorc(1, 0);
	SLsmg_draw_hline(79);
}
