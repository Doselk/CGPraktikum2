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
	// wir haben zwei punkte und machen darauas einen 2d vector mit den vier fällen dann wahrscheinlich

	// wir ziehen den punkt des bildes von der camerea position z ab und wir verschieben diesen neuen vektor an die spitze für den richtungsvektor
	// wir müssen aber beachten das wir nicht nur z sonder auch planeDist berücksichtugen um richtig anzukommen

	Vector ray =  Vector(x, y, planedist).normalize();


	return ray;
}

Vector Camera::Position() const
{
	// position von der kamera soll mittig sein, gegeben ist nur die z-koordinate (tiefe). X ist die breite und y die höhe
	return Vector(0, 0, z); 
}

SimpleRayTracer::SimpleRayTracer(unsigned int MaxDepth):maxDepth(MaxDepth){}


void SimpleRayTracer::traceScene( const Scene& SceneModel, RGBImage& Image)
{
    Camera cam = Camera(8, 1, 1, 0.75, 640, 480);
    for (int w = 0; w<Image.width(); w++) {
        for (int h = 0; h<Image.height(); h++) {
            Color c = trace(SceneModel, cam.Position(), cam.generateRay(w, h), maxDepth);
            Image.setPixelColor(w, h, c);
        }
    }
}

Color SimpleRayTracer::localIllumination( const Vector& Surface, const Vector& Eye, const Vector& N, const PointLight& Light, const Material& Mtrl )
{
    return Mtrl.getDiffuseCoeff(Surface);
}

Color SimpleRayTracer::trace( const Scene& SceneModel, const Vector& o, const Vector& d, int depth)
{
    for (int i = 0 ; i<SceneModel.getTriangleCount(); i++) {
        Vector A = SceneModel.getTriangle(i).A;
        Vector B = SceneModel.getTriangle(i).B;
        Vector C = SceneModel.getTriangle(i).C;
        
        float s;
        
        if (o.triangleIntersection(d, A, B, C, s) && s > 0) {
            //if (depth > 0) {
            //    depth--;
            //    return trace(SceneModel, o, d, depth);
            //} else {
                return Color(0.3,0.3,0.3);
            //}
        }
    }
    
	return Color(0,0,0); // wenn wir nichts treffen
}

