
#include "letimer.h"

#include <brd_config.h>

/**
 * @file letimer.c
 * @author Gavin Unrue
 * @date 3-21-2023
 * @brief contains function definitions needed for the letimer layer.
 *
 */

static uint32_t scheduled_comp0_cb;
static uint32_t scheduled_comp1_cb;
static uint32_t scheduled_uf_cb;






/***************************************************************************//**
 * @brief
 *  returns callbacks related to comp0 comp1 and underflow interrupts
 *
 *
 * @details
 *Since the comp0, 1 and underflow interrupts are static, a get function is needed to access these values
 *
 *
 *
 * @param[in] option
 *    this is the index which returns the callback number, with 0 starting with comp0,
 *    1 returning comp1 and 2 returning underflow.
 *
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/










uint32_t getcallbacks(int option){


  if(option==ZERO){
      return scheduled_comp0_cb;

  }


  if(option==ONE){
        return scheduled_comp1_cb;

    }

  if(option==TWO){
        return scheduled_uf_cb;

    }


  return 0;

}






/***************************************************************************//**
 * @brief
 *  configures the letimer peripheral's registers and initializes it.
 *
 *
 * @details
 * This function writes to the letimer's registers and configs it so that it can be used
 * to periodically generate interrupts.In current configuration, this function sets the letimer to
 * count down until it underflows, upon which the counter is reset to comp0. Interrupts are generated
 * once the counter underflows, equals comp0 and equals comp1.
 *
 *
 *
 *
 * @param[in] *letimer
 *   This is a pointer to the specific timer you want to operate on.
 *
 *
 *
 *
 *
 * @param[in] app_letimer_struct
 *      This is  a struct containing settings which are needed to initialize the letimer.
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/















void
letimer_pwm_open (LETIMER_TypeDef *letimer,
                  APP_LETIMER_PWM_TypeDef *app_letimer_struct)
{

  CMU_ClockEnable (cmuClock_LETIMER0, true);

  while (letimer->SYNCBUSY);

  letimer->CNT |= ONEBIT;

  EFM_ASSERT(letimer->CNT&ONEBIT);




  //clear written bit
  letimer->CNT &= ~ONEBIT;

  while (letimer->SYNCBUSY)
    ;




  LETIMER_Init_TypeDef letimee = LETIMER_INIT_DEFAULT;
  LETIMER_Init_TypeDef *letimee0 = &letimee;

  //LETIMER_Init_TypeDef *letimee0;





  letimee0->enable = app_letimer_struct->enable;
  letimee0->debugRun = app_letimer_struct->debugRun;

  letimee0->repMode = letimerRepeatFree;

  letimee0->ufoa0 = letimerUFOAPwm;
  letimee0->ufoa1 = letimerUFOAPwm;

  //enum for pwm

  letimee0->bufTop = false;
  letimee0->comp0Top = true;

  letimee0->topValue = app_letimer_struct->period;

  letimee0->out0Pol = ZERO;
  // is polarity, 1 is inverted, in sync.
  letimee0->out1Pol = ZERO;


  // Need REP0 != 0 to run PWM

  while (letimer->SYNCBUSY);

  LETIMER_RepeatSet (LETIMER0, ZERO, ONE);
  LETIMER_RepeatSet (LETIMER0, ONE, ONE);
  while (letimer->SYNCBUSY);




  while (letimer->SYNCBUSY);
  LETIMER_CompareSet (LETIMER0, ONE, app_letimer_struct->active_period);
  while (letimer->SYNCBUSY);


  //clear interrupts before enabling them.


  while (letimer->SYNCBUSY);
  letimer->IFC |= ONEBIT;
  letimer->IFC |= TWOBIT;
  letimer->IFC |= THREEBIT;
  while (letimer->SYNCBUSY);


  //enable interrupts

  //uint32_t test=app_letimer_struct->comp1_irq_enable;


  while (letimer->SYNCBUSY);
  letimer->IEN |= (app_letimer_struct->comp0_irq_enable);
  letimer->IEN |= (app_letimer_struct->comp1_irq_enable)<<1;
  letimer->IEN |= (app_letimer_struct->uf_irq_enable)<<2;


  letimer->IEN |= (app_letimer_struct->comp0_irq_enable);
  while (letimer->SYNCBUSY);



  //enable interrupts in the NVIC



  NVIC_EnableIRQ (LETIMER0_IRQn);

  scheduled_comp0_cb = app_letimer_struct->comp0_cb;
  scheduled_comp1_cb = app_letimer_struct->comp1_cb;

  scheduled_uf_cb = app_letimer_struct->uf_cb;

  //enable outputs.

  while (letimer->SYNCBUSY);
  LETIMER0->ROUTEPEN |= app_letimer_struct->out_pin_0_en;
  LETIMER0->ROUTEPEN |= (app_letimer_struct->out_pin_1_en)<<ONE ;
  while (letimer->SYNCBUSY);


  //set routes

  while (letimer->SYNCBUSY);
  LETIMER0->ROUTELOC0 |= app_letimer_struct->out_pin_route0;
  LETIMER0->ROUTELOC0 |= ((app_letimer_struct->out_pin_route1) << EIGHT);
  while (letimer->SYNCBUSY);


  LETIMER_Init (letimer, letimee0);



  int w=letimer->STATUS;


  int h=4;




}
;



static hasstart=1;

void
letimer_start (LETIMER_TypeDef *letimer, bool enable)
{












  LETIMER_Enable (letimer, enable);







  // if this is a call proceeding an enabling letimerstart call, invert functionality and disable letimer


  if(hasstart<1){
    LETIMER_Enable(letimer,false);

  }












  //Make sure that this function is not called more than necessary.
  //if the letimer is already active, then dont call the sleep_block_mode function again.
  if(hasstart==1){


  //assert that the timer is already running before enabling the sleep mode.

  EFM_ASSERT((letimer->STATUS)&ONEBIT);
  sleep_block_mode(LETIMER_EM);}











  //if the timer is not enabled, unblock the energy mode

  if(hasstart<1){

      sleep_unblock_mode(LETIMER_EM);





  }




  while(letimer->SYNCBUSY);





  hasstart=hasstart*INVERT;

}









/***************************************************************************//**
 * @brief
 *  Schedules respective events upon interrupt
 *
 *
 * @details
 * This function schedules events for the comp0 comp1 and underflow interrupts.
 * These interrupts are later serviced by their respective callback functions.
 *
 *
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/













void LETIMER0_IRQHandler (void)
{






  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();

  if (LETIMER0->IF & ONEBIT)
    {

      uint32_t intflag = (((LETIMER0->IF) & (LETIMER0->IEN)) & ONEBIT);

      add_scheduled_event (scheduled_comp0_cb);

      LETIMER0->IFC = intflag;

      EFM_ASSERT((LETIMER0->IF&intflag)==0);


    }

  if (LETIMER0->IF & TWOBIT)
    {

      uint32_t intflag = (((LETIMER0->IF) & (LETIMER0->IEN)) & TWOBIT);

      add_scheduled_event (scheduled_comp1_cb);

      LETIMER0->IFC = intflag;

      EFM_ASSERT((LETIMER0->IF&intflag)==0);

    }




  if (LETIMER0->IF & THREEBIT)
    {

      uint32_t intflag = (((LETIMER0->IF) & (LETIMER0->IEN)) & THREEBIT);

      add_scheduled_event (scheduled_uf_cb);

      LETIMER0->IFC = intflag;

      EFM_ASSERT((LETIMER0->IF&intflag)==0);


    }

  CORE_EXIT_CRITICAL();

}

