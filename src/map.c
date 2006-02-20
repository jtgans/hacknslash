#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <slang.h>

#include "hacknslash.h"
#include "map.h"

map *g_current_map = NULL;

void destroy_map()
{
	if (g_current_map != NULL) {
		free(g_current_map->name);
		free(g_current_map->data);
		free(g_current_map);
		g_current_map = NULL;
	}
}

int can_move_to(int x, int y)
{
    if (g_current_map->data[y * g_current_map->width + x] != '.') {
        return 0;
    } else {
        return 1;
    }
}

void create_new_map(char *title, int w, int h)
{
	if (g_current_map != NULL) destroy_map();
	
	g_current_map = calloc(1, sizeof(map));
	
	g_current_map->name = strdup(title);
	g_current_map->width = w;
	g_current_map->height = h;
	g_current_map->data = calloc(w * h, sizeof(int));
}

void create_room(int x_pos, int y_pos, int width, int height)
{
	int i, j, x, y, w, h;
	int pos;
	
	x = x_pos;
	y = y_pos;
	w = width;
	h = height;
        
	for (i=x; i<x+w-1; i++) {
		pos = i + (y * g_current_map->width);
		g_current_map->data[pos] = '#';
		
		pos = i + ((y + h - 1) * g_current_map->width);
		g_current_map->data[pos] = '#';
	}
	
	for (i=y; i<y+h; i++) {
		pos = x + (i * g_current_map->width);
		g_current_map->data[pos] = '#';
		
		pos = x + (i * g_current_map->width + h - 1);
		g_current_map->data[pos] = '#';
	}
	
	for (i=x+1; i<x+w-1; i++) {
		for (j=y+1; j<y+h-1; j++) {
			pos = i + (j * g_current_map->width);
			g_current_map->data[pos] = '.';
		}
	}
}
