/*
 * stepper.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Ferran
 */

#include "stepper.h"


uint8_t full_step[4][4] = {
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 1},
		{1, 0, 0, 1}
};

uint8_t full_step_inv[4][4] = {
		{0, 0, 1, 1},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 1}
};


// Configuracion de los pines para el stepper
const STEPPER_PINS STEPPER = {
		{GPIOA, GPIOA, GPIOA, GPIOA},
		{GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6}
};


// Da un pulso al stepper en un sentido u otro
void init_stepper(int pulse, int dir) {
	if (dir == 1) {
		HAL_GPIO_WritePin(STEPPER.gpio_port[0], STEPPER.in_pin[0],
				full_step[pulse][0]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[1], STEPPER.in_pin[1],
				full_step[pulse][1]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[2], STEPPER.in_pin[2],
				full_step[pulse][2]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[3], STEPPER.in_pin[3],
				full_step[pulse][3]);
	} else if (2) {
		HAL_GPIO_WritePin(STEPPER.gpio_port[0], STEPPER.in_pin[0],
				full_step_inv[pulse][0]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[1], STEPPER.in_pin[1],
				full_step_inv[pulse][1]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[2], STEPPER.in_pin[2],
				full_step_inv[pulse][2]);
		HAL_GPIO_WritePin(STEPPER.gpio_port[3], STEPPER.in_pin[3],
				full_step_inv[pulse][3]);
	}

}

void stop_stepper() {
	HAL_GPIO_WritePin(STEPPER.gpio_port[0], STEPPER.in_pin[0], 0);
	HAL_GPIO_WritePin(STEPPER.gpio_port[1], STEPPER.in_pin[1], 0);
	HAL_GPIO_WritePin(STEPPER.gpio_port[2], STEPPER.in_pin[2], 0);
	HAL_GPIO_WritePin(STEPPER.gpio_port[3], STEPPER.in_pin[3], 0);
}
