
#include <game.h>



/**
 * @file game.c
 * @author Gavin Unrue
 * @date 3-8-2023
 * @brief  contains code to play the game, and also other functions pertaining to the game
 *
 */















/***************************************************************************//**
 * @brief
 *
 *  inits game-gpio struct and calls gpioopen()
 *
 * @details
 *
 * This initializes the input_struct which is passed to the gpioopen() function
 * so that settings pertaining to the usage of gpio based interrupts can be used.
 *
 *
 * @return
 *
 * N/A its void.
 *
 ******************************************************************************/














void game_gpio_open(){


  GAME_GPIO_TypeDef input_struct={ENABLE,PB0_PIN,PB0_PORT,PB1_PIN,PB1_PORT,ENABLE,ENABLE,ENABLE,ENABLE};

  GAME_GPIO_TypeDef *input_struct_ptr=&input_struct;

  //should pass the input_struct as a pointer to gpio_open



  gpio_open(input_struct_ptr);




}














/***************************************************************************//**
 * @brief
 *  infiinite loop function..
 *
 * @details
 *
 * its an infinite loop :(
 *
 *
 *
 *
 * @return
 *
 * N/A its a loop.
 *
 ******************************************************************************/








void infloop(){

  while(true){



  }


}



























































  /***************************************************************************//**
   * @brief
   *  Gets bt0/bt1 status
   *
   *
   * @details
   * This function utilizes the gpio_PinInGet() function in a loop for a duration of MICROLENGTH
   * to check if button0 or button1 are currently being pressed.
   *
   *
   *
   * @note
   *   Nothing out of the ordinary.
   *
   *
   *
   * @param[in] int *pb0
   *   This is a pointer to the pb0 variable, which indicates whether or
   *   not the first button was held down at the moment of this functions
   *   conclusion.
   *
   *  @param[in] int *pb0
   *    same thing as pb1, but for the second button.
   *
   *
   *
   * @return
   *
   * EHRET, this is just equal to zero, isnt used at all.
   *
   ******************************************************************************/



















  int app_gpio_button_poll(int *pb0, int *pb1){


    //two pointers to bitpress variables are passed, so that this function can 'return' multiple values.

    //the function will poll for the micropolllength, updating PB0 and PB1 and when that ceases this function will return.


    int x=ZEROSTART;

    while (true)
    {

      x++;






      if (GPIO_PinInGet(PB0_PORT, PB0_PIN) != PRESSVALUE)
      {


          //is pressed
          *pb0=ISPRESS;

      }else{*pb0=ISNOTPRESS;}




      if (GPIO_PinInGet(PB1_PORT, PB1_PIN) != PRESSVALUE)
      {

          //is pressed.
          *pb1=ISPRESS;

      }else{*pb1=ISNOTPRESS;}


       //polling interval has passed.
       if(!(x<((MICROPOLLLENGTH)))){

           return EHRET;





      }





    }


      }










  /***************************************************************************//**
   * @brief
   *  flashes both leds.
   *
   *
   * @details
   * This function flashes both leds
   * Typical usage entails the SECOND macro being
   * passed for subinterval, and the number of
   * seconds to flash for being passed in the
   * interval parameter.
   *
   *
   *
   *
   *
   * @param[in] interval
   *    This is what controls how many times the subinterval should run, see details for usage.
   *
   *
   *
   *
   *  @param[in] subinterval
   *    value which dictates how long the function should keep the leds on/off for.
   *
   *
   *
   * @return
   *
   * void, nothing.
   *
   ******************************************************************************/































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







  /***************************************************************************//**
   * @brief
   *  flashes led0
   *
   *
   * @details
   * This function flashes led0
   * Typical usage entails the SECOND macro being
   * passed for subinterval, and the number of
   * seconds to flash for being passed in the
   * interval parameter.
   *
   *
   *
   *
   *
   * @param[in] interval
   *    This is what controls how many times the subinterval should run, see details for usage.
   *
   *
   *
   *
   *  @param[in] subinterval
   *    value which dictates how long the function should keep the leds on/off for.
   *
   *
   *
   * @return
   *
   * void, nothing.
   *
   ******************************************************************************/










  void flash0(int interval, int subinterval){




  for(int p=ZEROSTART;p<interval;p++){
  GPIO_PinOutClear(LED1_PORT, LED1_PIN);
  GPIO_PinOutClear(LED0_PORT, LED0_PIN);
  for(int w=ZEROSTART;w<subinterval;w++){}
  //currently set to one second.
  GPIO_PinOutSet(LED0_PORT, LED0_PIN);
  for(int w=ZEROSTART;w<subinterval;w++){}
  GPIO_PinOutClear(LED1_PORT, LED1_PIN);
  GPIO_PinOutClear(LED0_PORT, LED0_PIN);
  }
  }





  /***************************************************************************//**
   * @brief
   *  flashes led1
   *
   *
   * @details
   * This function flashes led1
   * Typical usage entails the SECOND macro being
   * passed for subinterval, and the number of
   * seconds to flash for being passed in the
   * interval parameter.
   *
   *
   *
   *
   *
   * @param[in] interval
   *    This is what controls how many times the subinterval should run, see details for usage.
   *
   *
   *
   *
   *  @param[in] subinterval
   *    value which dictates how long the function should keep the leds on/off for.
   *
   *
   *
   * @return
   *
   * void, nothing.
   *
   ******************************************************************************/


















  void flash1(int interval, int subinterval){

    //This function flashes led1
    // Typical usage entails the SECOND macro being
      //passed for subinterval, and the number of
      // seconds to flash for being passed in the
      //interval parameter.


  for(int p=ZEROSTART;p<interval;p++){
  GPIO_PinOutClear(LED1_PORT, LED1_PIN);
  GPIO_PinOutClear(LED0_PORT, LED0_PIN);
  for(int w=ZEROSTART;w<subinterval;w++){}
  //currently set to one second.
  GPIO_PinOutSet(LED1_PORT, LED1_PIN);
  for(int w=ZEROSTART;w<subinterval;w++){}
  GPIO_PinOutClear(LED1_PORT, LED1_PIN);
  GPIO_PinOutClear(LED0_PORT, LED0_PIN);
  }
  }






  /***************************************************************************//**
   * @brief
   *  creates a delay.
   *
   *
   * @details
   *  This function wastes machine cycles to create a delay.
   *  Typical usage entails the SECOND macro being
   *  passed for subinterval, and the number of
   *  seconds to wait for being passed in the
   *  interval parameter.

   *
   *
   *
   *
   *
   * @param[in] interval
   *    This is what controls how many times the subinterval should run, see details for usage.
   *
   *
   *
   *
   *  @param[in] subinterval
   *    value which dictates how long the function should wait.
   *
   *
   *
   * @return
   *
   * void, nothing.
   *
   ******************************************************************************/















  void wait(int interval, int subinterval){






  for(int p=ZEROSTART;p<interval;p++){

  for(int w=ZEROSTART;w<subinterval;w++){}
  //currently set to one second.

  for(int w=ZEROSTART;w<subinterval;w++){}

  }
  }






































  /**
   * @brief Game variables
   *
   *  →contains everything needed for the games operation,
   *
   *
   */


typedef struct game{










  int lev0[LVLCNT];/**< This is the set of patterns that led0 should cycle through, is later set to equal {1,0,1,1}  */


  int lev1[LVLCNT];/**< This is the set of patterns that led1 should cycle through, is later set to equal {1,1,0,1}  */




  int currentlevel;/**< this is the current level, this is updated as the game runs. */


  int rec0[LVLCNT];/**< An array in which user's button presses are recorded */
  int rec1[LVLCNT];




}game;














  enum states {START, PLAYING, LOSE, WIN, END};



  enum states cstate=START;



  game cgame={{BIN1,BIN0,BIN1,BIN1},{BIN1,BIN1,BIN0,BIN1},ZEROSTART};
  game *cgame_ptr= &cgame;



int pb0=ZEROSTART; //these variables are used in the polling code, located in the app.c file.*/
int pb1=ZEROSTART; // these variables are used in the polling code, located in the app.c file.*/

int *pb0_ptr=&pb0;
int *pb1_ptr=&pb1;
















/***************************************************************************//**
 * @brief
 *  Main game
 *
 *
 * @details
 *
 *
 * The game first starts off in the START state and flashes both leds for 30 seconds using the flash function,
 * next the game advances towards the PLAYING state. If the current level of the game is not equal to five, the code will
 * cycle through levels 1-4. During each level, the player is expected to match the led output using the buttons.
 * When the forth level ends, the code will go through an array containing the user's input and check if it matches the
 * proper input. If it does, the code goes to the WIN state, and the LOSE state otherwise. In the WIN state, led0 flashes
 * for 30 seconds, and the code advances to the END state. In the LOSE state, led1 flashes and the code advances to the END state.
 * In the END state, the program delays for 30 seconds, before restarting via going back to the START state.
 *
 *
 *
 *
 * * @param cgame
 *    This is the struct instance of game, which is described elsewhere.
 *
 *
 * @param pb0/pb1
 *    These are variables which the buttons push status write to. There is an associated pointer as
 *    well which is used in the polling function.
 *
 *
 * @param target0/1
 *    In the section its used, this is just equal to the current level's associated bit.
 *  These variables are used to make the code look nicer.
 *
 *
 * @param wflag
 *    This variable is used to check if the user has won. This variable has a default value of zero.
 * when the code goes through and checks each item in the lev0/1 arrays, if the user input is not
 * equal to the required input, this flag is set to zero.
 *
 *
 *
 * @return
 *
 * N/A game runs in infinite loop.
 *
 ******************************************************************************/












void rungame(){















while(true){


    switch(cstate){

        case(START):




        cgame_ptr->currentlevel=ZEROSTART;

        flash(FLASHP,SECONDW); //         currently FLASHP is set to 10 seconds.
        //flash for 10 seconds to indicate the game starting. */







        cstate=PLAYING;
        break;





        case(PLAYING):






        //check if we should be playing, or checking the
            // user input for correct input.
        if (cgame_ptr->currentlevel<LEVELMAX){



            int currentlevel=cgame_ptr->currentlevel;
            int target0=cgame_ptr->lev0[currentlevel];
            int target1=cgame_ptr->lev1[currentlevel];
            //this cleans up the code, target0 is the first bit for the level.







            //turn on appropriate leds for level.

            if(target0){
             GPIO_PinOutSet(LED0_PORT, LED0_PIN);
            }else{GPIO_PinOutClear(LED0_PORT, LED0_PIN);}


            if(target1){
                GPIO_PinOutSet(LED1_PORT, LED1_PIN);
            }else{GPIO_PinOutClear(LED1_PORT, LED1_PIN);}




            //button polling code :)
            //this is what retrieves user input.
            //Since the pb0 and pb1 variables do not change
            //after polling occurs, the can be used just as :>




              for(int ww=ZEROSTART;ww<(POLLLENGTH);ww++){

                  app_gpio_button_poll(pb0_ptr,pb1_ptr);

              }



              //record the current user input for the current level.
              // this array will be checked after the playing state.
              cgame_ptr->rec0[currentlevel]=pb0;
              cgame_ptr->rec1[currentlevel]=pb1;







                 cgame_ptr->currentlevel++;








        }else{
            // here we are checking if the user has won or not.
            // if they won, then the statemachine goes into the win state, and vice versa for loss.

            //this flag is set to one and stays one unless one of the
            // inputs doesn't match the required input for any given level.
            int wflag=WINCOND;

            for(int x=ZEROSTART;x<LVLCNT;x++){

                //just cleaning up the code here, for readability.
                int b0=cgame_ptr->rec0[x];
                int b1=cgame_ptr->rec1[x];

                int r0=cgame_ptr->lev0[x];
                int r1=cgame_ptr->lev1[x];


                if((b0!=r0)||(b1!=r1)){
                    wflag=FAILCOND;}

           }


           // if win, then win, yahdah yadha
           if(wflag){
               cstate=WIN;
           } else{cstate=LOSE;}






        break;


        case(LOSE):


        //flash the second bit for 10 seconds, then end.

        flash1(FLASHP,SECONDW);
        cstate=END;






        }






        break;


        case(WIN):

     //flash the first bit for 10 seconds, then end.

        flash0(FLASHP,SECONDW);
        cstate=END;

         break;
        case(END):


        //both bits should be zero here, so the wait just delays for 10 seconds, then restarts the game.
        wait(FLASHP,SECONDW);
        cstate=START;





         break;




        default:
         break;






    }

 }

}








