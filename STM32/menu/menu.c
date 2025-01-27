/*
 * menu.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Ferran
 */

#include "menu.h"

uint8_t lineas[50] = "----------------------------------------------\r\n";
uint8_t saludo[50] = "                BIENVENIDO                    \r\n";

uint8_t blank[50] = "                                              \r\n";

uint8_t inicio[50] = " Ingrese el numero segun la opcion deseada    \r\n";

// Opciones generales
uint8_t opcn_0[50] = "    0. Detener el sistema                     \r\n";
uint8_t opcn_1[50] = "    1. Iniciar el sistema		                \r\n";
uint8_t opcn_2[50] = "    2. Posicionar la barrera                  \r\n";
uint8_t opcn_3[50] = "    1. Cambiar velocidad                      \r\n";

// Opcion 1 (Seleccion de velocidad)
uint8_t opc1_1[50] = " Indique la velocidad de la cinta             \r\n";
uint8_t opc1_2[50] = " Indique el cambio a otra velocidad           \r\n";
uint8_t opc1_3[50] = "    1. Baja  [ 10.8 s/m ]                     \r\n";
uint8_t opc1_4[50] = "    2. Media [ 5.6  s/m ]                     \r\n";
uint8_t opc1_5[50] = "    3. Alta  [ 3.6  s/m ]                     \r\n";

// Opcion 2 (Movimiento de la barrera)
uint8_t opc2_1[50] = " Indique la posicion de la barrera            \r\n";
uint8_t opc2_2[50] = "    1. Desviando                              \r\n";
uint8_t opc2_3[50] = "    2. Sin desviar                            \r\n";

// Opcion 4 (Error en la deteccion de la caja)
uint8_t MSG_cajaND[50] = "ERROR : Caja no detectada en el segundo sensor\r\n";

// Especiales
uint8_t clear[] = "\e[2J";

void menu_seleccion(int opc, int vel) {

	HAL_UART_Transmit(&huart3, clear, sizeof(clear), 100);

	// ===========================================================
	// Menu a mostrar cuando se inicia el sistema / Sistema detenido
	if (opc == 0 || opc == 4) {
		if (opc == 0) {
			HAL_UART_Transmit(&huart3, lineas, sizeof(lineas), 100);
			HAL_UART_Transmit(&huart3, lineas, sizeof(lineas), 100);
			HAL_UART_Transmit(&huart3, saludo, sizeof(lineas), 100);
			HAL_UART_Transmit(&huart3, lineas, sizeof(lineas), 100);

		} else {
			HAL_UART_Transmit(&huart3, MSG_cajaND, sizeof(MSG_cajaND), 100);

		}

		HAL_UART_Transmit(&huart3, blank, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, inicio, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opcn_1, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opcn_2, sizeof(lineas), 100);
	}

	// ===========================================================
	// Seleccion de velocidades
	if (opc == 1) {
		HAL_UART_Transmit(&huart3, blank, sizeof(lineas), 100);

		// Condicionamos si se inicia de cero o es un cambio de velocidad
		if (vel == 0) {
			HAL_UART_Transmit(&huart3, opc1_1, sizeof(lineas), 100);
		} else {
			HAL_UART_Transmit(&huart3, opc1_2, sizeof(lineas), 100);
		}

		if (vel != 100) {
			HAL_UART_Transmit(&huart3, opc1_3, sizeof(lineas), 100);
		}
		if (vel != 200) {
			HAL_UART_Transmit(&huart3, opc1_4, sizeof(lineas), 100);
		}
		if (vel != 300) {
			HAL_UART_Transmit(&huart3, opc1_5, sizeof(lineas), 100);
		}

	}

	// ===========================================================
	// Cambio de la posicion de la barrera
	if (opc == 2) {
		HAL_UART_Transmit(&huart3, blank, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opc2_1, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opc2_2, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opc2_3, sizeof(lineas), 100);
	}

	// ===========================================================
	// Sistema en marcha
	if (opc == 3) {
		HAL_UART_Transmit(&huart3, lineas, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, inicio, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opcn_0, sizeof(lineas), 100);
		HAL_UART_Transmit(&huart3, opcn_3, sizeof(lineas), 100);
	}

	return;
}
