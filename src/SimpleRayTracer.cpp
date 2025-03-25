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
	:zvalue(zvalue),
	planedist(planedist),
	width(width),
	height(height),
	widthInPixel(widthInPixel),
	heightInPixel(heightInPixel)
{
	
}

Vector Camera::generateRay( unsigned int x, unsigned int y) const
{
    // 1. Umrechnung von Pixelkoordinaten in normalisierte Gerätekoordinaten (-1 bis 1)
    /*
		mit ndc koordinaten wandlen wir die pixelkoordinaten in eine einheitliche koordinate um, die von -1 bis 1 geht
        https://www.mebuyukbulut.com/cg/normalized-device-coordinate-ndc/2022/#:~:text=Normalized%20device%20coordinate%20or%20NDC,that%20defines%20the%20view%20volume.

		die berechnung der ndc Koordinaten haben wir folgender Seite entnommen:
        https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
    */
    float ndcX = (2.0f * x / (float)widthInPixel) - 1.0f;  // -1 (links) bis 1 (rechts)
    float ndcY = 1.0f - (2.0f * y / (float)heightInPixel); // 1 (oben) bis -1 (unten)

    // 2. Skalierung auf die physische Größe der Bildebene
    float worldX = ndcX * (width / 2.0f);
    float worldY = ndcY * (height / 2.0f);

    // 3. Berechnung des Punkts auf der Bildebene in Weltkoordinaten
    // Da die Kamera entlang der Z-Achse blickt, liegt die Bildebene bei z + planedist
    Vector pointOnPlane(worldX, worldY, zvalue + planedist);

    // 4. Berechnung des Richtungsvektors vom Augpunkt zum Punkt auf der Bildebene
    Vector direction = pointOnPlane - Position();

    // 5. Normalisierung des Richtungsvektors
    direction.normalize();

    return direction;
}

Vector Camera::Position() const
{
	// position von der kamera soll mittig sein, gegeben ist nur die z-koordinate (tiefe). X ist die breite und y die höhe
	return Vector(0, 0, zvalue); 
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

