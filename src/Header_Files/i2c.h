#include "sleep_routines.h"
#include "scheduler.h"
#include "em_i2c.h"

#include "em_cmu.h"

#include "em_assert.h"








#define measuretempholdcontrollermode 0xE3


#define ACKK 0x00000040
#define NACKK 0x00000080
#define MSTOPP 0x00000100
#define RRXDATA 0x00000020

#define SI7021ADDR 0x40



#define ABORT 0x00000020



#define I2CIRQN 17


#define ACKKYSEND 0x00000004







typedef struct {


bool enable;
bool master;
uint32_t refFreq;
uint32_t freq;
I2C_ClockHLR_TypeDef clhr;

}I2C_Open_TypeDef;






typedef enum {I2C_INIT, I2C_RX_SEND_CMD, I2C_RX_SEND_ADDR,I2C_RX_RECEIVE_DATA,I2C_CLOSE}STATEE;




typedef enum{READ,WRITE}tI2c_CMD;




typedef enum{RUNNING,WAITING}substatee;




typedef struct {


 STATEE cstate;

 bool isbusy;


 //this is the address of the i2c_peripheral that is utilized
 //to write specific values to the humidity sensor.

 I2C_TypeDef *i2c_peripheral;







 uint32_t i2c_num_bytes;
 volatile uint32_t i2c_curr_bytes;
 uint32_t i2c_device_address;
 uint32_t i2c_register_address;
 uint32_t *i2c_data;
 tI2c_CMD i2c_cmd;
 uint32_t i2c_cb;

 substatee subby;










}I2C_StateMachine_TypeDef;




static void i2c_ack (I2C_StateMachine_TypeDef *i2c_sm);


static void i2c_rxdatav (I2C_StateMachine_TypeDef *i2c_sm);


static void i2c_mstop (I2C_StateMachine_TypeDef *i2c_sm);



static void i2c_nack (I2C_StateMachine_TypeDef *i2c_sm) ;



void i2c_bus_reset(I2C_TypeDef *i2c_peripheral);



void i2c_start(I2C_StateMachine_TypeDef *i2c_sm);










void i2c_open(I2C_TypeDef *i2c_peripheral, I2C_Open_TypeDef *i2c_open);





I2C_StateMachine_TypeDef *geti2state(void);




