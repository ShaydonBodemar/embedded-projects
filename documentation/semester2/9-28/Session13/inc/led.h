//
// COMP-GENG 422 - Tom Lupfer
//
// LED module header file
//

#ifndef LED_H_
#define LED_H_

#define LED_TASK_PRI			1
#define LED_TASK_STACK			500


void LedBlinkTask(void *pvParameters);

#endif // LED_H_
