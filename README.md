# Desvío de cajas mediante barrera automática

Este proyecto implementa un sistema de clasificación de cajas en una cinta transportadora, utilizando sensores y un microcontrolador STM32 para su control. Fue desarrollado como parte de la asignatura **Microcontroladores y Electrónica de Potencia** en la carrera de **Ingeniería en Mecatrónica** en la **Universidad Nacional de Cuyo**.

## Descripción

El objetivo del proyecto es identificar y desviar cajas de color blanco mientras que las cajas de color negro continúan por el canal principal. Este sistema simula los procesos de clasificación que se encuentran en aeropuertos o líneas de ensamblaje industrial.

### Componentes principales:
- **Microcontrolador STM32F103C8T6 (Bluepill)**: Control del sistema.
- **Motor paso a paso 28BYJ-48**: Movimiento de la cinta transportadora.
- **Servomotor SG92R**: Posicionamiento de la barrera.
- **Sensores infrarrojos TCRT5000**: Detección de cajas.
- **LCD Hitachi HDD44780 16x2**: Visualización de información.
- **Leds**: Indicadores de proceso y errores.
- **Comunicación serial**: Instrucciones para microncotrolador.

### Funcionalidad:
1. Las cajas son transportadas por una cinta principal.
2. Los sensores identifican cajas blancas y activan un servomotor que posiciona la barrera para desviar las cajas hacia un segundo canal.
3. Se valida el correcto desvío de las cajas con un segundo sensor.
4. El sistema se detiene y genera alertas visuales en caso de fallos en el proceso.

## Estructura del Proyecto

El proyecto incluye:
- Configuración y programación del microcontrolador STM32 utilizando **STM32CubeIDE**.
- Control de los motores (PAP y servomotor).
- Implementación de sensores para detección y lógica de control.
- Interacción con el usuario mediante un menú de configuración y visualización en el LCD.

## Autores

- **Ferran Martinez**

## Institución

- **Universidad Nacional de Cuyo (UNCuyo)**
- Ingeniería en Mecatrónica
- Asignatura: Microcontroladores y Electrónica de Potencia
