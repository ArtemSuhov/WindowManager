#include "Vector.h"
#include "TXLib.h"
#pragma once

typedef void(*Action) ();

struct Button {
public:
	Button(const char* name, Point position, Vector size, Action func) :
		name(name),
		position(position),
		func(func)
	{
		this->size.equalize(size);
	}

	virtual void drawButton() {
		RECT rect{ position.x,				 position.y,
				   position.x + size.getX(), position.y + size.getY() };

		txSetFillColor (TX_WHITE);
		txRectangle	   (rect.left, rect.bottom, rect.right, rect.top);
		txSetColor	   (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name);
	}

	virtual bool isPressed(float x, float y) {
		float eqX = x - position.x;
		float eqY = y - position.y;

		return eqX > 0 && eqY > 0 && eqX < size.getX() && eqY < size.getX();
	}

	void press() {
		func();
	}

protected:
	const char* name;
	Point       position;
	Vector		size;
	Action		func;
};

struct CircleButton : public Button {
	CircleButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position.x,				 position.y,
				   position.x + size.getX(), position.y + size.getY() };

		txSetFillColor (TX_WHITE);
		txCircle	   (position.x + size.getX() / 2, position.y + size.getY() / 2, size.getX() / 2);
		txSetColor	   (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name);
	}

	virtual bool isPressed(float x, float y) override {
		Vector mouseToCenter(position.x + size.getX() / 2 - x, position.y + size.getY() / 2 - y);
		return mouseToCenter.length() <= size.getX() / 2;
	}
};

struct OvalButton : public Button {
	OvalButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position.x - 10,				 position.y,
				   position.x + size.getX() + 10, position.y + size.getY() };

		txSetFillColor (TX_WHITE);
		txEllipse      (rect.left, rect.bottom, rect.right, rect.top);
		txSetColor     (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name);
	}

	virtual bool isPressed(float x, float y) override {
		float firstLength  = (x - position.x) * (x - position.x) / ((size.getX() + 10) * (size.getX() + 10));
		float secondLength = (y - position.y) * (y - position.y) / (size.getY() * size.getY());
		return firstLength + secondLength <= 1;
	}
};


struct CloseButton : public Button {
	CloseButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position.x,				 position.y,
				   position.x + size.getX(), position.y + size.getY() };

		txSetColor (TX_WHITE);
		txLine     (rect.left, rect.bottom, rect.right, rect.top);
		txLine	   (rect.left, rect.top, rect.right, rect.bottom);
	}

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
	int		 count;
};