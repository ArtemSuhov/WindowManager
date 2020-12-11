#include "TXLib.h"
#pragma once

struct Window {
	
	Window() {
		Point  left_ { 0, 0 };
		Vector size_ ( 0, 0 );
	}

	Window(Point left, Vector size) {
		left_ = left;
		size_.equalize(size);
	}

	virtual void drawWindow() {
		txCreateWindow(size_.getX(), size_.getY());
		txBegin();
	}

	virtual void mousePress() {

	}
	
	virtual void buttonPress() {

	}

protected:
	Point  left_;
	Vector size_;

};