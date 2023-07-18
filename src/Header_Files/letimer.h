/* System include statements */
/* Silicon Labs include statements */
#include "em_cmu.h"
#include "em_assert.h"
#include "em_letimer.h"
#include "em_gpio.h"
/* The developer's include statements */
#include "scheduler.h"

#include "sleep_routines.h"


#include "i2c.h"



#define LETIMER_EM EM3



/**
 * @file letimer.h
 * @author Gavin Unrue
 * @date 3-21-2023
 * @brief contains function declarations and defines for the letimer layer.
 *
 */



#define ZERO 0

#define ONE 1
#define TWO 2
#define THREE 3

#define EIGHT 8


#define ONEBIT 0x00000001
#define TWOBIT  0x00000002
#define THREEBIT  0x00000004

uint32_t getcallbacks(int option);






  /**
   * @brief Letimer struct
   *
   *  →contains everything needed to initialize the letimers.
   *
   *
   */


typedef struct {



  bool debugRun;     /**<  should letimer continue running while halted    */
  bool enable;         /**<  enable letimer upon completion of open() */
  uint32_t out_pin_route0;     /**< out 0 route to gpio port/pin */
  uint32_t out_pin_route1;     /**< out 1 route to gpio port/pin */
  bool out_pin_0_en;             /**< enable out 0 route */
  bool out_pin_1_en;             /**< enable out 1 route */
  float period;                /**< total period in seconds */
  float active_period;         /**<  part of period that is LLH in seconds*/
  bool comp0_irq_enable;         /**<  enable interrupt on comp0 interrupt*/
  uint32_t comp0_cb;           /**<  comp0 callback (unique for scheduler)*/
  bool comp1_irq_enable;         /**<  enable interrupt on comp1 interrupt*/
  uint32_t comp1_cb;           /**<  comp1 callback (unique for scheduler)*/
  bool uf_irq_enable;          /**<  enable interrupt on underflow interrupt*/
  uint32_t uf_cb;              /**< underflow cb (unique for scheduler) */

  }APP_LETIMER_PWM_TypeDef;



  void letimer_pwm_open(LETIMER_TypeDef *letimer, APP_LETIMER_PWM_TypeDef *app_letimer_struct);


  void letimer_start(LETIMER_TypeDef *letimer, bool enable);



#define LETIMER_HZ 1000

  //this is in hz


#define ONEBIT 0x00000001


