//
// COMP-GENG 421 - Tom Lupfer
//
// Debug module header file
//

#ifndef DBG_H_
#define DBG_H_

#include "gpio.h"


// PA6 -> Debug pin
#define DBG_CLR()	(GPIO_PA6_CLR())
#define DBG_SET()	(GPIO_PA6_SET())
#define DBG_TOG()	(GPIO_PA6_TOG())

#endif	// DBG_H_
