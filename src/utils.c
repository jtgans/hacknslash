#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <slang.h>

#include "hacknslash.h"
#include "utils.h"

int get_input(int x, int y, char *buf, int len)
{
	int count;
	int ch;
	int i;
	
	ch = 0;
	count = 0;

	buf[0] = '\0';

	SLang_flush_input();
	
	while (1) {
		ch = SLkp_getkey();
		
		switch (ch) {
		case SL_KEY_BACKSPACE:
			if (count > 0) {
				count--;
				buf[count] = '\0';
			}
			break;
			
		case '\r':
		case SL_KEY_ENTER:
			return count;
			break;
			
		default:
			if ((ch < 256) && (count < len)) {
				buf[count] = ch;
				count++;
			}
			break;
		}
		
		SLsmg_gotorc(x, y);
		for (i=0; i<count; i++) {
			SLsmg_write_char(buf[i]);
		}
		SLsmg_write_char(' ');
		SLsmg_gotorc(x, y + count);
		SLsmg_refresh();
	}
}
