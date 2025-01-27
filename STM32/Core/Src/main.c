/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#include "../../ECUAL/LCD16x2/LCD16x2.h"
#include "../../ECUAL/INT_TO_STR/INT_TO_STR.h"

#include "../../menu/menu.h"
#include "../../stepper/stepper.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// ==========================================================
// Variables para UART
uint8_t RX_char = 0x00;
//\033[%dm %3d\033[m
uint8_t MSG_cajaD[] =
		"\n\033[0;31mCAJA DETECTADA:\033[0m Inicio del proceso de derivacion\r\n";

uint8_t MSG_cajaP[] =
		"\nCAJA PROCESADA: Caja detectada en el segundo sensor\r\n";
uint8_t MSG_cajaEC[] =
		"\nCAJA EN COLA: Nueva caja detectada durante el proceso\r\n";

uint8_t MSG_pulsadorP[] =
		"\nSISTEMA DETENIDO: Se pulso el interruptor de parada\r\n";

uint8_t MSG_sisMarcha[] =
		"\nEl sistema se encuentra procesando una caja, aguarde a que termine\r\n";
uint8_t MSG_opcIncorrecta[] = "\nOpcion incorrecta \r\n";

// ==========================================================
// Variables para el sistema
uint16_t contador_cajas = 0;
int pulso_stepper = 0;

uint16_t pulsos_proceso = 0;
uint16_t pulsos_caja_cola = 0;

const uint16_t PULSOS_XM = 1086;
const uint8_t D_SENSORES = 2;

// ESTADOS
// ==========================================================
enum sistema {
	detenido, pendiente, en_proceso, caja_procesada
} estado_sistema;

// ==========================================================
// Determinamos las frecuencias de los pulsos segun la configuracion del timer
// PSC = 3000
// ARR de 240 -> f = 100Hz
// ARR de 120 -> f = 200Hz
// ARR de 80 -> f = 300Hz
enum estado_motor_1 {
	parado = 0, v_baja = 240, v_media = 120, v_alta = 80
} motor_1;

// ==========================================================
// Estado del motor_2
enum estado_motor_2 {
	desviando = 4350, sin_desviar = 2625
} motor_2;

// ==========================================================
// Estado de las cajas (cola de cajas)
enum estado_cajas {
	cola_vacia, caja_en_cola
} cola_de_cajas;

// ==========================================================
// Para determinar la seleccion del usuario
enum opciones {
	none, por_iniciar, mover_barrera, baja = 100, media = 200, alta = 300
} seleccion_usuario;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM2_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */

	// ==========================================================
	// ==========================================================
	// Inicio del LCD
	LCD_Init();
	LCD_Clear();
	LCD_msg("Cajas procesadas", 1, 0);
//	LCD_msg("0",2,0);

	// ==========================================================
	// Para evitar el salto a PeriodElapsedCallback al iniciar los temporizadores con IT
//	TIM1->SR &= ~TIM_SR_UIF_Msk;

	// ==========================================================
	// Variables de estado iniciales
	estado_sistema = detenido;
	cola_de_cajas = cola_vacia;
	motor_1 = parado;
	motor_2 = sin_desviar;
	seleccion_usuario = none;

	// Estado de la compuerta (motor_2 inicialmente sin desviar)
	TIM3->CCR1 = motor_2;
	// Podria venir por flash

	// ==========================================================
	// Lanzamos el menu por UART
	menu_seleccion(0, 0);
	// Activamos las interrupciones para recibir por UART
	HAL_UART_Receive_IT(&huart3, &RX_char, 1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&& EXTI CALLBACKS &&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	UNUSED(GPIO_Pin);

	// ==========================================================
	// SENSOR 1
	// Se detecta una caja, pero se tiene en cuenta que quizas se este procesando
	// una caja en ese momento
	if (GPIO_Pin == sensor_1_Pin) {

		// Se detecto una caja, entonces se inicia el proceso de desviacion
		if (estado_sistema == pendiente) {
			estado_sistema = en_proceso;

			// Se inicia el contador de pulsos
			pulsos_proceso = 0;

			// Se indica con el led de proceso
			HAL_GPIO_WritePin(led_proceso_GPIO_Port, led_proceso_Pin, 1);

			// Se transmite por UART
			HAL_UART_Transmit(&huart3, MSG_cajaD, sizeof(MSG_cajaD), 100);

		}

		// En el caso de que una caja se este procesando, entonces se coloca
		// una caja en cola
		if (estado_sistema == en_proceso && motor_2 == desviando
				&& pulsos_proceso > (int) PULSOS_XM / 10) {
			cola_de_cajas = caja_en_cola;
		}

	}

	// ==========================================================
	// SENSOR 2
	// La caja fue derivada/procesada correctamente
	if (GPIO_Pin == sensor_2_Pin && estado_sistema == en_proceso
			&& motor_2 == desviando) {
		estado_sistema = caja_procesada;
		contador_cajas++;



		// Cambio del numero de cajas procesadas
		LCD_msg("", 2, 0);
		char aux[12];
		int_to_str((int) contador_cajas, aux);
		LCD_msg(aux, 2, 0);

		// Se comunica a traves de uart
		HAL_UART_Transmit(&huart3, MSG_cajaP, sizeof(MSG_cajaP), 100);

	}

	// ==========================================================
	// PULSADOR DE PARADA
	// Se usa para interrumpir y detener al sistema
	if (GPIO_Pin == pulsador_parada_Pin && estado_sistema != detenido) {
		estado_sistema = detenido;
		seleccion_usuario = none;

		// Detenemos motor_1 y motor_2
		HAL_TIM_Base_Stop_IT(&htim2);
		stop_stepper();
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

		// Mostramos menu de inicio
		HAL_UART_Transmit(&huart3, MSG_pulsadorP, sizeof(MSG_pulsadorP), 100);
		menu_seleccion(0, 0);
	}

}
// ---------------------------------------------------------------------------------------
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&& PeriodElapsed CALLBACKS &&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	UNUSED(htim);

	// ==========================================================
	// Movimiento de motor_1
	if (htim == &htim2) {

		init_stepper(pulso_stepper, (int) 1);

		// El pulso del stepper toma valores entre 0 y 3
		pulso_stepper++;
		if (pulso_stepper >= 4) {
			pulso_stepper = 0;
		}

		if (estado_sistema == en_proceso || estado_sistema == caja_procesada
				|| cola_de_cajas == caja_en_cola) {

			pulsos_proceso++;
			// Segundo contador de pulsos para la caja en cola
			if (cola_de_cajas == caja_en_cola) {
				pulsos_caja_cola++;
			}

			// Movimiento de motor_2 a la mitad del trayecto
			if ((pulsos_proceso >= (uint16_t) ((PULSOS_XM * D_SENSORES) / 2))
					&& estado_sistema == en_proceso) {

				motor_2 = desviando;
				TIM3->CCR4 = motor_2;
			}

			// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// La caja deberia haber alcanzado el segundo sensor
			if (pulsos_proceso >= (PULSOS_XM * D_SENSORES)) {

				// En caso de no haber detectado la segunda caja
				//  -> Se enciende el led de alerta
				//	-> Se para motor_1
				// 	-> Se avisa por sistema
				if (estado_sistema != caja_procesada) {
					estado_sistema = detenido;
					seleccion_usuario = none;

					// Se posiciona nuevamente y motor_2
					motor_2 = desviando;
					TIM2->CCR4 = motor_2;

					// Se detiene motor_1 y motor_2
					HAL_TIM_Base_Stop_IT(&htim2);
					stop_stepper();
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

					// Se enciende el led de alerta y apaga el de proceso
					HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
					HAL_GPIO_WritePin(led_proceso_GPIO_Port, led_proceso_Pin,
							0);

					// Se reinicia el menu por UART
					menu_seleccion(4, 0);
					return;
				}

				// Si habia una caja en cola, entonces movemos la cantidad de pulsos
				// contados de la caja en cola al proceso general
				if (cola_de_cajas == caja_en_cola) {
					cola_de_cajas = cola_vacia;
					estado_sistema = en_proceso;

					pulsos_proceso = pulsos_caja_cola;
					pulsos_caja_cola = 0;
					return;
				}

				// Finalmente si era una sola caja y fue procesada,
				// se coloca la barrera nuevamente a sin_desviar
				motor_2 = sin_desviar;
				TIM3->CCR4 = motor_2;

				// Se apaga el led de proceso
				HAL_GPIO_WritePin(led_proceso_GPIO_Port, led_proceso_Pin, 0);

				// Y se cambia al estado pendiente
				estado_sistema = pendiente;

			}
		}

	}

}
// ---------------------------------------------------------------------------------------

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&& UART CALLBACK &&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	UNUSED(huart);

	// ==========================================================
	// El sistema esta detenido, las opciones que se manejan son
	// 1. Iniciar
	// 2. Cambiar posicion de barrera
	if (seleccion_usuario == none && estado_sistema == detenido) {

		// Si esta encendido el led de alerta lo apagamos
		if (htim1.ChannelState[3] == HAL_TIM_CHANNEL_STATE_BUSY) {
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
		}

		if (RX_char == '1') {
			seleccion_usuario = por_iniciar;
			menu_seleccion(1, 0);
		} else if (RX_char == '2') {
			seleccion_usuario = mover_barrera;
			menu_seleccion(2, 0);
		} else {
			HAL_UART_Transmit(&huart3, MSG_opcIncorrecta,
					sizeof(MSG_opcIncorrecta), 100);
		}

		RX_char = 0x00;
		HAL_UART_Receive_IT(&huart3, &RX_char, 1);
		return;
	}

	// ==========================================================
	// El usuario va a seleccionar una velocidad de inicio / Se inicia el sistema
	if (seleccion_usuario == por_iniciar) {
		if (RX_char == '1') {
			seleccion_usuario = baja;
			motor_1 = v_baja;
		} else if (RX_char == '2') {
			seleccion_usuario = media;
			motor_1 = v_media;
		} else if (RX_char == '3') {
			seleccion_usuario = alta;
			motor_1 = v_alta;
		} else {
			HAL_UART_Transmit(&huart3, MSG_opcIncorrecta,
					sizeof(MSG_opcIncorrecta), 100);

			RX_char = 0x00;
			HAL_UART_Receive_IT(&huart3, &RX_char, 1);
			return;
		}

		// Menu -> sistema en marcha
		menu_seleccion(3, 0);
		// Set de estados
		estado_sistema = pendiente;

		// Iniciamos motor_1 y motor_2
		TIM2->ARR = motor_1;
		if (htim2.State != HAL_TIM_STATE_BUSY)
			HAL_TIM_Base_Start_IT(&htim2);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

		RX_char = 0x00;
		HAL_UART_Receive_IT(&huart3, &RX_char, 1);
		return;

	}

	// ==========================================================
	// Con el sistema en marcha solo se pueden hacer dos cosas, siempre
	// y cuando el sistema se encuentre en estado de pendiente
	// 0. Detener el sistema
	// 1. Cambiar velocidad
	if (estado_sistema == pendiente) {

		if (RX_char == '0') {
			estado_sistema = detenido;
			motor_1 = parado;
			seleccion_usuario = none;

			// Paramos a motor_1 y motor_2
			HAL_TIM_Base_Stop_IT(&htim2);
			stop_stepper();
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);

			// Mostramos menu de inicio
			menu_seleccion(0, 0);

		} else if (RX_char == '1') {
			seleccion_usuario = por_iniciar;
			menu_seleccion(1, (int) seleccion_usuario);

		} else {
			HAL_UART_Transmit(&huart3, MSG_opcIncorrecta,
					sizeof(MSG_opcIncorrecta), 100);
		}

		RX_char = 0x00;
		HAL_UART_Receive_IT(&huart3, &RX_char, 1);
		return;

	} else if (estado_sistema != pendiente && estado_sistema != detenido) {
		// El sistema esta en marcha pero procesando una caja, entonces
		// hay que esperar a que el proceso termine
		HAL_UART_Transmit(&huart3, MSG_sisMarcha, sizeof(MSG_sisMarcha), 100);

		RX_char = 0x00;
		HAL_UART_Receive_IT(&huart3, &RX_char, 1);
		return;
	}

	// ==========================================================
	// Con el sistema detenido, el usuario puede decidir la posicion inicial
	// de la barrera
	// 1. Desviando
	// 2. Sin desviar
	if (seleccion_usuario == mover_barrera && estado_sistema == detenido) {

		if (RX_char == '1') {
			motor_2 = desviando;
		} else if (RX_char == '2') {
			motor_2 = sin_desviar;
		} else {
			HAL_UART_Transmit(&huart3, MSG_opcIncorrecta,
					sizeof(MSG_opcIncorrecta), 100);

			RX_char = 0x00;
			HAL_UART_Receive_IT(&huart3, &RX_char, 1);
			return;
		}

		// Posicionamos la barrera
		TIM3->CCR4 = motor_2;
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

		// Seteamos menu y estado de seleccion
		seleccion_usuario = none;
		menu_seleccion(0, 0);

		RX_char = 0x00;
		HAL_UART_Receive_IT(&huart3, &RX_char, 1);
		return;
	}

	RX_char = 0x00;
	HAL_UART_Receive_IT(&huart3, &RX_char, 1);
	return;

}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
