/***************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for SLSTK3LVLCNT02A
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "main.h"

#include "sleep_routines.h"

/**
 * @file main.c
 * @author Gavin Unrue
 * @date 2-28-2023
 * @brief initializes peripherals and also contains game code.
 *
 */

/***************************************************************************//**
 * @brief
 *  Main execution
 *
 *
 * @details
 *
 *This initializes the clocks for needed peripherals, and then calls the app_peripheral setup which calls
 *other functions.
 *
 * @return
 *
 * N/A
 *
 ******************************************************************************/

int
main (void)
{

  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;

  /* Chip errata */
  CHIP_Init ();

  /* Init DCDC regulator and HFXO with kit specific parameters */
  /* Init DCDC regulator and HFXO with kit specific parameters */
  /* Initialize DCDC. Always start in low-noise mode. */
  CMU_HFRCOBandSet (MCU_HFXO_FREQ);        // Sets main CPU oscillator frequency
  EMU_EM23Init_TypeDef em23Init = EMU_EM23INIT_DEFAULT;
  EMU_DCDCInit (&dcdcInit);
  em23Init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  EMU_EM23Init (&em23Init);
  CMU_HFXOInit (&hfxoInit);

  CMU_ClockEnable (cmuClock_CORELE, true);

  /* Switch HFCLK to HFRCO and disable HFRCO */
  CMU_OscillatorEnable (cmuOsc_HFRCO, true, true);

// this code is redundant, but its here to keep the oscillator typedef's name around for later use.
//  CMU_OscillatorEnable(cmuOsc_ULFRCO, true, true);

  CMU_ClockSelectSet (cmuClock_HF, cmuSelect_HFRCO);

  CMU_OscillatorEnable (cmuOsc_HFXO, false, false);

  //enable oscillators for i2c peripheral

  CMU_HFRCOBandSet (MCU_HFXO_FREQ);
  CMU_OscillatorEnable (cmuOsc_HFRCO, true, true);
  CMU_ClockSelectSet (cmuClock_HF, cmuSelect_HFRCO);
  CMU_OscillatorEnable (cmuOsc_HFXO, false, false);

  /* Call application program to open / initialize all required peripheral */
  app_peripheral_setup ();

  //this keeps track of the current event that has taken place.

  //static uint32_t eevent=ZEROSTART;

  while (true)
    {

      CORE_DECLARE_IRQ_STATE;
      CORE_ENTER_CRITICAL();

      if (!get_scheduled_events ())
        {
          Enter_Sleep ();
        }

      CORE_EXIT_CRITICAL();

      i2c_start (geti2state ());

      if (get_scheduled_events () == getcallbacks (0))
        {
          comp0cb ();
          remove_scheduled_event (getcallbacks (0));
        }

      if (get_scheduled_events () == getcallbacks (1))
        {
          comp1cb ();
          remove_scheduled_event (getcallbacks (1));
        }

      if (get_scheduled_events () == getcallbacks (2))
        {
          underflowcb ();
          remove_scheduled_event (getcallbacks (2));

        }

      if (get_scheduled_events () == GPIO_ODD_IRQ_CB)
        {

          uint32_t current_block_em = current_block_energy_mode ();

          sleep_unblock_mode (current_block_em);

          if (current_block_em < 4)
            {

              sleep_block_mode (current_block_em + 1);
            }
          else
            {
              sleep_block_mode (EM0);
            }

          uint32_t ww = current_block_energy_mode ();

          remove_scheduled_event (GPIO_ODD_IRQ_CB);

        }

      if (get_scheduled_events () == GPIO_EVEN_IRQ_CB)
        {

          uint32_t current_block_em = current_block_energy_mode ();
          sleep_unblock_mode (current_block_em);

          if (current_block_em > 0)
            {

              sleep_block_mode (current_block_em - 1);

            }
          else
            {

              sleep_block_mode (EM4);
            }

          uint32_t ww = current_block_energy_mode ();

          remove_scheduled_event (GPIO_EVEN_IRQ_CB);

        }

    }

  /*


   while(true){


   if(get_scheduled_events()==GPIO_ODD_IRQ_CB){

   remove_scheduled_event(GPIO_ODD_IRQ_CB);

   //button 1 pressed, set eevent to 2
   eevent=scheduled_gpio_odd_irq_cb();




   }




   if(get_scheduled_events()==GPIO_EVEN_IRQ_CB){

   remove_scheduled_event(GPIO_EVEN_IRQ_CB);
   //button 0 pressed, record and run the change state function.
   eevent=eevent+scheduled_gpio_even_irq_cb();

   //Since eevent is default zero, this assigns to 1, and three if button 1 is also pressed.


   }else{eevent=ZEROSTART;}





   //call to change state function here.

   changestate(eevent);













   }

   */

}

