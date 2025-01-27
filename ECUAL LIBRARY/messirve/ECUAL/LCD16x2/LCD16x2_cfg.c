/*
 * File: LCD16x2_cfg.c
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#include "LCD16x2.h"

const LCD16x2_CfgType LCD16x2_CfgParam = {
	GPIOB,
	GPIO_PIN_4,			// D4
	GPIO_PIN_5,			// D5
	GPIO_PIN_6,			// D6
	GPIO_PIN_7,			// D7
	GPIO_PIN_8,			// EN
	GPIO_PIN_9,     	// RS
	20
};
