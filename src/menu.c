#include <stdio.h>
#include <stdlib.h>

#include <slang.h>

#include "player.h"
#include "screen.h"
#include "menu.h"

void draw_main_menu(void)
{
	draw_window("Main Menu", 4, 5, 8, 40);
	
	SLsmg_gotorc(6, 7);  SLsmg_write_string("1. Create A New Character");
	SLsmg_gotorc(7, 7);  SLsmg_write_string("2. Load Save Game");
	SLsmg_gotorc(8, 7);  SLsmg_write_string("3. Exit Game");
	
	SLsmg_gotorc(10, 7); SLsmg_write_string("Your selection: ");
}
