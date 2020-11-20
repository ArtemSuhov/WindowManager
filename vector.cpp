#include "pch.h"
#include "Vector.h"
#include "Plane.h"
#include "CoordSys.h"
#include "TXLib.h"
#include <math.h>
#include <iostream>
#pragma once

RGBQUAD* Video_memory = NULL;

typedef void(*Action) ();

class Button {
public:
	Button(const char* name, Point position, Vector size, Action func) :
		name(name), 
		position(position),
		func(func)
	{
		this->size.equalize(size);
	}

	virtual void drawButton() {
		txSetFillColor(TX_WHITE);
		txRectangle(position.x, position.y, position.x + size.getX(), position.y + size.getY());
		txSetColor(TX_BLACK);
		txDrawText(position.x, position.y, position.x + size.getX(), position.y + size.getY(), name);
	}

	virtual bool isPressed(float x, float y) {
		float eqX = x - position.x;
		float eqY = y - position.y;

		return eqX > 0 && eqY > 0 && eqX < size.getX() && eqY < size.getX();
	}
	
	void press() {
		func();
	}

private:
	const char* name;
	Point position;
	Vector size;
	Action func;
};

class ButtonManager {
public:
	ButtonManager(Button** buttons, int count) {
		this->count = count;
		this->buttons = buttons;
	}

	void draw() {
		for (int i = 0; i < count; i++) {
			buttons[i]->drawButton();
		}
	}

	void press() {
		for (int i = 0; i < count; i++) {
			if (buttons[i]->isPressed(txMouseX(), txMouseY())) {
				buttons[i]->press();
			}
		 }
	}

private:
	Button** buttons;
	int count;
};

CoordSys* GlobalCoord = NULL;

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
	txSetFillColor(TX_BLACK);
	txClear();
	txSetColor(TX_WHITE);
	GlobalCoord->drawAxes();
}

int main()
{
	Vector size (700, 400);
	Vector xStep (1, 0);
	Vector yStep (0, 1);
	Point zeroOfAxis { 50, 650 };
	Vector shift (50, 50);

	Video_memory = txVideoMemory();

	CoordSys coordSys (size, xStep, yStep, zeroOfAxis, shift, Vector(0.002, 150));
	GlobalCoord = &coordSys;

	txSetColor(TX_WHITE);
	GlobalCoord->drawAxes();

	const int count = 4;
	Button sinButton ("SIN",   Point{ 100, 100 }, Vector(50, 50), drawSin);
	Button cosButton ("COS",   Point{ 300, 100 }, Vector(50, 50), drawCos);
	Button tanButton ("TAN",   Point{ 500, 100 }, Vector(50, 50), drawTan);
	Button clrButton ("CLEAR", Point{ 700, 100 }, Vector(50, 50), clear  );

	Button* buttons[count] = { &sinButton, &cosButton, &tanButton, &clrButton };
	ButtonManager manager (buttons, count);

	while (true) {
		manager.draw();

		if (txMouseButtons() == 1) {
			manager.press();
		}

		txSleep();
	}
}


//членам класса земля в конце ставить. ПРОБЕЛЫ! КОПИИ НА ССЫЛКИ! * [] ИЛИ ** МАССИВ УКАЗАТЕЛЕЙ (кнопки на наследовании (разной формы)). button manager
//конструктор можно без равно писать. VIRTUAL - ВИРТУАЛЬНЫЙ МЕТОД КОТОРЫЙ МЕНЯТЬ БУДЕМ OVERRIDE - ПРОВЕРКА НА ТО ЧТО РЕАЛЬНО ПЕРЕЗАПИСЫВАЕМ
