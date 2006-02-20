#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <slang.h>

#include "hacknslash.h"
#include "player.h"
#include "screen.h"
#include "utils.h"

void create_new_player(player *p)
{
	if (!p) return;
	
	draw_borders();
	draw_window("Create New Character", 5, 5, 11, 60);
	SLsmg_gotorc(6, 7);
	SLsmg_write_string("Name: ");
	
	p->name = calloc(255, sizeof(char));
	if (!p->name) {
		exit(1);
	}

	SLsmg_refresh();
	get_input(6, 13, p->name, 254);
	
	p->level    = 1;
	p->exp_cur  = 0;
	p->exp_next = 1000;
	
	srand(time(0));
	
	SLang_flush_input();
	do {
		SLsmg_gotorc(8,  7); SLsmg_write_string("                ");
		SLsmg_gotorc(9,  7); SLsmg_write_string("                ");
		SLsmg_gotorc(10, 7); SLsmg_write_string("                ");
		SLsmg_gotorc(11, 7); SLsmg_write_string("                ");
		SLsmg_gotorc(12, 7); SLsmg_write_string("                ");
		
		p->str  = rand() % 10 + 1;
		p->end  = rand() % 10 + 1;
		p->intl = rand() % 10 + 1;
		p->wil  = rand() % 10 + 1;
		p->spd  = rand() % 10 + 1;
		
		SLsmg_gotorc(8,  7); SLsmg_printf("STR: %d", p->str);
		SLsmg_gotorc(9,  7); SLsmg_printf("END: %d", p->end);
		SLsmg_gotorc(10, 7); SLsmg_printf("INT: %d", p->intl);
		SLsmg_gotorc(11, 7); SLsmg_printf("WIL: %d", p->wil);
		SLsmg_gotorc(12, 7); SLsmg_printf("SPD: %d", p->spd);
		
		SLsmg_gotorc(14, 7); SLsmg_write_string("Press any key to reroll, or enter to keep the above.");
		
		SLsmg_refresh();
	} while (SLkp_getkey() != '\r');

	p->x = 100;
	p->y = 100;
	
	recalculate_stats(p);
}

void recalculate_stats(player *p)
{
	p->hp_cur = p->end * p->level;
	p->hp_max = p->end * p->level;
	p->mp_cur = p->end * p->level;
	p->mp_max = p->end * p->level;
	
	p->exp_next = ceil(p->exp_cur * 1.25);
}
