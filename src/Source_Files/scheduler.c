
#include "scheduler.h"


#include <brd_config.h>



/**
 * @file scheduler.c
 * @author Gavin Unrue
 * @date 3-14-2023
 * @brief takes care of all scheduling stuff aside from the main while loop.
 *
 */


//Default config=0 i.e. no events scheduled, 1 equals button 0 pressed, 2 equals button 1 pressed, 3 equals both buttons pressed.

static uint32_t event_scheduled;



/***************************************************************************//**
 * @brief
 * initializes the scheduler
 *
 *
 * @details
 *  this function initializes the events scheduled variable, this makes it so that the
 *  scheduler knows what callbacks to perform.
 *
 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/



void scheduler_open(void){

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();


  //non interruptable code goes here

  event_scheduled=ZEROSTART;

  CORE_EXIT_CRITICAL();

}

/***************************************************************************//**
 * @brief
 *  returns the event scheduled variable
 *
 * @details
 *This function returns the events scheduled variable since it is
 *a static variable, and therefore will not allow other layers to access it unless
 * this get function is used
 *
 * @return
 *
 * The events scheduled variable.
 *
 ******************************************************************************/



uint32_t get_scheduled_events(void){

  return event_scheduled;

}



/***************************************************************************//**
 * @brief
 *  Adds desired bit to the events scheduled variable
 *
 *
 * @details
 * This function performs a bitwise or operation with the events scheduled variable to
 * add an event.
 *
 *
 *
 * @param[in] event
 *    This is the passed event, should be one bit.
 *
 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/



void add_scheduled_event(uint32_t event){
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();



  event_scheduled|=event;




CORE_EXIT_CRITICAL();



}



/***************************************************************************//**
 * @brief
 *  removes an event bit
 *
 * @details
 *  This function removes a bit from the events scheduled variable via bitwise and operations.
 *
 *
 *
 *
 *
 * @param[in] event
 *    should only have the one event bit that needs to be cleared.
 *

 *
 * @return
 *
 * void, nothing.
 *
 ******************************************************************************/





void remove_scheduled_event(uint32_t event){


  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();


event_scheduled&= ~event;


//this is like a bitwise not


  CORE_EXIT_CRITICAL();

}


