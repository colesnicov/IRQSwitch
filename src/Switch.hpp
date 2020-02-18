#pragma once

/**
 * This file is a part of Switch library for embedded devices.
 *
 * File:		Switch.hpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/Switch
 * Version:		2.8.1
 *
 * Note:		Attention! The getClickCountWithReset() method should only be used
 * 				sensibly if you use external interruption to change the
 * 				status of the buttons!!
 *
 * Note:		CS: Pozor! GetClickCountWithReset() ma smysl pouzivat pouze pokud
 * 				k pouzivate rutinu externiho preruseni pro tlacitka!!
 */

/** NOTES **
 *
 * - Nepouzivat 'setClick(...)' - Neni zrejmy koncept, k cemu je?
 */

/** UPDATES **
 *
 *
 * 26.03.2019 - 2.3.5
 *  - Pridana metoda pro zaznamenavani poctu kliknuti na tlacitko.
 *
 * 26.03.2019 - 2.3.6
 *  - Prejmenovana metoda 'setClickDown()' na setClickStart().
 *  - Prejmenovana metoda 'setClickUp()' na setClickEnd().
 *  - Upravena metoda 'getClickCount()' uz automaticky neresetuje svoje pocitadlo.
 *  - Pridana metoda 'getClickCountWithReset()' ktera automaticky resetuje svoje pocitadlo.
 *  - Odstranena staicka promena 'any_button_clicked'.
 *  - Oprava chyby ktera se tezko popisuje.
 *  - Oprava detekce dlouheho stisku tlacitka a inkrementace pocitadla.
 *    Drive se pocitadlo zvysovalo i pri dlouhem stisku tlacitka a to je spatne.
 *    Pokud je potreba puvodni funkcionalita, snadno se da implementovat v kodu.
 *
 * 28.03.2019 - 2.4.0
 *  - Pridana metoda 'getHoldedTime()'
 *  - Pridana metoda 'getHoldedTimeWithReset()'
 *
 * 28.03.2019 - 2.4.2
 *  - Uzpusobene pro lepsi produktivitu.
 *  - Poupraveny komentare.
 *
 * 28.03.2019 - 2.5.0
 *  - Metody 'bind(...)' a 'unbind(...)' jiz jsou pouzitelne.
 *
 * 29.03.2019 - 2.5.1
 *  - Definice jsou presunuty do samostatneho souboru 'SwitchConfig.h'
 *
 * 03.02.2020 - 2.6.1
 *  - Metoda 'isHolded()' nyni jako argument prijima cas v milisekundach.
 *  	Je tomu tak kvuli prenositelnosti mezi ruznymi platformami.
 *  	Driv tato metoda volala interne funkci 'millis()' coz omezovalo prenositelnost..
 *    
 * 05.03.2020 - 2.7.0
 *  Kvuli prenositelnosti mezi jinymi platformami..
 *  - Odstraneny metody:
 *    - uint8_t Switch::getPin()
 *    - void Switch::bind(uint8_t pin)
 *    - void Switch::bind(uint8_t pin, uint8_t mode)
 *    - void Switch::unbind()
 *  - Odstranena promena:
 *    - m_pin
 *  - Metoda 'getHoldedTime()' nyni jako argument prijima cas v milisekundach.
 *  - Metoda 'getHoldedTimeWithReset()' nyni jako argument prijima cas v milisekundach.
 *    Je tomu tak kvuli prenositelnosti mezi ruznymi platformami.
 *    Driv tato metoda volala interne funkci 'millis()' coz omezovalo prenositelnost..
 *
 * 12.02.2020 - 2.8.0
 *	- Vychozi hodnoty pro clenske promene jsou nastaveny v definici tridy.
 *	- Metoda Switch::getHoldedTimeWithReset(uint32_t _ms) vraci 0.
 *
 *  16.02.2020 - 2.8.1
 *  - Uprava komentaru
 *
 *  16.02.2020 - 2.8.2
 *  - Pridana metoda 'Switch::isPressed()'
 *
 *  17.02.2020 - 2.9.0
 *  - Implementace "atomiticidy"
 */

#include <stdint.h>

#include "SwitchConfig.h"

class Switch {
public:

	/**
	 * Constructor
	 * Do nothing
	 */
	Switch();

	/**
	 * Destructor
	 * Do nothing
	 */
	~Switch();

#if SWITCH_IMPLEMENT_CLICK_HELD

	/**
	 * Is the switch has helded?
	 *
	 * CS: Je tlacitko udrzovane ve stisknutem stavu?
	 *
	 * @return bool TRUE if is helded, otherwise FALSE
	 *
	 * @note See SWITCH_IMPLEMENT_CLICK_HELD definition
	 */
	bool isHolded(uint32_t ms);

#endif

#if SWITCH_IMPLEMENT_CLICK_COUNT > 0

	/**
	 * Get Click Count on the button.
	 *
	 * CS: Vrati pocet stisknuti tlacitka.
	 *
	 * @return uint8_t Count of clicks
	 *
	 * @note @see SWITCH_IMPLEMENT_CLICK_COUNT
	 */
	uint8_t getClickCount();

	/**
	 * Get click count on the Button with reset clicks counter.
	 *
	 * CS: Vrati pocet stisknuti tlacitka a zaroven vynuluje pocitadlo.
	 *
	 * @return uint8_t Count of clicks
	 *
	 * @note @see SWITCH_IMPLEMENT_CLICK_COUNT
	 */
	uint8_t getClickCountWithReset();

	/**
	 * Reset clicks counter.
	 *
	 * CS: Vynuluje pocitadlo stisknuti tlacitka.
	 */
	void cleanClickCount();

#endif

#if SWITCH_IMPLEMENT_CLICK_HELD_TIME

	/**
	 * Returns the hold time of the button.
	 *
	 * CS: Vrati dobu v milisekundach, po kterou je tlacitko udrzovane
	 * 	ve stisknutem stavu.
	 *
	 * @param ms Time in milliseconds, typically call millis()...
	 *
	 * @return uint32_t Time in milliseconds.
	 */
	uint32_t getHoldedTime(uint32_t _ms);

	/**
	 * Returns the hold time of the button with reset hold counter.
	 *
	 * CS: Vrati dobu v milisekundach, po kterou je tlacitko udrzovane
	 *  ve stisknutem stavu a vynuluje pocitadlo.
	 *
	 * @param ms Time in milliseconds, typically from millis()...
	 *
	 * @return uint32_t Time in milliseconds.
	 *
	 * @note Not implemented!
	 */
	uint32_t getHoldedTimeWithReset(uint32_t _ms);

#endif

	/**
	 * Is the switch has clicked?
	 *
	 * CS: Tlacitko bylo stisknuto a uvolneno?
	 *
	 * @return bool TRUE if has clicked, otherwise FALSE
	 */
	bool isClicked();

	/**
	 * Reset Click state.
	 *
	 * CS: Vznuluje stav stisknuteho a ynovu uvolneneho tlacitka.
	 */
	inline void CleanClick();

	/**
	 * Set Sets the button to "released".
	 *
	 * CS: Nastavi tlacitku stav "uvolneno".
	 *
	 * @see
	 *
	 * @param ms Time in milliseconds, typically from millis()...
	 *
	 * @note Pro volani uvnitr metody zpracovavajici stisk tlacitka nebo preruseni
	 */
	bool setClickEnd(uint32_t ms);

	/**
	 * Set Sets the button to "pushed".
	 *
	 * CS: Nastavi tlacitku stav "stisknuto".
	 *
	 * @param ms Time in milliseconds, typically from millis()...
	 *
	 * @return True if success otherwise FALSE
	 *
	 * @note Pro volani uvnitr metody zpracovavajici stisk tlacitka nebo preruseni
	 */
	bool setClickStart(uint32_t ms);

	/**
	 * Set the button to "push and release" status.
	 *
	 * CS: Nastavi tlacitku stav "stisknuto a uvolneno".
	 *
	 * @param ms Time in milliseconds, typically from millis()...
	 *
	 * @note This method its a pure concept!
	 * @note The method has never been tested. Use may cause undefined behavior!
	 */
	void setClick(uint32_t ms);

	/**
	 * Is the button pressed?
	 *  Attention! This state does not depend on the state of the button holded!
	 *
	 * CS: Je tlačítko stisknuto?
	 *  Pozor! Tento stav nezávisí na stavu podrženého tlačítka!
	 *
	 * @return bool TRUE if pressed, overwise FALSE.
	 */
	bool isPressed();


private:

	bool m_is_clicked = false; /*!< The switch button has bin clicked for now?. */
	uint32_t m_start_click = 0; /*!< Time in milliseconds where the click/hold action is started. */
	uint32_t m_end_click = 0; /*!< Time in milliseconds where the click/hold action is ended. */
	uint16_t m_time_debounce = SWITCH_TIME_DEBOUNCE; /*!< Delay in milliseconds to prevent a debounced noise. */

#if SWITCH_IMPLEMENT_CLICK_HELD
	uint32_t m_time_hold = 450; /*!< Delay in milliseconds before button hold state is registered. */
#endif

#if SWITCH_IMPLEMENT_CLICK_COUNT
	uint8_t m_click_count = 0; /*!< Incremental variable to maintain the number of button clicks. */
#endif

};
