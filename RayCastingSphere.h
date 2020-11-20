#include "Vector.h"
#include "Plane.h"
#include <math.h>
#include "TXLib.h"
#pragma once

struct Light {
	Vector color;
	Vector position;
};

Vector channelMul(Vector a, Vector b) {
	return Vector(a.getX() * b.getX(), a.getY() * b.getY(), a.getZ() * b.getZ());
}

Vector colorise(Vector color) {
	float r = color.getX();
	float g = color.getY();
	float b = color.getZ();
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;

	return Vector(r, g, b);
}

const Vector FillingLight = Vector(51, 51, 51);
const float MaterialShape = 40;

Vector getLightedPointColor(Light* lights, int lightsCount, Vector camera, Vector point, Vector center, Vector sphereColor) {
	Vector resultColor = channelMul(sphereColor * (1. / 255), FillingLight * (1. / 255)) * 255;
	Vector normalVector = (point - center).normalize();

	for (int i = 0; i < lightsCount; i++) {
		Vector pointToLight = (lights[i].position - point).normalize();
		Vector pointToCamera = (camera - point).normalize();
		Vector reflectedLight = (normalVector * 2 - pointToLight).normalize();

		float reflCos = pointToCamera ^ reflectedLight;
		float angleCos = pointToLight ^ normalVector;

		float reflIntensity = reflCos > 0 ? pow(reflCos, MaterialShape) : 0;
		float intensity = angleCos > 0 ? angleCos : 0;

		Vector currentColor = channelMul(sphereColor * (1. / 255), lights[i].color * (1. / 255)) * 255;

		resultColor.equalize(colorise(resultColor + currentColor * intensity + lights[i].color * reflIntensity));
	}

	return resultColor;
}

void drawLightedSphere(Plane plane, Point center, float radius, Vector camera, Light* lights, int lightsCount, Vector sphereColor) {
	Vector size = plane.getSize();
	float xSize = size.getX();
	float ySize = size.getY();

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			Point point{ x, y };
			Point spherePoint = point - center;

			if (Vector(spherePoint).length() < radius) {
				float z = sqrt(radius * radius - spherePoint.x * spherePoint.x - spherePoint.y * spherePoint.y);
				Vector color = getLightedPointColor(lights, lightsCount, camera, Vector(point.x, point.y, z), Vector(center), sphereColor);
				plane.drawPixel(point, color);
			}
		}
	}
}

//ÐÈÑÎÂÀÍÈÅ ÑÔÅÐÛ Ñ ÒÅÍßÌÈ (ðýéêàñòèíã)
//Vector camera = Vector(0, 0, 750);
//Vector sphereColor = Vector(0, 255, 0);

//int lightsCount = 2;
//Light light1;
//light1.color.equalize(Vector(64, 128, 255));
//light1.position.equalize(Vector(300, -150, 0));
//Light light2;
//light2.color.equalize(Vector(255, 255, 64));
//light2.position.equalize(Vector(-300, 300, 300));

//float time = 0;
//float timeStep = 0.1;

//while (true) {
//	Light * lights = new Light[2]{ light1, light2 };
//	drawLightedSphere(plane, { size.getX() / 2, size.getY() / 2 }, 150, camera, lights, lightsCount, sphereColor);

//	time += timeStep;
//
//	light2.position.setX(-300 * (1 + cos(time)));
//	light2.position.setY(-300 *      cos(time));
//	light2.position.setZ( 300 *		 sin(time));

//	txSleep();
//}