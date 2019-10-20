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
 * WYMAGANE WYWYO£ANIE FUNKCJI sei() w pliku main.c
 *
 * 	WYMAGANE BIBLIOTEKI : <avr/io.h> <avr/interrupt.h>
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	pwm.h
 */

#ifndef PWMLIB_PWM_H_
#define PWMLIB_PWM_H_
// skrócenie pisania zmiennej jednobajtowej
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

//-------------------------------------------------------------------------
// 						USTAWIENIA PROGRAMU
//-------------------------------------------------------------------------
#define USE_SOFT_PWM	1
#define USE_HARD_PWM 	1

// Urz¹dzenie w³¹czone za przez podanie stanu niskiego/wysokiego - 0/1
#define GND_VCC_ON_SWITCH 1 // np dla diody RGB ze wspóln¹ anod¹

#define USE_PWM_CHANNEL1	1 // aktywacja poszczególnych kana³ów PWM
#define USE_PWM_CHANNEL2	1 // jeœli potrzebujemy tylko jednemu to
#define USE_PWM_CHANNEL3	1 // aktywujemy tylko jeden dziêki temu
#define USE_PWM_CHANNEL4	0 // oszczêdzamy pamiêc procesora

#define USE_PWM_HARDWARE_CHANNEL	1 // aktywacja sprzêtowego PWM, aby go wykorzystac jednoczeœnie z programowym musimy
// zaznaczyc USE_COMP_ISR na 0 i USE_OVF_ISR na 1



//--------------------------------------------------------------------------
// 					 MAKRA UPRASZCZAJ¥CE DOSTÊP DO PORTÓW
//--------------------------------------------------------------------------
// PORT - wyjœcie
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// PIN - wejœcie
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// DDR - kierunek
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


//--------------------------------------------------------------------------
//						MAKRA PINÓW I PORTÓW uC
//--------------------------------------------------------------------------
#define HARD_PWM_PORT D //pin OCx
#define HARD_PWM_PIN 7

#if USE_PWM_CHANNEL1 == 1
#define PWM_PORT_1 A
#define PWM_PIN_1 0
#endif

#if USE_PWM_CHANNEL2 == 1
#define PWM_PORT_2 A
#define PWM_PIN_2 1
#endif

#if USE_PWM_CHANNEL3 == 1
#define PWM_PORT_3 A
#define PWM_PIN_3 2
#endif

#if USE_PWM_CHANNEL4 == 1
#define PWM_PORT_4 A
#define PWM_PIN_4 3
#endif

//--------------------------------------------------------------------------
//				MAKRA DO ZMIENIANA STANU LOGICZNEGO NA PINACH PWM
//--------------------------------------------------------------------------
#if USE_PWM_CHANNEL1 == 1
#define SET_PWM1_HIGH PORT(PWM_PORT_1) |= (1<<PWM_PIN_1)
#define SET_PWM1_LOW PORT(PWM_PORT_1) &= ~(1<<PWM_PIN_1)
#endif

#if USE_PWM_CHANNEL2 == 1
#define SET_PWM2_HIGH PORT(PWM_PORT_2) |= (1<<PWM_PIN_2)
#define SET_PWM2_LOW PORT(PWM_PORT_2) &= ~(1<<PWM_PIN_2)
#endif

#if USE_PWM_CHANNEL3 == 1
#define SET_PWM3_HIGH PORT(PWM_PORT_3) |= (1<<PWM_PIN_3)
#define SET_PWM3_LOW PORT(PWM_PORT_3) &= ~(1<<PWM_PIN_3)
#endif

#if USE_PWM_CHANNEL4 == 1
#define SET_PWM4_HIGH PORT(PWM_PORT_4) |= (1<<PWM_PIN_4)
#define SET_PWM4_LOW PORT(PWM_PORT_4) &= ~(1<<PWM_PIN_4)
#endif
//--------------------------------------------------------------------------
// 					DEKLARACJE FUNKCJI I ZMIENNYCH PROJEKTU
//--------------------------------------------------------------------------

extern volatile u8 pwm1, pwm2, pwm3, pwm4;



void soft_PWM_init(void);					// inicjalizacja programowego PWM
void hard_PWM_init(void);					// inicjalizacja sprzêtowego PWM
void soft_PWM_write(u8 channel, u16 width); // zmiana wype³nienia na danym pinie PWM
void hard_PWM_write(u8 width);				// zmiana wype³nienia na sprzêtowym kanale PWM

#endif /* PWMLIB_PWM_H_ */
