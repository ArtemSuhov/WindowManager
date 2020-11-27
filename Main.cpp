#include "pch.h"

#include "Vector.h"
#include "Plane.h"
#include "CoordSys.h"
#include "Buttons.h"

#include "TXLib.h"

#include <math.h>
#include <iostream>
#pragma once

RGBQUAD*  Video_memory = NULL;
CoordSys* GlobalCoord  = NULL;

void drawSin() {
	GlobalCoord->drawFunction(sin);
}

void drawCos() {
	GlobalCoord->drawFunction(cos);
}

void drawTan() {
	GlobalCoord->drawFunction(tan);
}

void clear() {
	txSetFillColor ( TX_BLACK );
	txClear		   (		  );
	txSetColor     ( TX_WHITE );

	GlobalCoord->drawAxes();
}

int main()
{
	Vector size       ( 700, 400 );
	Vector xStep	  ( 1,   0   );
	Vector yStep      ( 0,   1   );
	Point  zeroOfAxis { 50,  650 };
	Vector shift      ( 50,  50  );

	Video_memory = txVideoMemory();

	CoordSys coordSys ( size, xStep, yStep, zeroOfAxis, shift, Vector(0.002, 150) );
	GlobalCoord = &coordSys;

	txSetColor(TX_WHITE);
	GlobalCoord->drawAxes();

	const int count = 4;
	Button		 sinButton ("SIN",   Point{ 100, 100 }, Vector( 50, 50 ), drawSin);
	CircleButton cosButton ("COS",   Point{ 300, 100 }, Vector( 50, 50 ), drawCos);
	OvalButton   tanButton ("TAN",   Point{ 500, 100 }, Vector( 50, 50 ), drawTan);
	CloseButton  clrButton ("CLEAR", Point{ 700, 100 }, Vector( 50, 50 ), clear  );

	Button*       buttons[count] { &sinButton, &cosButton, &tanButton, &clrButton };
	ButtonManager manager	     ( buttons, count );

	while (true) {
		manager.draw();

		if (txMouseButtons() == 1) {
			manager.press();
		}

		txSleep();
	}
}

//TODO: Класс менеджера кнопок, добавить функцию добавления кнопки в массив указателей кнопок (добавлять в динамический массив или большой статический).