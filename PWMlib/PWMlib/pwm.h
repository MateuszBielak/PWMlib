/*	Programowa obs�uga modulacji szeroko�ci� impulsu PWM
 * 	Znajdzie zastosowanie w sterowaniu jasno�ci� o�wietlenia, sterowaniem
 * 	diodami wielokolorowymi RGB, sterowaniu silnikami elektrycznymi DC,
 * 	serwomechanizmam i nie tylko.
 *
 * 	Umo�liwia sterowanie zar�wno za pomoc� GND (urz�dzenie w��czone w trakcie
 * 	trwania stanu niskiego) lub VCC (urz�dzenie w��czone w trakcie trwania
 * 	stanu wysokiego)
 *
 *  ZALECANE TAKTOWANIE PROCESORA TO 16MHZ (dla innych wymagane zmiany w
 *  ustawieniach timer�w)
 *
 * WYMAGANE WYWYO�ANIE FUNKCJI sei() w pliku main.c
 *
 * 	WYMAGANE BIBLIOTEKI : <avr/io.h> <avr/interrupt.h>
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	pwm.h
 */

#ifndef PWMLIB_PWM_H_
#define PWMLIB_PWM_H_
// skr�cenie pisania zmiennej jednobajtowej
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

//-------------------------------------------------------------------------
// 						USTAWIENIA PROGRAMU
//-------------------------------------------------------------------------
#define USE_SOFT_PWM	1
#define USE_HARD_PWM 	1

// Urz�dzenie w��czone za przez podanie stanu niskiego/wysokiego - 0/1
#define GND_VCC_ON_SWITCH 1 // np dla diody RGB ze wsp�ln� anod�

#define USE_PWM_CHANNEL1	1 // aktywacja poszczeg�lnych kana��w PWM
#define USE_PWM_CHANNEL2	1 // je�li potrzebujemy tylko jednemu to
#define USE_PWM_CHANNEL3	1 // aktywujemy tylko jeden dzi�ki temu
#define USE_PWM_CHANNEL4	0 // oszcz�dzamy pami�c procesora

#define USE_PWM_HARDWARE_CHANNEL	1 // aktywacja sprz�towego PWM, aby go wykorzystac jednocze�nie z programowym musimy
// zaznaczyc USE_COMP_ISR na 0 i USE_OVF_ISR na 1



//--------------------------------------------------------------------------
// 					 MAKRA UPRASZCZAJ�CE DOST�P DO PORT�W
//--------------------------------------------------------------------------
// PORT - wyj�cie
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// PIN - wej�cie
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// DDR - kierunek
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


//--------------------------------------------------------------------------
//						MAKRA PIN�W I PORT�W uC
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
void hard_PWM_init(void);					// inicjalizacja sprz�towego PWM
void soft_PWM_write(u8 channel, u16 width); // zmiana wype�nienia na danym pinie PWM
void hard_PWM_write(u8 width);				// zmiana wype�nienia na sprz�towym kanale PWM

#endif /* PWMLIB_PWM_H_ */
