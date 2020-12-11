#include "pch.h"
#include "Vector.h"
#include "Plane.h"
#include "CoordSys.h"
#include "Buttons.h"
#include "Ploter.h"
#include "TXLib.h"
#include <math.h>
#include <iostream>
#pragma once

RGBQUAD*  Video_memory = NULL;


int main()
{
	Video_memory = txVideoMemory();

	Point  left  { 0  , 0   };
	Vector size  ( 700, 400 );
	Vector xStep ( 1  , 0   );
	Vector yStep ( 0  , 1   );

	HPEN pen = Win32::CreatePen(PS_DOT, 1, TX_RED);

	txSelectObject(pen);

	Plane plane (left, size, xStep, yStep);

	HDC pencil = txLoadImage("Pencil.bmp");

	txSetFillColor (    TX_WHITE    );
	txRectangle    ( 0, 0, 700, 400 );
	
	Vector color(0, 0, 0);

	while (!GetAsyncKeyState(VK_ESCAPE)) {
		Point mouse { txMouseX(), txMouseY() };
		txBitBlt(txDC(), mouse.x - 4, mouse.y - 32, 32, 32, pencil);

		if (txMouseButtons() == 1) {
			plane.drawRect ( mouse, color );
		}
		else if (txMouseButtons() == 2) {
			plane.drawRect ( mouse, Vector(255, 255, 255) );
		}

		txSleep();
	}

	txDeleteDC(pencil);
}

// Рисовать линию между текущей и прошлой точкой! Сплайн (пример скинули).
// Два холста, ткслиб разобраться. И гашение мышки (txSetWindowsHook). Все есть в документации.
// Рисование в виртуальном холсте (невидимый холст!)