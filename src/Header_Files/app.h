#ifndef APP_HG
#define APP_HG

//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_cmu.h"
#include "cmu.h"
#include "gpio.h"



//***********************************************************************************
// defined files
//***********************************************************************************


#define ONEEVENT 1
#define TWOEVENT 2
#define THREEEVENT 3





#define LETIMER0_COMP0_CB 0x10000000
#define LETIMER0_COMP1_CB 0x20000000
#define LETIMER0_UF_CB    0x30000000



#define PWM_ACT_PER 0.25
#define PWM_PER 3.0



//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************



#endif



void app_peripheral_setup(void);

uint32_t scheduled_gpio_even_irq_cb();

uint32_t scheduled_gpio_odd_irq_cb();

void changestate(int event);

void underflowcb(void);




void comp0cb(void);




void comp1cb(void);



void app_letimer_pwm_open(float period, float act_period, uint32_t out0_route, uint32_t out1_route);








