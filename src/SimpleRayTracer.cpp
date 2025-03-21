//
//  SimpleRayTracer.cpp
//  SimpleRayTracer
//
//  Created by Philipp Lensing on 03.09.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#include "SimpleRayTracer.h"
#include "rgbimage.h"
#include <stdio.h>
#include <math.h>


Camera::Camera(float zvalue, float planedist, float width, float height, unsigned int widthInPixel, unsigned int heightInPixel)
	:z(zvalue),
	planedist(planedist),
	width(width),
	height(height),
	widthInPixel(widthInPixel),
	heightInPixel(heightInPixel)
{
	
}

Vector Camera::generateRay( unsigned int x, unsigned int y) const
{
	// vier punkte , die die ecken des bildschirms darstellen
	// wir haben zwei punkte und machen darauas einen 2d vector mit den vier f�llen dann wahrscheinlich

	// wir ziehen den punkt des bildes von der camerea position z ab und wir verschieben diesen neuen vektor an die spitze f�r den richtungsvektor
	// wir m�ssen aber beachten das wir nicht nur z sonder auch planeDist ber�cksichtugen um richtig anzukommen

	Vector ray =  (Vector(x, y, z-planedist) - Position()).normalize();


	return ray;
}

Vector Camera::Position() const
{
	// position von der kamera soll mittig sein, gegeben ist nur die z-koordinate (tiefe). X ist die breite und y die h�he
	return Vector(0, 0, z); 
}

SimpleRayTracer::SimpleRayTracer(unsigned int MaxDepth)
{
	// TODO: Add your code
}


void SimpleRayTracer::traceScene( const Scene& SceneModel, RGBImage& Image)
{
	// TODO: Add your code
}

Color SimpleRayTracer::localIllumination( const Vector& Surface, const Vector& Eye, const Vector& N, const PointLight& Light, const Material& Mtrl )
{
	// TODO: Add your code
	return Color(); // dummy (remove)
}

Color SimpleRayTracer::trace( const Scene& SceneModel, const Vector& o, const Vector& d, int depth)
{
	// TODO: Add your code
	return Color(); // dummy (remove)
}

