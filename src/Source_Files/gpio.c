
/**
 * @file gpio.c
 *
 * @author
 *
 * @date
 *
 * @brief
 *
 */
//***********************************************************************************
// Include files
//***********************************************************************************
#include "gpio.h"

#include "scheduler.h"




//***********************************************************************************
// defined files
//***********************************************************************************



//***********************************************************************************
// static global variables
//***********************************************************************************

static uint32_t gpio_even_irq_cb=GPIO_EVEN_IRQ_CB;

static uint32_t gpio_odd_irq_cb=GPIO_ODD_IRQ_CB;





//***********************************************************************************
// function prototypes
//***********************************************************************************


//***********************************************************************************
// functions
//***********************************************************************************
/***************************************************************************//**
 * @brief
 *
 *
 * @details
 *
 *
 *
 ******************************************************************************/





/**
 * @file gpio.c
 * @author Gavin Unrue
 * @date 2-28-2023
 * @brief configures gpio pins for led output and button input+ other initialization.
 *
 */









/***************************************************************************//**
 * @brief
 *  Initialize gpio peripheral
 *
 *
 * @details
 * This function first utilizes the cmu to enable the clock to the gpio peripheral
 * so that gpio functionality can be used. Then, the first bit of the gpio control register
 * is set to one and then cleared.  A test of the EFM_Assert function is performed, and
 * afterwards the gpios responsible for led and button input/output are configured
 * to receive / transmit data.
 *
 * afterwards, the gpio pins are configured to generate interrupts, after
 * the gpio IEN register is set so that its respective bits are enabled.
 *
 *
 *
 *
 *
 * @return
 * void, nothing returned.
 *
 ******************************************************************************/





void gpio_open(GAME_GPIO_TypeDef *input_struct_ptr){


  //rename the ptr for less typing.
  GAME_GPIO_TypeDef *istuc=input_struct_ptr;



  //EFM_ASSERT(SOMEVALUE==SOMEOTHERVALUE);


  // Peripheral clock enabled
  CMU_ClockEnable(cmuClock_GPIO, true);

  //writing to the gpio register, I am writing to the first bit on the gpio ctrl register,
  //before setting this bit to one, I checked to make sure that the bit was zero to begin with
  //to ensure that I don't accidentally set a random bit to zero when I reset the bit.


GPIO->P[gpioPortF].CTRL|=B0EQ1;


EFM_ASSERT((GPIO->P[gpioPortF].CTRL&B0EQ1)==B0EQ1);

GPIO->P[gpioPortF].CTRL&=MASKFEFE;

//code which makes test fail: this basically just reverts the bit back to one.






//GPIO->P[gpioPortF].CTRL|=B0EQ1;


EFM_ASSERT((GPIO->P[gpioPortF].CTRL&B0EQ1)!=B0EQ1);




  // Configure PB0 and PB1 as input
  GPIO_PinModeSet(PB0_PORT, PB0_PIN, PB_GPIOMODE, PB_DEFAULT);
  GPIO_PinModeSet(PB1_PORT, PB1_PIN, PB_GPIOMODE, PB_DEFAULT);




  // Configure LED0 and LED1 as output
  GPIO_PinModeSet(LED0_PORT, LED0_PIN, LED_GPIOMODE, LED0_DEFAULT);
  GPIO_PinModeSet(LED1_PORT, LED1_PIN, LED_GPIOMODE, LED1_DEFAULT);




  //configure the enable pin to be pushpull, so that
  // the enable pin connecting the emf32 can drive or pull a current to be one or zero


  GPIO_PinModeSet(SI7021_SENSOR_EN_PORT, SI7021_SENSOR_EN_PIN, SI7021_SENSOR_EN_GPIOMODE, SI7021_SENSOR_EN_DEFAULT);






  GPIO_DriveStrengthSet(SI7021_SENSOR_EN_PORT, SI7021_SENSOR_EN_CURRENTMODE);




  GPIO_PinModeSet(SI7021_SDA_PORT,SI7021_SDA_PIN,SI7021_SDA_GPIOMODE,SI7021_SDA_DEFAULT);


  GPIO_PinModeSet(SI7021_SCL_PORT,SI7021_SCL_PIN,SI7021_SCL_GPIOMODE,SI7021_SCL_DEFAULT);



  GPIO_PinOutSet(SI7021_SENSOR_EN_PORT, SI7021_SENSOR_EN_PIN);









  //GPIO_PinModeSet






// INTERRUPT BASED CODE!!









  //clear the selected interrupts


  uint32_t GPIO_ODD_INT_MASK=ODDINTMASK;
  uint32_t GPIO_EVEN_INT_MASK=EVENINTMASK;

  GPIO->IFC = (GPIO_ODD_INT_MASK|GPIO_EVEN_INT_MASK);



  //enable the push button interrupts


  //I guess its a little too early to use these :(
  //GPIO->IEN|=0x00000006;
  //GPIO->IEN|=0x00000007;



GPIO_ExtIntConfig(istuc->btn0_port, istuc->btn0_pin, istuc->btn0_pin, ENABLE, DISABLE, ENABLE);
GPIO_ExtIntConfig(istuc->btn1_port, istuc->btn1_pin,istuc->btn1_pin , ENABLE, DISABLE, ENABLE);



  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);










}



//testing code, remove me when done


/*
void flash(int interval, int subinterval){



 for(int p=ZEROSTART;p<interval;p++){
 GPIO_PinOutClear(LED1_PORT, LED1_PIN);
 GPIO_PinOutClear(LED0_PORT, LED0_PIN);
 for(int w=ZEROSTART;w<subinterval;w++){}
 //currently set to one second.
 GPIO_PinOutSet(LED1_PORT, LED1_PIN);
 GPIO_PinOutSet(LED0_PORT, LED0_PIN);
 for(int w=ZEROSTART;w<subinterval;w++){}
 GPIO_PinOutClear(LED1_PORT, LED1_PIN);
 GPIO_PinOutClear(LED0_PORT, LED0_PIN);
 }
 }


*/





/***************************************************************************//**
 * @brief
 *  button 01 interrupt handler
 *
 *
 * @details
 *
 * This handles the first button interrupt. First the function isolates the bit which represents the button 01 interrupt flag.
 * This is accomplished via anding the GPIO enable register and the interrupt register, along with a bitmask which contains
 * a one in the button 01 interrupt flags position. Afterwards, the handler code is executed, in this case its the flashing of
 * led0 and led1. Finally, the interrupt clear register is set to the isolated button 01 interrupt flag, to clear the interrupt.
 *
 *
 *
 *
 *
 * @return
 *
 * N/A its an interrupt.
 *
 ******************************************************************************/








void GPIO_ODD_IRQHandler(){




  //make atomic
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();










  uint32_t GPIO_ODD_INT_MASK=ODDINTMASK;

  uint32_t intflag=(((GPIO->IF) & (GPIO->IEN)) & GPIO_ODD_INT_MASK);






  add_scheduled_event(gpio_odd_irq_cb);










//flash(TWO,SECONDW);





  GPIO->IFC = intflag;


  CORE_EXIT_CRITICAL();







}     /**< GPIO_ODD IRQ Handler */












/***************************************************************************//**
 * @brief
 *  button 00 interrupt handler
 *
 *
 * @details
 *
 * This handles the first button interrupt. First the function isolates the bit which represents the button 00 interrupt flag.
 * This is accomplished via anding the GPIO enable register and the interrupt register, along with a bitmask which contains
 * a one in the button 00 interrupt flags position. Afterwards, the handler code is executed, in this case its the flashing of
 * led0 and led1. Finally, the interrupt clear register is set to the isolated button 00 interrupt flag, to clear the interrupt.
 *
 *
 *
 *
 *
 * @return
 *
 * N/A its an interrupt.
 *
 ******************************************************************************/















void GPIO_EVEN_IRQHandler(){

  // make atomic
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();













  //clear flag
  uint32_t GPIO_EVEN_INT_MASK=EVENINTMASK;

  uint32_t intflag=(((GPIO->IF) & (GPIO->IEN)) & GPIO_EVEN_INT_MASK);





  add_scheduled_event(gpio_even_irq_cb);

  //flash(TWO,SECONDW);








  GPIO->IFC = intflag;




  CORE_EXIT_CRITICAL();

}    /**< GPIO_EVEN IRQ Handler */




