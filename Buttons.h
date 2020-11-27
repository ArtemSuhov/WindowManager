#include "Vector.h"
#include "TXLib.h"
#pragma once

typedef void(*Action) ();

struct Button {
public:
	Button(const char* name, Point position, Vector size, Action func) :
		name_(name),
		position_(position),
		func_(func)
	{
		this->size_.equalize(size);
	}

	virtual void drawButton() {
		RECT rect{ position_.x,				   position_.y,
				   position_.x + size_.getX(), position_.y + size_.getY() };

		txSetFillColor (TX_WHITE);
		txRectangle	   (rect.left, rect.bottom, rect.right, rect.top);
		txSetColor	   (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name_);
	}

	virtual bool isPressed(float x, float y) {
		float eqX = x - position_.x;
		float eqY = y - position_.y;

		return eqX > 0 && eqY > 0 && eqX < size_.getX() && eqY < size_.getX();
	}

	virtual void press() {
		func_();
	}

protected:
	const char* name_;
	Point       position_;
	Vector		size_;
	Action		func_;
};

struct CircleButton : public Button {
	CircleButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position_.x,				   position_.y,
				   position_.x + size_.getX(), position_.y + size_.getY() };

		txSetFillColor (TX_WHITE);
		txCircle	   (position_.x + size_.getX() / 2, position_.y + size_.getY() / 2, size_.getX() / 2);
		txSetColor	   (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name_);
	}

	virtual bool isPressed(float x, float y) override {
		Vector mouseToCenter(position_.x + size_.getX() / 2 - x, position_.y + size_.getY() / 2 - y);
		return mouseToCenter.length() <= size_.getX() / 2;
	}
};

struct OvalButton : public Button {
	OvalButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position_.x - 10,				 position_.y,
				   position_.x + size_.getX() + 10,  position_.y + size_.getY() };

		txSetFillColor (TX_WHITE);
		txEllipse      (rect.left, rect.bottom, rect.right, rect.top);
		txSetColor     (TX_BLACK);
		txDrawText	   (rect.left, rect.bottom, rect.right, rect.top, name_);
	}

	virtual bool isPressed(float x, float y) override {
		float firstLength  = (x - position_.x) * (x - position_.x) / ((size_.getX() + 10) * (size_.getX() + 10));
		float secondLength = (y - position_.y) * (y - position_.y) / (size_.getY() * size_.getY());
		return firstLength + secondLength <= 1;
	}
};


struct CloseButton : public Button {
	CloseButton(const char* name, Point position, Vector size, Action func) :
		Button(name, position, size, func)
	{
	}

	virtual void drawButton() override {
		RECT rect{ position_.x,				   position_.y,
				   position_.x + size_.getX(), position_.y + size_.getY() };

		txSetColor (TX_WHITE);
		txLine     (rect.left, rect.bottom, rect.right, rect.top);
		txLine	   (rect.left, rect.top, rect.right, rect.bottom);
	}

};

class ButtonManager {
public:
	ButtonManager(Button** buttons, int count) :
	count_(count)
	{
		if (count < maxSize_) {
			for (int i = 0; i < count; i++) {
				buttons_[i] = buttons[i];
			}	
		}
		else {
			std::cerr << "Manager is full";
		}
	}

	void addButton(Button* button) {
		if (count_ < maxSize_) {
			buttons_[count_] = button;
			count_++;
		}
		else {
			std::cerr << "Manager is full";
		}
	}

	void draw() {
		for (int i = 0; i < count_; i++) {
			buttons_[i]->drawButton();
		}
	}

	void press() {
		for (int i = 0; i < count_; i++) {
			if (buttons_[i]->isPressed(txMouseX(), txMouseY())) {
				buttons_[i]->press();
			}
		}
	}

protected:
	static const int maxSize_ = 50;
	Button*			 buttons_[maxSize_];
	int				 count_;
};