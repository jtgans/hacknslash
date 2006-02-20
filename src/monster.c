#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <slang.h>

#include "hacknslash.h"
#include "monster.h"

monster g_monsters[MONSTER_COUNT];

void init_monsters(int num)
{
    int i;
    
    for (i=0; i<num; i++) {
        g_monsters[i].name = strdup("google-eyed bat");
        g_monsters[i].hp_cur = 5;
        g_monsters[i].hp_max = 5;
        g_monsters[i].mp_cur = 0;
        g_monsters[i].mp_max = 0;
        g_monsters[i].str = '%';
        g_monsters[i].x = 35;
        g_monsters[i].y = 35;
    }
}

void update_monsters()
{
}
