/**
 * This file is a part of examples of a Switch library.
 *
 * Created on:  	16.02.2020
 * Author:    		Denis Colesnicov <eugustus@gmail.com>
 * Licence:   		MIT
 * Home:    		https://github.com/colesnicov/Switch
 * Description:		Priklad pouziti alternativnich tlacitek s prerusenim.
 * 					 Je zde ukazana moznost stisku nekolika tlacitek soucasne.
 * Note:    		Pozor! Jedna se o "pure concept"! Funkcnost neni doladena!
 */

#include <Arduino.h>

#include "Switch/SwitchArduino.hpp"
#include "Switch/SwitchConfig.h"
#include "Switch/Switch.hpp"

// Definice pinu
#define BTN_one 2
#define BTN_two 3

// Objekty predstavujici tlacitka
Switch btn_two;
Switch btn_one;

// Spravce obsluhy stavu tlacitek
SwitchArduino handler;

// Spravce obsluhy stavu alternativnich tlacitek
SwitchArduino handlerAlt;

void buttonProccess() {
	handler.Update(millis());
}

void buttonProccessAlt() {
	handlerAlt.Update(millis());
}

void setup() {
	Serial.begin(115200);

	Serial.print("Switch Version ");
	Serial.println(Switch_Version);

	// Nastavuji piny jako vystup.
	pinMode(BTN_one, INPUT);
	pinMode(BTN_two, INPUT);

	// Zapinam interni PULL_UP rezistory.
	/* Odkomentovat, pokud nejsou pripojeny externi PULLUP odpory */
	//digitalWrite(BTN_one, HIGH);
	//digitalWrite(BTN_two, HIGH);
	handler.AddButton(&btn_one, BTN_one);
	handlerAlt.AddButton(&btn_two, BTN_two);

	// Navesuji preruseni.
	attachInterrupt(digitalPinToInterrupt(BTN_one), buttonProccess, CHANGE);
	attachInterrupt(digitalPinToInterrupt(BTN_two), buttonProccessAlt, CHANGE);

	Serial.println("Ready!\n\n");

}

void loop() {

	// Vypis stavu tlacitek.

	if (handlerAlt.GetButton(BTN_two)->isPressed()) {
		if (btn_one.isClicked()) {
			Serial.println("Alternative button + Button 1 clicked!");
		}
	} else {
		if (btn_one.isClicked()) {
			Serial.println("Button 1 clicked!");
		}
	}
}

