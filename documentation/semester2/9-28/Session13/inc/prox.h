//
// COMP-GENG 422 - Tom Lupfer
//
// Proximity measurement module header file
//

#ifndef PROX_H_
#define PROX_H_

#define PROX_QUEUE_ITEM_SIZE	sizeof(uint16_t)
#define PROX_QUEUE_LENGTH		10
#define PROX_TASK_PRI			1
#define PROX_TASK_STACK			1000


void ProxTask(void *pvParameters);

#endif // PROX_H_
