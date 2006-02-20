#ifndef __PLAYER_H_
#define __PLAYER_H_

typedef struct player_t {
	char *name;
	int level;
	int exp_cur;
	int exp_next;
	
	int hp_cur;
	int hp_max;
	int mp_cur;
	int mp_max;
	
	int str; 	// carrying weight and melee weapon damage
	int end;	// endurance (max hp)
	int intl;	// chance of spell failing, spell effect magnitude
	int wil;	// chance of resisting spell effect (poison, etc) and the max mp
	int spd;	// speed of movement and attack

	int x;
	int y;
	
//	spell_list *spells;
//	inventory_list *inventory;
} player;

void create_new_player(player *p);
void recalculate_stats(player *p);

#endif // __PLAYER_H_
