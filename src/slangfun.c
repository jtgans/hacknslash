#include <stdio.h>
#include <stdlib.h>

#include <slang.h>

#include "hacknslash.h"
#include "utils.h"
#include "slangfun.h"
#include "map.h"

void shutdown_slang(void)
{
	SLsmg_reset_smg();
	SLang_reset_tty();
}

void initialize_slang(void)
{
	SLtt_get_terminfo();
	
	if (SLkp_init() == -1) {
		SLang_doerror("SLkp_init failed.");
		exit(1);
	}
	
	if (SLang_init_tty(-1, 0, 0) == -1) {
		SLang_doerror("SLang_init_tty failed.");
		exit(1);
	}
	
	if (SLsmg_init_smg() == -1) {
		SLang_doerror("SLsmg_init_smg() failed.");
		exit(1);
	}

	SLadd_intrinsic_function("create_room", (FVOID_STAR) create_room, SLANG_VOID_TYPE, 4,
				 SLANG_INT_TYPE, SLANG_INT_TYPE, SLANG_INT_TYPE, SLANG_INT_TYPE);
	
	atexit(shutdown_slang);
}

