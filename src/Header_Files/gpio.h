#ifndef GPIO_HG
#define GPIO_HG

//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_gpio.h"
#include "brd_config.h"

#include "em_assert.h"

#include <bsp.h>
#include <bspconfig.h>



//***********************************************************************************
// defined files
//***********************************************************************************

#define SOMEVALUE 12
#define SOMEOTHERVALUE 123123
#define B0EQ1 0x00000001
#define MASKFEFE 0xfffffffe

















  /**
   * @brief Gpio struct variables
   *
   *  →contains everything needed to initialize the gpio module for interrupts.
   *
   *
   */






typedef struct {


bool Enable;/**<enable the GPIO upon completion of open  */
uint32_t btn0_pin;/**< btn0 route to gpio pin */
uint32_t btn0_port;/**< btn0 route to gpio port */
uint32_t btn1_pin;/**<btn1 route to gpio pin  */
uint32_t btn1_port;/**<btn1 route to gpio port  */

bool btn0_en;/**< enable btn0 port/pin */
bool btn1_en;/**< enable btn1 port/pins */


bool btn0_irq_enable; /**<  enable interrupt on btn0 interrupt*/

bool btn1_irq_enable;/**< enable interrupt on btn0 interrupt */

} GAME_GPIO_TypeDef;




























//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************
void gpio_open(GAME_GPIO_TypeDef *input_struct_ptr);

#endif



