/**
 * This file is a part of Switch library for embedded devices.
 *
 * File:		Switch.cpp
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/Switch
 * Version:		2.9.0
 */

#include "Switch.hpp"

Switch::Switch() {
}

Switch::~Switch() {
}

#if SWITCH_IMPLEMENT_CLICK_HELD

bool Switch::isHolded(uint32_t ms) {
	bool _is_clicked;
	uint32_t _start_click;

	SWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_start_click = m_start_click;
	SWITCH_ATOMIC_END

	return _is_clicked && ms - _start_click > m_time_hold;
}
#endif

void Switch::CleanClick() {
	SWITCH_ATOMIC_START
		m_end_click = 0;
	SWITCH_ATOMIC_END
}

bool Switch::isClicked() {
	bool _is_clicked;
	uint32_t _end_click;

	SWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_end_click = m_end_click;
	SWITCH_ATOMIC_END

	if (!_is_clicked && _end_click > 0) {
		CleanClick();
		return true;
	} else {
		return false;
	}
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
void Switch::setClick(uint32_t ms) {
	if (ms - m_end_click > m_time_debounce || m_end_click == 0) {
		m_end_click = ms;
		m_is_clicked = false;
	}
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
bool Switch::setClickEnd(uint32_t ms) {
	if ((ms - m_end_click > m_time_debounce || m_end_click == 0)) {
		m_end_click = ms;
		m_is_clicked = false;

#if SWITCH_IMPLEMENT_CLICK_HELD
		if (ms - m_start_click > m_time_hold) {
			m_end_click = 0;
		}
#endif

#if SWITCH_IMPLEMENT_CLICK_COUNT > 0
		if (m_end_click > 0 && m_click_count < SWITCH_IMPLEMENT_CLICK_COUNT) {
			m_click_count++;
		}
#endif

		return true;
	}
	return false;
}

/**
 * @note Metoda je volana v rutine preruseni. ATOMIC_BLOCK neumistovat!
 */
bool Switch::setClickStart(uint32_t ms) {
	if ((ms - m_end_click) > m_time_debounce || m_end_click == 0) {
		m_start_click = ms;
		m_is_clicked = true;
		return true;
	}
	return false;
}

#if SWITCH_IMPLEMENT_CLICK_COUNT

uint8_t Switch::getClickCount() {
	uint8_t _click_count;

	SWITCH_ATOMIC_START
		_click_count = m_click_count;
	SWITCH_ATOMIC_END

	return _click_count;
}

uint8_t Switch::getClickCountWithReset() {
	uint8_t _click_count;

	SWITCH_ATOMIC_START
		_click_count = m_click_count;
		m_click_count = 0;
	SWITCH_ATOMIC_END

	return _click_count;
}

void Switch::cleanClickCount() {
	SWITCH_ATOMIC_START
		m_click_count = 0;
	SWITCH_ATOMIC_END
}

#endif

#if SWITCH_IMPLEMENT_CLICK_HELD_TIME

uint32_t Switch::getHoldedTime(uint32_t _ms) {
	bool _is_clicked;
	uint32_t _start_click;

	SWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
		_start_click = m_start_click;
	SWITCH_ATOMIC_END

	if (_is_clicked) {
		return _ms - _start_click;
	} else {
		return 0;
	}
}

uint32_t Switch::getHoldedTimeWithReset(uint32_t _ms) {
	uint32_t t = 0;

	return t;
}

bool Switch::isPressed() {
	bool _is_clicked;

	SWITCH_ATOMIC_START
		_is_clicked = m_is_clicked;
	SWITCH_ATOMIC_END

	return _is_clicked;
}

#endif

