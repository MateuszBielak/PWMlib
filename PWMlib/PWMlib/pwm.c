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
 *	WYMAGANE WYWYO£ANIE FUNKCJI sei() w pliku main.c
 *
 * 	WYMAGANE BIBLIOTEKI : <avr/io.h> <avr/interrupt.h>
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 * 	pwm.c
 */



#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pwm.h"
typedef uint8_t u8;
typedef uint16_t u16;
 // zmienne u¿ywane w przerwaniu
volatile u8 pwm1, pwm2, pwm3, pwm4;



static inline void soft_pwm_dir_out(void){
#if USE_PWM_CHANNEL1 == 1
	DDR(PWM_PORT_1) |= (1<<PWM_PIN_1);
#endif
#if USE_PWM_CHANNEL2 == 1
	DDR(PWM_PORT_2) |= (1<<PWM_PIN_2);
#endif
#if USE_PWM_CHANNEL3 == 1
	DDR(PWM_PORT_3) |= (1<<PWM_PIN_3);
#endif
#if USE_PWM_CHANNEL4 == 1
	DDR(PWM_PORT_4) |= (1<<PWM_PIN_4);
#endif
}

// -------------------------------------------------------------------
//						INICJALIZACJA PWM
// -------------------------------------------------------------------
#if USE_SOFT_PWM == 1
void soft_PWM_init(void){
	// kana³y PWM - wyjœcie
	soft_pwm_dir_out();
//-----------------------USTAWIENIA TIMERA----------------------------
	//Tryb NORMAL
	TCCR0 |= (1<<CS00); // preskaler /1
	TIMSK |= (1<<TOIE0); // zezwolenie na przerwania OVF
	TCNT0 = 100;

}
#endif

 	 	 // sprzêtowy kana³ PWM
#if USE_PWM_HARDWARE_CHANNEL == 1
void hard_PWM_init(void){
	DDR(HARD_PWM_PORT) |= (1<<HARD_PWM_PIN);
	TCCR2 |= (1<<WGM20) | (1<<WGM21); // tryb fastPWM
	TCCR2 |= (1<<CS20); // preskaler /1
	TCCR2 |= (1<<COM21); // Sterowanie VCC
	OCR2 = 0;
}
#endif
//---------------------------------------------------------------------
//						PROCEDURY PRZERWAÑ
//---------------------------------------------------------------------

ISR( TIMER0_OVF_vect ) {
	TCNT0 = 100;
	static uint8_t counter;

#if USE_PWM_CHANNEL1 == 1
	if(counter <= pwm1) SET_PWM1_HIGH; else SET_PWM1_LOW;
	if(pwm1 == 0) SET_PWM1_LOW;
#endif
#if USE_PWM_CHANNEL2 == 1
	if(counter <= pwm2) SET_PWM2_HIGH; else SET_PWM2_LOW;
	if(pwm2 == 0) SET_PWM2_LOW;
#endif
#if USE_PWM_CHANNEL3 == 1
	if(counter <= pwm3) SET_PWM3_HIGH; else SET_PWM3_LOW;
	if(pwm3 == 0) SET_PWM3_LOW;
#endif
#if USE_PWM_CHANNEL4 == 1
	if(counter <= pwm4) SET_PWM4_HIGH; else SET_PWM4_LOW;
	if(pwm4 == 0) SET_PWM4_LOW;
#endif


	counter++;
	if(counter>255) counter = 0;
}





//--------------------------------------------------------------------
//					FUNKCJE DOSTÊPNE DLA U¯YTKOWNIKA
//--------------------------------------------------------------------
	// ustawianie wype³nienia pwm na poszczególnych kana³ach
#if USE_SOFT_PWM == 1
void soft_PWM_write(u8 channel, u16 width){
#if GND_VCC_ON_SWITCH == 0 // wspólna anoda np
	  width = 255-width;
#endif
	switch(channel){
		case 1:	pwm1 = width; break;
		case 2: pwm2 = width; break;
		case 3: pwm3 = width; break;
		case 4: pwm4 = width; break;
	}
}
#endif
	// ustawianie wype³nienia na sprzêtowym kanale PWM
#if USE_PWM_HARDWARE_CHANNEL == 1
void hard_PWM_write(u8 width){
#if GND_VCC_ON_SWITCH == 0
	width = 255-width;
#endif
	OCR2 = width;
}
#endif
