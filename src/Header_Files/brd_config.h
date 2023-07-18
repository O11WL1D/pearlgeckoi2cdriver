



#ifndef BRD_CONFIG_HG
#define BRD_CONFIG_HG


//These isolate specific bits, used in clearing the letimer register.

#define ONEBIT 0x00000001
#define TWOBIT  0x00000002
#define THREEBIT  0x00000004

#define OONEBIT 0x00000001



#define ZEROHEX 0x00000000


#define COUNTEDPERIOD 3000

#define COUNTEDACTIVEPERIOD 25


#define INVERT -1



#define CLEARING 0xFFFFFFFF




#define SI7021_SCL_PORT gpioPortC
#define SI7021_SCL_PIN 11u
#define SI7021_SDA_PORT gpioPortC
#define SI7021_SDA_PIN 10u
#define SI7021_SENSOR_EN_PORT gpioPortB
#define SI7021_SENSOR_EN_PIN 10u


#define SI7021_SENSOR_EN_GPIOMODE gpioModePushPull
#define SI7021_SENSOR_EN_DEFAULT 0


#define SI7021_SENSOR_EN_CURRENTMODE gpioDriveStrengthWeakAlternateWeak





#define SI7021_SCL_GPIOMODE gpioModeWiredAnd
#define SI7021_SDA_GPIOMODE gpioModeWiredAnd

#define SI7021_SDA_DEFAULT 1
#define SI7021_SCL_DEFAULT 1






//***********************************************************************************
// Include files
//***********************************************************************************
#include "em_gpio.h"
#include "em_cmu.h"

//***********************************************************************************
// defined files
//***********************************************************************************



// LED 0 pin is
#define	LED0_PORT				  gpioPortF
#define LED0_PIN				  4u
#define LED0_DEFAULT			0 	// Default false (0) = off, true (1) = on
#define LED0_GPIOMODE			gpioModePushPull

// LED 1 pin is
#define LED1_PORT				  gpioPortF
#define LED1_PIN				  5u
#define LED1_DEFAULT			0	// Default false (0) = off, true (1) = on
#define LED1_GPIOMODE			gpioModePushPull



#define MCU_HFXO_FREQ			cmuHFRCOFreq_26M0Hz















// ADDITONAL GPIO pin setup






#define PB0_PORT       gpioPortF
#define PB0_PIN        6
#define PB1_PORT       gpioPortF
#define PB1_PIN        7


#define PB_DEFAULT      0   // Default false (0) = off, true (1) = on



#define LED_GPIOMODE gpioModePushPull
#define PB_GPIOMODE gpioModeInput







#define LED_RED_PORT LED0_PORT
#define LED_GREEN_PORT LED1_PORT

#define LED_RED_PIN LED0_PIN
#define LED_GREEN_PIN  LED1_PIN



#define PRESSVALUE (1)


#define SECONDW 3500000


#define FLASHP 30

#define LVLCNT 4

#define ZEROSTART 0
#define ONESTART 1

#define POLLLENGTH 200

#define MICROPOLLLENGTH 3500


#define BIN1 1
#define BIN0 0


#define LEVELMAX 5

#define WINCOND 1
#define FAILCOND 0


#define ISPRESS 1
#define ISNOTPRESS 0


#define EHRET 0





#define ENABLE true

#define DISABLE false


#define GPIO_ODD_IRQn 18
#define GPIO_EVEN_IRQn 10


#define TWO 2

#define EVENINTMASK 0x00000040


#define ODDINTMASK 0x00000080


// every odd bit

//every odd bit will set the interrupt, you need to clear every

// replace with 0000aaaa


// same with even bit

//  00005555  -> with bit 4 and bit 1



// all even bits in the iF will trigger the even handler





#define GPIO_EVEN_IRQ_CB 0x00000001

#define GPIO_ODD_IRQ_CB 0x00000002








#define STRONG_DRIVE

#ifdef STRONG_DRIVE
	#define LED0_DRIVE_STRENGTH		gpioDriveStrengthStrongAlternateStrong
	#define LED1_DRIVE_STRENGTH		gpioDriveStrengthStrongAlternateStrong
#else
	#define LED0_DRIVE_STRENGTH		gpioDriveStrengthWeakAlternateWeak
	#define LED1_DRIVE_STRENGTH		gpioDriveStrengthWeakAlternateWeak
#endif


//***********************************************************************************
// global variables
//***********************************************************************************


//***********************************************************************************
// function prototypes
//***********************************************************************************

#endif
