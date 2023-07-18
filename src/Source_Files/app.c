/*
 * app.c
 *
 *  Created on:
 *      Author:
 */

//***********************************************************************************
// Include files
//***********************************************************************************
#include "app.h"

#include "game.h"

#include "scheduler.h"

#include "letimer.h"




static int toggle = ONE;
static int toggle2 = ONE;

//***********************************************************************************
// defined files
//***********************************************************************************

//***********************************************************************************
// global variables
//***********************************************************************************

//***********************************************************************************
// function
//***********************************************************************************

/**
 * @file app.c
 * @author Gavin Unrue
 * @date 2-28-2023
 * @brief initializes peripherals used and also calls game function.
 *
 */

void
app_peripheral_setup (void)
{
  cmu_open ();

  scheduler_open ();

  game_gpio_open ();

  app_letimer_pwm_open (PWM_PER, PWM_ACT_PER, LETIMER_ROUTELOC0_OUT0LOC_LOC28,
                        LETIMER_ROUTELOC0_OUT0LOC_LOC28);

  //rungame();
  //infloop();
  sleep_open();


  letimer_start (LETIMER0, true);

  app_i2c_open(true,true,0, I2C_FREQ_STANDARD_MAX,i2cClockHLRAsymetric);









}

/***************************************************************************//**
 * @brief
 *  handles the even event
 *
 *
 * @details
 *  This function handles the even event, on the first button press it will
 *  turn on led 0, on the second press it turns off led 1. This is also used in
 *  the state machine, by returning a value.
 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/

uint32_t
scheduled_gpio_even_irq_cb ()
{

  toggle = INVERT * toggle;

  if (toggle < ZEROSTART)
    {

      //turn on led0
      GPIO_PinOutSet (LED0_PORT, LED0_PIN);

    }
  else
    {
      //turn off led1
      GPIO_PinOutClear (LED1_PORT, LED1_PIN);

    }

  return ONEEVENT;

}

/***************************************************************************//**
 * @brief
 *  initializes letimer struct and inits letimer.
 *
 *
 * @details
 * This function initializes a letimer struct, which is defined in the letimer.h file,
 * and then passes said struct to the letimer open function which initializes the letimer
 * peripheral.
 *
 *
 *
 *
 *
 * @param[in] float period
 *    This is the period which dictates when the letimer fires. The period is the time it takes for a full cycle to execute.
 *
 *
 *
 *
 *
 * @param[in] float act_period
 *      This dictates how long the active period should be. the active period is equal to half of the period.
 *
 * @param[in] out0_route
 *    no idea :/
 *
 *
 * @param[in] out1_route
 *    sample text
 *
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/

void
app_letimer_pwm_open (float period, float act_period, uint32_t out0_route,
                      uint32_t out1_route)
{

  APP_LETIMER_PWM_TypeDef letimer1 =
    { DISABLE, ENABLE, out0_route, out1_route, ENABLE, ENABLE, COUNTEDPERIOD,
        COUNTEDACTIVEPERIOD, ENABLE, LETIMER0_COMP0_CB, ENABLE,
        LETIMER0_COMP1_CB, ENABLE, LETIMER0_UF_CB };

  APP_LETIMER_PWM_TypeDef *letimer1_ptr = &letimer1;

  letimer_pwm_open (LETIMER0, letimer1_ptr);



  int x=0;

}





//put i2c struct init details here
void app_i2c_open(bool enable, bool master, uint32_t refFreq, uint32_t freq,I2C_ClockHLR_TypeDef clhr
 ){



  I2C_Open_TypeDef ii2c={enable, master, refFreq, freq, clhr};
  I2C_Open_TypeDef *ii2c_ptr=&ii2c;


  i2c_open(I2C0,ii2c_ptr);




}







/***************************************************************************//**
 * @brief
 *  handles the even event
 *
 *
 * @details
 *  This function handles the even event, on the first button press it will
 *  turn on led 1, on the second press it turns off led 0. This is also used in
 *  the state machine, by returning a value.
 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/

uint32_t
scheduled_gpio_odd_irq_cb ()
{

  toggle2 = INVERT * toggle2;

  if (toggle2 < ZEROSTART)
    {

      //turn on led1
      GPIO_PinOutSet (LED1_PORT, LED1_PIN);

    }
  else
    {
      //turn off led0
      GPIO_PinOutClear (LED0_PORT, LED0_PIN);

    }

  return TWOEVENT;

}
;

enum wstates
{
  Wone, Wtwo, Wthree
};

static uint32_t count = ZEROSTART;

static enum wstates wstate = Wone;

/***************************************************************************//**
 * @brief
 * Handles state machine transitions
 *
 *
 * @details
 *
 * This function is what handles the transitions to the statemachine.
 * This is called repeatively in a loop, so the function might not do anything
 * in every case.
 *
 * In state one, if b1 is pressed, it returns to b1. if b0 is pressed, it turns to state 2.
 * In state two, if b1 is pressed, it turns to state three. if b0 is pressed, it turns to state one.
 * in state three, if either or both b1 and b2 are pressed twice, it enables the FSM to transition back to state
 * one once the user follows with pressing B1 and B2 at the same time.
 *
 *
 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/

void
changestate (int event)
{

  switch (wstate)
    {

    case (Wone):

      //if button 1 pressed.
      if (event == TWOEVENT)
        {
          //do nothing/

        }

      //if button 0 pressed
      if (event == ONEEVENT)
        {

          wstate = Wtwo;

        }

      break;

    case (Wtwo):

      if (event == ONEEVENT)
        {
          wstate = Wone;

        }

      if (event == TWOEVENT)
        {
          wstate = Wthree;

        }

      break;

    case (Wthree):

      if ((event == ONEEVENT) || (event == TWOEVENT) || (event == THREEEVENT))
        {
          count++;

        }

      if (count >= TWOEVENT)
        {
          if (event == THREEEVENT)
            {
              count = ZEROSTART;
              wstate = Wone;

            }
        }

      break;

    default:

      break;

    }

}
;





/***************************************************************************//**
 * @brief
 *  callback handler for underflow event
 *
 *
 * @details
 * Doesnt do anything yet, but may be used for periodic checks or something.
 *
 *
 *
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/



void underflowcb(){




  //i2c_nack(i2cstate);


};




/***************************************************************************//**
 * @brief
 *  Callback handler for comp0 interrupt.
 *
 *
 * @details
* doesnt currently do anything, but will in future
 *

 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/






void comp0cb(){




}






/***************************************************************************//**
 * @brief
 *  callback handler for comp1 interrupt.
 *
 *
 * @details
 * Functionality tbd
 *
 * @return
 *
 * void, nothing
 *
 ******************************************************************************/











void comp1cb(){

}





















