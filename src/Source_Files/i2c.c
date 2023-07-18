#include "i2c.h"

#include "em_i2c.h"

#include "brd_config.h"

static I2C_StateMachine_TypeDef i2cstatee;

static I2C_StateMachine_TypeDef *i2cstate = &i2cstatee;

//I2C_StateMachine_TypeDef i2cstate;

static uint32_t msbbyte;

static uint32_t lsbbyte;

static void
i2c_ack (I2C_StateMachine_TypeDef *i2c_sm)
{

  switch (i2c_sm->cstate)
    {

    case (I2C_INIT):

      i2c_sm->cstate = I2C_RX_SEND_CMD;
      i2c_nack (i2c_sm);

      break;

    case (I2C_RX_SEND_CMD):

      i2c_sm->cstate = I2C_RX_SEND_ADDR;
      i2c_nack (i2c_sm);

      break;

    case (I2C_RX_SEND_ADDR):

      i2c_sm->cstate = I2C_RX_RECEIVE_DATA;
      i2c_nack (i2c_sm);

      break;

    case (I2C_RX_RECEIVE_DATA):

    i2c_sm->cstate = I2C_CLOSE;
    i2c_nack (i2c_sm);

      break;

    case (I2C_CLOSE):

      break;

    }

}

void
i2c_open (I2C_TypeDef *i2c_peripheral, I2C_Open_TypeDef *i2c_open)
{

  NVIC_EnableIRQ (I2C0_IRQn);

  //enable clocks for the i2c module.
  CMU_ClockEnable (cmuClock_I2C0, true);
  CMU_ClockEnable (cmuClock_I2C1, true);

  I2C_Init_TypeDef initpass;

  initpass.enable = i2c_open->enable;
  initpass.master = i2c_open->master;
  initpass.refFreq = i2c_open->refFreq;
  initpass.freq = i2c_open->freq;
  initpass.clhr = i2c_open->clhr;

  I2C_Init_TypeDef *initpass_ptr = &initpass;

  //initialize the i2c peripheral
  I2C_Init (i2c_peripheral, initpass_ptr);

  //open must be init type def !!!!

  //check to see if clocks are configured properly↓ if this EFM assert statement doesnt work, then the clocks are not configured properly.
  //check if the first bit or the i2c enable bit is high
  EFM_ASSERT(i2c_peripheral->CTRL&OONEBIT);

  //enable instance of I2C_StateMachine

  i2cstate->cstate = I2C_INIT;

  i2cstate->isbusy = true;

  i2cstate->i2c_peripheral = i2c_peripheral;

  i2cstate->i2c_num_bytes = 2;
  i2cstate->i2c_curr_bytes = 0;
  i2cstate->i2c_device_address = 0x40;
  i2cstate->i2c_register_address = &(i2c_peripheral->RXDATA);
  i2cstate->i2c_data = &(i2c_peripheral->RXDATA);
  i2cstate->i2c_cmd = READ;
  i2cstate->i2c_cb = 0xF1F1F1F1;

  i2cstate->subby = RUNNING;

  //={I2C_INIT,true,i2c_peripheral,2,0,0x40,&(i2c_peripheral->RXDATA),&(i2c_peripheral->RXDATA),READ,0xF1F1F1F1,RUNNING};

  //assign the I2Cstate machine to a static variable.

  //block EM2 energy mode
  sleep_block_mode (EM2);

  //enableroutereg
  i2c_peripheral->ROUTEPEN = 0x3;

  i2c_peripheral->ROUTELOC0 = 0xF0F;

  //enable nack, mstop and ack interrupts
  i2c_peripheral->IEN = 0x1E0;

  //reset the bus
  i2c_bus_reset (i2c_peripheral);

  //clear pre-existing interrupts ->
  i2c_peripheral->IFC = CLEARING;

}
;

static int w = 0;

//this function is called upon every underflow, and contains the switch statement which
//decides functionality upon the state machines current state.

static void
i2c_nack (I2C_StateMachine_TypeDef *i2c_sm)
{

  int j = 5;

  switch (i2c_sm->cstate)
    {

    case I2C_INIT:

      //  I2C_TypeDef *device=i2c_sm->i2c_device_address;

      //I2C_Transfer

      //send abort cmd to clear the bus of any current transfers, then send start cmd.

      /*

       this got me to the send cmd state where the measure cmd reg woudnt write for some reason, I have no idea what is even wrong at this point.



       //periodic bus reset to ensure that bus is not tied up and therefore prevents desired transmissions from occuring,
       w++;
       if(w>200){
       i2c_bus_reset(i2c_sm->i2c_peripheral);
       //(i2c_sm->i2c_peripheral)->CMD|=ABORT;

       w=0;
       }

       */

      (i2c_sm->i2c_peripheral)->TXDATA = (((i2c_sm->i2c_device_address) << 1));

      //send start cmd
      (i2c_sm->i2c_peripheral)->CMD = OONEBIT;

      //(i2c_sm->i2c_peripheral)->TXDATA=(((i2c_sm->i2c_device_address)<<1)) ;

      //set read/write bit to read, or one
      //(i2c_sm->i2c_peripheral)->SADDR|=OONEBIT;

      break;

    case (I2C_RX_SEND_CMD):

      /*
       w++;
       if(w>100){
       (i2c_sm->i2c_peripheral)->CMD|=ABORT;
       w=0;
       }

       */

      j = 7;

      (i2c_sm->i2c_peripheral)->TXDATA = measuretempholdcontrollermode;

      j = 5;

      j = 22;

      break;

    case (I2C_RX_SEND_ADDR):

      /*
       w++;
       if(w>200){
       i2c_bus_reset(i2c_sm->i2c_peripheral);
       w=0;
       }
       */

      //send repeated start cmd, this is literally just the start cmd send after the first one.
      (i2c_sm->i2c_peripheral)->CMD = OONEBIT;

      (i2c_sm->i2c_peripheral)->TXDATA = (((i2c_sm->i2c_device_address) << 1)
          | OONEBIT);

      j = 22;

      break;

    case (I2C_RX_RECEIVE_DATA):

      //send ack interrupt

      if (i2c_sm->i2c_curr_bytes == 1)
        {


        }

      //send mstop
      if (i2c_sm->i2c_curr_bytes == 2)
        {

        }

      break;

    case (I2C_CLOSE):


    i2c_sm->isbusy=false;
    sleep_unblock_mode(EM2);
    add_scheduled_event(i2c_sm->i2c_cb);


    while(true){}






      break;

    }
}

I2C_StateMachine_TypeDef*
geti2state ()
{

  return i2cstate;

}

void
i2c_start (I2C_StateMachine_TypeDef *i2c_sm)
{

//while(true){
  i2c_nack (i2cstate);
//}

}

void
i2c_bus_reset (I2C_TypeDef *i2c_peripheral)
{

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();

  //abort all prev commands
  (i2c_peripheral)->CMD = ABORT;

  //clear the IF
  i2c_peripheral->IFC = CLEARING;
//  while(i2c_peripheral->IF){
  //     i2c_peripheral->IFC=CLEARING;

  //};

  //clear transmit buffers

  i2c_peripheral->TXDATA = ZEROHEX;
  i2c_peripheral->TXDOUBLE = ZEROHEX;

  while ((i2c_peripheral->TXDOUBLE) || (i2c_peripheral->TXDOUBLE))
    {
      i2c_peripheral->TXDATA = ZEROHEX;
      i2c_peripheral->TXDOUBLE = ZEROHEX;
    }

  //write start and stop bits into cmd.
  (i2c_peripheral)->CMD = (TWOBIT | OONEBIT);

  while (!(i2c_peripheral->IF & I2C_IF_MSTOP))
    {
    };

  //clear the IF
  i2c_peripheral->IFC = CLEARING;
  while (i2c_peripheral->IF)
    {
      i2c_peripheral->IFC = CLEARING;

    };

  (i2c_peripheral)->CMD = ABORT;

  CORE_EXIT_CRITICAL();

//check lab writeup  page 9, !!
  //

}
;

void
I2C0_IRQHandler ()
{

  int intflag = 0x00000000;

  I2C_StateMachine_TypeDef *stateptr = geti2state ();

  if ((stateptr->i2c_peripheral->IF) & (ACKK))
    {

      //clear the interrupt
      intflag = ((stateptr->i2c_peripheral->IF) & (ACKK));
      (stateptr->i2c_peripheral->IFC) = intflag;

      i2c_ack (i2cstate);

    }

  if ((stateptr->i2c_peripheral->IF) & (NACKK))
    {

      //clear interrupt:

      intflag = ((stateptr->i2c_peripheral->IF) & (NACKK));
      (stateptr->i2c_peripheral->IFC) = intflag;
      i2c_nack (i2cstate);

    }

  if ((stateptr->i2c_peripheral->IF) & (MSTOPP))
    {

      //clear the interrupt.
      intflag = ((stateptr->i2c_peripheral->IF) & (MSTOPP));
      (stateptr->i2c_peripheral->IFC) = intflag;

      //check if fruitful interrupt
      if (msbbyte)
        {



          i2c_ack (i2cstate);







        }

    }




  if ((stateptr->i2c_peripheral->IF) & (RRXDATA))
    {

      //clear the interrupt.
      intflag = ((stateptr->i2c_peripheral->IF) & (RRXDATA));
      (stateptr->i2c_peripheral->IFC) = intflag;




      //read data from sensor

      if (stateptr->i2c_curr_bytes == 0)
        {

          msbbyte = stateptr->i2c_peripheral->RXDATAP;
          (i2cstate->i2c_peripheral)->CMD = I2C_CMD_ACK;// ACKKYSEND;

          stateptr->i2c_curr_bytes++;



        }





      else
        {
          lsbbyte = stateptr->i2c_peripheral->RXDATAP;



         // while(true){}


          //write start and stop bits into cmd.



          (i2cstate->i2c_peripheral->CMD) = I2C_CMD_NACK; //(TWOBIT | OONEBIT);
          (i2cstate->i2c_peripheral)->CMD = I2C_CMD_START | I2C_CMD_STOP;

          stateptr->i2c_curr_bytes++;

        }

      //i2c_nack (i2cstate);

    }

}
;

