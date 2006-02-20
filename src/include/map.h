#ifndef __MAP_H_
#define __MAP_H_

#define MAP_EMPTY	0
#define MAP_WALL	1
#define MAP_DOOR	2
#define MAP_MONSTER	3
#define MAP_ITEM	4
#define MAP_SCROLL	5
#define MAP_PLAYER	6

typedef struct map_t {
	char *name;
	int *data; // actually it's two chars [type][parameters]
	int width;
	int height;
} map;

extern map *g_current_map;

void create_room(int x_pos, int y_pos, int width, int height);
int can_move_to(int x, int y);
void create_new_map(char *title, int w, int h);
void destroy_map();

#endif // __MAP_H_
