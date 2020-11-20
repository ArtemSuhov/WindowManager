#include "TXLib.h"
#pragma once

class Plane {
public:
	Plane(Vector size, Vector xStep, Vector yStep) {
		this->size.equalize(size);
		this->xStep.equalize(xStep);
		this->yStep.equalize(yStep);
		txCreateWindow(size.getX(), size.getY());
		txBegin();
	}

	void setSize(Vector size) {
		this->size.equalize(size);
	}

	void setXStep(Vector xStep) {
		this->xStep.equalize(xStep);
	}

	void setYStep(Vector yStep) {
		this->yStep.equalize(yStep);
	}

	Vector getSize() {
		return size;
	}

	Vector getXStep() {
		return xStep;
	}

	Vector getYStep() {
		return yStep;
	}

	void drawPixel(Vector vector, Vector color) {
		Point pixel;
		float x = vector.getX();
		float y = vector.getY();
		pixel.x = xStep.getX() * x + yStep.getX() * y;
		pixel.y = xStep.getY() * x + yStep.getY() * y;
		txSetPixel(pixel.x, pixel.y, RGB(color.getX(), color.getY(), color.getZ()));
	}

	void drawPixel(Point point, Vector color) {
		Point pixel;
		float x = point.x;
		float y = point.y;
		pixel.x = xStep.getX() * x + yStep.getX() * y;
		pixel.y = xStep.getY() * x + yStep.getY() * y;

		txSetPixel(pixel.x, pixel.y, RGB(color.getX(), color.getY(), color.getZ()));
	}


	void drawPixel(float x, float y, Vector color) {
		Point pixel;
		pixel.x = xStep.getX() * x + yStep.getX() * y;
		pixel.y = xStep.getY() * x + yStep.getY() * y;
		txSetPixel(pixel.x, pixel.y, RGB(color.getX(), color.getY(), color.getZ()));
	}

private:
	Vector size;
	Vector xStep;
	Vector yStep;
};