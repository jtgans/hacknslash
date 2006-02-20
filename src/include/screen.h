#ifndef __SCREEN_H_
#define __SCREEN_H_

#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 25

#define MAPSCREEN_WIDTH  79
#define MAPSCREEN_HEIGHT 19

void draw_borders(void);
void update_status(player p);
void draw_main_menu(void);
void update_screen(player p);
void draw_window(char *title, int x, int y, int w, int h);
void display_message(char *msg, int clear);

#endif //__SCREEN_H_
