/*
 * stepper.h
 *
 *  Created on: Aug 1, 2024
 *      Author: Ferran
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "stm32f1xx.h"





typedef struct
{
	GPIO_TypeDef * gpio_port[4];
	uint8_t in_pin[4];
} STEPPER_PINS;




void init_stepper(int pulse, int dir);
void stop_stepper();





#endif /* STEPPER_H_ */
