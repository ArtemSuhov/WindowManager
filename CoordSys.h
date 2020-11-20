#include "Vector.h"
#include "Plane.h"
#include "TXLib.h"
#pragma once

typedef double(*MathPlot) (double x);

class CoordSys : Plane {
public:
	CoordSys(Vector size, Vector xStep, Vector yStep, Point zeroPoint, Vector shift, Vector scaleStep)
		: Plane(Vector(size.getX() + zeroPoint.x + shift.getX(), zeroPoint.y + shift.getY()), xStep, yStep) {
		this->zeroPoint = zeroPoint;
		this->size.equalize(size);
		this->shift.equalize(shift);
		this->scaleStep.equalize(scaleStep);
	}

	void drawAxes() {
		Vector xAxis(size.getX(), 0, 0);
		Vector yAxis(0, -size.getY(), 0);
		xAxis.DrawVector(zeroPoint);
		yAxis.DrawVector(zeroPoint);
	}

	void drawFunction(MathPlot func) {
		float x = 0;
		while (x < size.getX()) {
			float y = func(x * scaleStep.getX()) * scaleStep.getY();

			if (y < size.getY()) {
				drawPixel(Point{ x + zeroPoint.x, zeroPoint.y - y , 0 }, Vector(255, 255, 255));
			}

			x++;
		}
	}

private:
	Point  zeroPoint;
	Vector size;
	Vector shift;
	Vector scaleStep;
};