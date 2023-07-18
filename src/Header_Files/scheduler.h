

#ifndef SCHEDULER_HG
#define SCHEDULER_HG

#include "em_emu.h"




/* System include statements */
#include <stdint.h>
/* Silicon Labs include statements */
#include "em_assert.h"
#include "em_core.h"



#endif




void remove_scheduled_event(uint32_t event);

void add_scheduled_event(uint32_t event);


uint32_t get_scheduled_events(void);

void scheduler_open(void);
