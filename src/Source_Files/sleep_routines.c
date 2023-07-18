#include "sleep_routines.h"


#include <em_core.h>






/**************************************************************************
* @file sleep.c
*****************************************************************************
* @section License
* <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
* ****************************************************************************
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
* obligation to support this Software. Silicon Labs is providing the
* Software "AS IS", with no express or implied warranties of any kind,
* including, but not limited to, any implied warranties of merchantability
* or fitness for any particular purpose or warranties against infringement
* of any proprietary rights of a third party.
* Silicon Labs will not be liable for any consequential, incidental, or
* special damages, or any other relief, or for any claim by any third party,
* arising from your use of this Software.
**************************************************************************/












static uint32_t lowest_energy_mode[MAX_ENERGY_MODES];




void Enter_Sleep(void){

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();


  if(lowest_energy_mode[EM0]){




      return;}



  else{



      if(lowest_energy_mode[EM1]){

          return;
      }else{


          if(lowest_energy_mode[EM2]){EMU_EnterEM1();}else{

              if(lowest_energy_mode[EM3]){EMU_EnterEM2(true);}


              else{EMU_EnterEM3(true);}

          }}}

  CORE_EXIT_CRITICAL();

  int w=0;





}




void sleep_block_mode(uint32_t EM){

  EFM_ASSERT (EM>=0 && EM<5);

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();












  //The parameter is the Desired energy mode to block.



  //clear the current energy mode





  for(int x=0;x<MAX_ENERGY_MODES;x++){


      if(lowest_energy_mode[x]>0){

          lowest_energy_mode[x]=0;
      }

  }


  //set the passed energymode



  lowest_energy_mode[EM]=1;


  //edgecase testing, if you are deincrementing past the lowest energy mode you've got a problem :)









  CORE_EXIT_CRITICAL();


  int w=0;



}




void sleep_unblock_mode(uint32_t EM){


  EFM_ASSERT (EM>=0 && EM<5);

  CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_CRITICAL();







  //clear current blocked sleep mode


  for(int x=0;x<MAX_ENERGY_MODES;x++){


      if(lowest_energy_mode[x]>0){

          lowest_energy_mode[x]=0;
      }

  }







  CORE_EXIT_CRITICAL();









}



void sleep_open(void){



//clear lowest energy mode array.
for(int x=0;x<MAX_ENERGY_MODES;x++){
    lowest_energy_mode[x]=0;
}






};




uint32_t current_block_energy_mode(){

  for(int x=0;x<MAX_ENERGY_MODES;x++){

      if(lowest_energy_mode[x]==1){
          return x;}
  }
}










