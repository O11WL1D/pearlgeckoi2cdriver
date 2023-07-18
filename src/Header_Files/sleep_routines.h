#include "em_emu.h"

#include "em_core.h"


#include "em_assert.h"








void sleep_open(void);


void sleep_block_mode(uint32_t EM);



void sleep_unblock_mode(uint32_t EM);




void Enter_Sleep(void);


uint32_t current_block_energy_mode(void);




#define EM0 0u

#define EM1 1u
#define EM2 2u
#define EM3 3u
#define EM4 4u
#define MAX_ENERGY_MODES 5u


