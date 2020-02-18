/**
 * This file is a part of Switch library for embedded devices.
 *
 * File:		Switchconfig.h
 * Created on:	29.03.2019
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/Switch
 */

/** UPDATES **
 *
 * 29.03.2019 - 2.5.1
 *  - Definice jsou presunuty do samostatneho souboru 'SwitchConfig.h'
 *
 * 05.02.2020 - 2.7.0
 *  - Ve vychozim nastaveni jsou vsechny moznosti zapnute.
 *
 * 12.02.2020 - 2.8.0
 *	- Nove definice pro arduino handler
 *  - Odstranene definice:
 *    - SWITCH_DEBUG
 *    - SWITCH_NAME_LENGTH
 *    - SWITCH_HANDLER_CHECK_COUNT
 *    - SWITCH_HANDLER_MAX_BUTTONS
 *  - Zmenena hodnota definice SWITCH_IMPLEMENT_CLICK_COUNT ze 100 na 3
 *
 *  16.02.2020 - 2.8.1
 *  - Uprava komentaru
 *
 *  16.02.2020 - 2.8.3
 *  - Pridana podminka pro preprocesor ktera zamezuje compilaci Arduino handleru
 *   na nearduino platforme.
 *
 *  17.02.2020 - 2.9.0
 *  - Pridana podpora atomickych operaci.
 */

#ifndef SRC_SWITCHCONFIG_H_
#define SRC_SWITCHCONFIG_H_

/**
 * Library version.
 */
#define Switch_Version "2.9.0"

/**
 * Set to 1 if you are programming Arduino like, otherwise 0.
 * CS: Nastavte na 1 pokud programujete arduino.
 */
#define SWITCH_ARDUINO	0

#if SWITCH_ARDUINO

// We need this!
#include "Arduino.h"

/**
 * The state of the button input (pin) in the pressed state.
 * Arduino like state:
 * - LOW = The button is switching against ground.
 * - HIGH = The button is switching against VCC.
 *
 *
 * CS: Stav tlacitka (pinu) ve stisknutem stavu.
 * 	Jako u arduina:
 * 	- LOW = tlacitko je spinane vuci zemi.
 * 	- HIGH = tlacitko je spinane vuci VCC.
 */
#define SWITCH_CLICK	LOW

/**
 * Macros for atomic operations.
 *
 * CS: Makra pro atomicke operace.
 */
#include <util/atomic.h>
#define SWITCH_ATOMIC_START	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
#define SWITCH_ATOMIC_END	}

#else

/**
 * Macros for atomic operations.
 * These macros are platform dependent.
 * These macros must be defined by the programmer at his discretion.
 *
 * Aaron Wisner library can be used as one of the solutions:
 * 	https://github.com/wizard97/SimplyAtomic (BSD Licence)
 *
 * CS: Makra pro atomicke operace.
 * 		Tato makra jsou zavisla na platforme.
 * 		Tato makra si musi programator definovat podle vlastniho uvazovani.
 *
 * 		Jako jedno z reseni muze byt pouzita knihovna od Aaron Wisner:
 * 		 https://github.com/wizard97/SimplyAtomic (BSD Licence)
 *
 * Example with SimplyAtomic by Aaron Wisner for ESP32:
 *
 * 	#include <SimplyAtomic.h>
 * 	#define SWITCH_ATOMIC_START	ATOMIC(){
 *  #define SWITCH_ATOMIC_END	}
 *
 *
 * Example with AVR standard atomic macros for AVR/Arduino:
 *
 *  #include <util/atomic.h>
 * 	#define SWITCH_ATOMIC_START	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
 *  #define SWITCH_ATOMIC_END	}
 *
 */
#include <util/atomic.h>
#define SWITCH_ATOMIC_START	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
#define SWITCH_ATOMIC_END	}

#endif

/**
 * Time in milliseconds to prevent the condition "bouncing" button.
 *
 * CS: Cas v milisekundach, pro zamazeni stavu "skakajiciho tlacitka".
 */
#define SWITCH_TIME_DEBOUNCE			40

/**
 * Set to 1 if you wanna have a hold BUTTON functionality, otherwise 0.
 *
 * CS: Nastavte na 1, pokud chcete mit funkcionalitu detekce
 *  udrzovaneho tlacitka.
 */
#define SWITCH_IMPLEMENT_CLICK_HELD	1

/**
 * Set to 1 if you wanna have a time of hold BUTTON in milliseconds
 *  functionality, otherwise 0.
 *
 * CS: Nastavte na 1, pokud chcete mit funkcionalitu mereni doby po kterou je
 *  tlacitko udrzovane ve stisknutem stavu.
 */
#define SWITCH_IMPLEMENT_CLICK_HELD_TIME	1

/**
 * Set (count of clicks) to positive value if you wanna to have
 *  Click Counter functionality. otherwise 0.
 *  Atention! Minimal value is 0! Maximalm value is 255!
 *
 * CS: Nastavte na pozitivni celociselnou hodnotu, pokud chcete mit
 *  funkcionalitu pocitani stisku tlacitka.
 *  Pozor! Minimalni hodnota je 0! Maximalni hodnota je 255!
 */
#define SWITCH_IMPLEMENT_CLICK_COUNT 3

/////////
///
/// Check configurations.
///
/////////

#if SWITCH_IMPLEMENT_CLICK_HELD_TIME and !SWITCH_IMPLEMENT_CLICK_HELD
#error "Not allowed, You must enable the 'Keep button pressed' (see SWITCH_IMPLEMENT_CLICK_HELD) feature."
#endif

#endif /* SRC_SWITCHCONFIG_H_ */

