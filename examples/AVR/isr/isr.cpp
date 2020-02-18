/**
 * cmd:	avrdude -v -patmega328p -carduino -P/dev/ttyUSB0 -b115200 -Uflash:w:/home/denis/Dropbox/Projects/github/temp/Release/temp.hex:i
 *
 *
 * This file is a part of examples of a Switch library.
 *
 * Created on:  	17.02.2020
 * Author:    		Denis Colesnicov <eugustus@gmail.com>
 * Licence:   		MIT
 * Home:    		https://github.com/colesnicov/Switch
 * Description:		Priklad pouziti na AVR.
 *
 * Note:    		Pozor! Testovane pouze na ATMEGA328P!
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "Switch/SwitchArduino.hpp"
#include "Switch/SwitchConfig.h"
#include "Switch/Switch.hpp"
#include "uart/uart.hpp"
#include "utils/avr.hpp"
#include "millis/millis.hpp"

// Definice pinu
#define BTN_non	0
#define BTN_one 2
#define BTN_two 3

// Objekty predstavujici tlacitka
Switch btn_two;
Switch btn_one;

// Piny pro tlacitka
#define BTN_PIN			PIND
#define BTN_DIR			DDRD
#define BTN_PORT		PORTD
#define BTN_ONE_PIN		PIND2 /*!< PD2 */
#define BTN_TWO_PIN		PIND3 /*!< PD3 */

// Prevent before clicking on multiple buttons at once.
volatile static uint8_t last_btn_clicked = BTN_non;

ISR (INT0_vect) {
	uint32_t ms = millis();

	if (!(BTN_PIN & (1 << BTN_ONE_PIN))) {  // The button is pressed
		if (last_btn_clicked == BTN_non) { // The other button is not pressed
			btn_one.setClickStart(ms); // Set to clicked
			last_btn_clicked = BTN_one; // Remember the ID of the pressed button
		}
	} else if (last_btn_clicked == BTN_one) { // The last pressed button ID is the same
		btn_one.setClickEnd(ms); // Set to released
		last_btn_clicked = BTN_non; // Set the ID of the pressed button to 0
	}
}

ISR(INT1_vect) {
	uint32_t ms = millis();

	if (!(BTN_PIN & (1 << BTN_TWO_PIN))) {
		if (last_btn_clicked == BTN_non) {
			btn_two.setClickStart(ms);
			last_btn_clicked = BTN_two;
		}
	} else if (last_btn_clicked == BTN_two) {
		btn_two.setClickEnd(ms);
		last_btn_clicked = BTN_non;
	}
}

extern "C" int main() {

// Inicializace hodin a UART0
	clock_init();
	uart_init(9600);

// Nastavuji piny jako vystup.
	SetAsInput(BTN_DIR, BTN_ONE_PIN);
	SetAsInput(BTN_DIR, BTN_TWO_PIN);

// Zapinam interni PULL_UP rezistory.
	/* Odkomentovat, pokud nejsou pripojeny externi PULLUP odpory */
//	SetAsOn(BTN_PORT, BTN_ONE_PIN);
//	SetAsOn(BTN_PORT, BTN_TWO_PIN);

// Navesuji preruseni.
	EICRA |= (1 << ISC00) | (1 << ISC10); // INT0 a INT1 na obe hrany
	EIMSK |= (1 << INT0) | (1 << INT1); // Zapinam INT0 a INT1

// Povoluji globalni preruseni
	sei();

	uart_puts((char*) "Switch Version ");
	uart_puts((char*) Switch_Version);
	uart_puts((char*) "\n");
	uart_puts((char*) "Ready!\n\n");

	while (true) {

// Vypis stavu tlacitek.
		if (btn_one.isClicked()) {
			uart_puts((char*) "Button 1 clicked!\n");
		}

		if (btn_two.isClicked()) {
			uart_puts((char*) "Button 2 clicked!\n");
		}

#if SWITCH_IMPLEMENT_CLICK_HELD
		{
			if (btn_one.isHolded(millis())) {
				uart_puts((char*) "Button 1 holded!\n");
			}

			if (btn_two.isHolded(millis())) {
				uart_puts((char*) "Button 2 holded!\n");
			}
		}
#endif

#if SWITCH_IMPLEMENT_CLICK_HELD_TIME
		{
			if (btn_one.isHolded(millis())) {
				uart_puts((char*) "Button 1 has holded state: '");
				char buf[4] = { '\0' };
				itoa(btn_one.getHoldedTime(millis()), buf, 10);
				uart_puts(buf);
				uart_puts((char*) "' ms\n");
			}

			if (btn_two.isHolded(millis())) {
				uart_puts((char*) "Button 2 has holded state: '");
				char buf[4] = { '\0' };
				itoa(btn_two.getHoldedTime(millis()), buf, 10);
				uart_puts(buf);
				uart_puts((char*) "' ms\n");
			}
		}
#endif

#if SWITCH_IMPLEMENT_CLICK_COUNT > 0
		{
// Prvni tlacitko je bez automatickeho resetovani pocitadla stisku tlacitka.
			uint8_t count1 = btn_one.getClickCount();

// Druhe tlacitko s automatickym resetovanim pocitadla stisknuti tlacitka.
			uint8_t count2 = btn_two.getClickCountWithReset();

			if (count1 > 0) {
				uart_puts((char*) "Button 1 has '");
				char buf[4] = { '\0' };
				itoa(count1, buf, 10);
				uart_puts(buf);
				uart_puts((char*) "' clicks\n");
			}

			if (count1 >= SWITCH_IMPLEMENT_CLICK_COUNT)
// Pokud je dosazen limit poctu stisknuti, proved reset pocitadla stisku tlacitka
			{
				btn_one.cleanClickCount();
				uart_puts((char*) "Reset clicks counter.\n");
			}

			if (count2 > 0) {
				uart_puts((char*) "Button 2 has '");
				char buf[4] = { '\0' };
				itoa(count2, buf, 10);
				uart_puts(buf);
				uart_puts((char*) "' clicks\n");
			}
		}
#endif

// Pockame 2 sekundy v necinosti
		delay(2000);

	}
}
