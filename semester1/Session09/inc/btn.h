//
// COMP-GENG 421 - Tom Lupfer
//
// Button module header file
//

#ifndef BTN_H_
#define BTN_H_

#include "gpio.h"


// PC13 <- User button (blue) - active low
#define BTN_IS_PRESSED()	(!GPIO_PC13_IS_SET())

#endif	// BTN_H_
