#ifndef __MONSTER_H_
#define __MONSTER_H_

#define MONSTER_COUNT 10

typedef struct monster_t {
	char *name;
	
	int hp_cur;
	int hp_max;
	int mp_cur;
	int mp_max;
	
	int str;
	
	// Map coordinates
	int x;
	int y;
} monster;

extern monster g_monsters[MONSTER_COUNT];

void init_monsters(int num);
void update_monsters();

#endif // __MONSTER_H_
