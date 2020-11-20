#include "TXLib.h"
#pragma once

struct Point {
	float x;
	float y;
	float z;

	Point operator+ (Point a) {
		return { a.x + x, a.y + y, a.z + z };
	}

	Point operator- (Point a) {
		return { a.x - x, a.y - y, a.z - z };
	}
};


class Vector {
public:
	Vector() {
		this->setX(0);
		this->setY(0);
		this->setZ(0);
	}

	Vector(Point a) {
		this->setX(a.x);
		this->setY(a.y);
		this->setZ(a.z);
	}

	Vector(float x, float y) {
		this->setX(x);
		this->setY(y);
		this->setZ(0);
	}

	Vector(float x, float y, float z) {
		this->setX(x);
		this->setY(y);
		this->setZ(z);
	}

	void equalize(Vector a) {
		coords.x = a.getX();
		coords.y = a.getY();
		coords.z = a.getZ();
	}

	void setX(float x) {
		coords.x = x;
	}

	void setY(float y) {
		coords.y = y;
	}

	void setZ(float z) {
		coords.z = z;
	}

	float getX() {
		return coords.x;
	}

	float getY() {
		return coords.y;
	}

	float getZ() {
		return coords.z;
	}

	float length() {
		return sqrt(coords.x * coords.x + coords.y * coords.y + coords.z * coords.z);
	}

	Vector operator+ (Vector a) {
		return Vector(coords.x + a.getX(), coords.y + a.getY(), coords.z + a.getZ());
	}

	Vector operator* (float a) const {
		return Vector(coords.x * a, coords.y * a, coords.z * a);
	}

	Vector operator- (Vector a) {
		return *this + (a * (-1));
	}

	Vector normalize()
	{
		float inv_length = this->length();

		if (inv_length != 0) {
			inv_length = 1.0f / inv_length;
		}

		return *this * (inv_length);
	}

	void DrawVector(Point a) {
		DrawVectorWithoutArrow(a);
		Point end = this->coords + a;
		DrawArrow(end);
	}

	Vector planeOrd() {
		return Vector(this->coords.y, -this->coords.x);
	}

private:
	Point coords;
	const int arrowSize = 10;

	void DrawVectorWithoutArrow(Point a) {
		txLine(a.x, a.y, a.x + coords.x, a.y + coords.y);
	}

	void DrawArrow(Point a) {
		Vector firstArrow = this->planeOrd();
		Vector secondArrow = this->planeOrd() * -1;

		((firstArrow.normalize() + this->normalize()) * -arrowSize).DrawVectorWithoutArrow(a);
		((secondArrow.normalize() + this->normalize()) * -arrowSize).DrawVectorWithoutArrow(a);
	}
};

float operator^(Vector a, Vector b) {
	return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
};