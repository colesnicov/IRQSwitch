#pragma once

/**
 * This file is a part of Switch Arduino library.
 *
 * File:		SwitchArduino.hpp
 * Created on:	12.02.2020
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/Switch
 * Version:		2.9.0
 */

/**
 * @todo	Pridat definici poctu tlacitek do souboru s definicemi.
 * 			Pocet tlacitek by mel odpovidat maximalnimu mnozstvi pinu MCU + 1
 */

#include "SwitchConfig.h"

#if SWITCH_ARDUINO

#include <stdint.h>

#include "Switch.hpp"

class SwitchArduino {
public:

	/**
	 * Constructor
	 * Do nothing.
	 */
	SwitchArduino();

	/**
	 * Add button to "watch".
	 *
	 * CS: Prida tlacitko ke "hlidani".
	 *
	 * @param	b*	Pointer to button.
	 * @param	pin	Pin number, 0 ... max arduino pin number
	 *
	 */
	void AddButton(Switch *b, uint8_t pin);

	/**
	 * Update states.
	 *
	 * CS: Aktualizovat stav tlacitek.
	 *
	 * @note:	Call in main loop or in interrupt routenes.
	 *
	 * @note	CS: volat v hlavni smycce nebo v rutine preruseni.
	 *
	 * @param ms Current time in milliseconds.
	 */
	void Update(uint32_t ms);

	/**
	 * Return a pointer to the button by their PIN number.
	 *
	 * CS: Vrati ukazatel na tlacitko podle jeho pinu.
	 *
	 * @param id	ID of button.
	 *
	 * @return	Switch*	Pointer to object.
	 */
	Switch* GetButton(uint8_t pin);

private:

	Switch *m_buttons[255] = { nullptr }; /*!< List of buttons. */
	uint8_t m_last_clicked = 255; /*!< ID of last clicket button */
};

#endif
