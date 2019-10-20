/*	Programowa obs³uga modulacji szerokoœci¹ impulsu PWM
 * 	Znajdzie zastosowanie w sterowaniu jasnoœci¹ oœwietlenia, sterowaniem
 * 	diodami wielokolorowymi RGB, sterowaniu silnikami elektrycznymi DC,
 * 	serwomechanizmam i nie tylko.
 *
 * 	Umo¿liwia sterowanie zarówno za pomoc¹ GND (urz¹dzenie w³¹czone w trakcie
 * 	trwania stanu niskiego) lub VCC (urz¹dzenie w³¹czone w trakcie trwania
 * 	stanu wysokiego)
 *
 *  ZALECANE TAKTOWANIE PROCESORA TO 16MHZ (dla innych wymagane zmiany w
 *  ustawieniach timerów)
 *
 * 	WYMAGANE BIBLIOTEKI : <avr/io.h> <avr/interrupt.h>
 *
 * 	WYMAGANE WYWYO£ANIE FUNKCJI sei() w pliku main.c
 *
 * 	Rozmiar biblioteki z przyk³adowym programem po kompilacji to 622 bajty
 * 	Dla porównania, podobny program w Arduino zajmuje dwukrotnie wiêcej pamiêci flash
 * 	Procesor u¿yty w projekcje to ATmega32
 *
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	main.c
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "PWMlib/pwm.h"

#define RED_CH 1
#define GREEN_CH 2
#define BLUE_CH 3

#define COLOR_HEX 1

void color_set(u8 red, u8 green, u8 blue);
void color_hex(u32 hex_color);


//------------------------------------------------------------------------------------
//								FUNKCJE DLA DIODY RGB
//------------------------------------------------------------------------------------

void color_set(u8 red, u8 green, u8 blue){
	soft_PWM_write(RED_CH, red);
	soft_PWM_write(GREEN_CH, green);
	soft_PWM_write(BLUE_CH, blue);
}
void color_hex(u32 hex_color){
	color_set((hex_color & 0xFF0000) >> 16, (hex_color & 0x00FF00) >> 8, (hex_color & 0x0000FF));
}



int main(void) {
sei();

 soft_PWM_init();
 hard_PWM_init();


 while(1){
// dioda swieci siê wszystkimi kolorami palety RGB
//
	  for (u16 i = 0; i <= 255; i++) {
		 color_set(255 - i, i, 0);
		 hard_PWM_write(i);
	    _delay_us(100);
	  }

	  for (u16 i = 0; i <= 255; i++) {
		 color_set(0, 255 - i, i);
	    _delay_us(100);
	  }

	  for (u16 i = 0; i <= 255; i++) {
		 color_set(i, 0, 255 - i);
		 hard_PWM_write(255-i);
	    _delay_us(100);
	  }
#if COLOR_HEX == 1
	  color_hex(0xffab02);
#endif
   }
}

