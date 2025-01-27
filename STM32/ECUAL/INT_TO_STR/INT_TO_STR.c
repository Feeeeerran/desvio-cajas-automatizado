/*
 * INT_TO_STR.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Ferran
 */

#include "INT_TO_STR.h"


void int_to_str(int num, char str[]) {
	int i = 0;

	// En caso de ser cero retornamos cero
	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	// Procesamos cada numero
	while (num != 0) {
		int rem = num % 10;
		str[i++] = rem + '0';
		num = num / 10;
	}

	// Colocamos al final el retorno
	str[i] = '\0';

	// Invertimos la cadena
	int start = 0;
	int end = i - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	return;
}
