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
    Vector pointOnPlane(worldX, worldY, -zvalue + planedist);

    // 4. Berechnung des Richtungsvektors vom Augpunkt zum Punkt auf der Bildebene
    Vector direction = pointOnPlane - Position();

    // 5. Normalisierung des Richtungsvektors
    direction.normalize();

    return direction;
}

Vector Camera::Position() const
{
	// position von der kamera soll mittig sein, gegeben ist nur die z-koordinate (tiefe). X ist die breite und y die höhe
	return Vector(0, 0, -zvalue); 
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
    // 1. Suche das nächste Dreieck, das der Strahl trifft

    // Korrekte Suche nach dem nächstgelegenen Dreieck
    // 
    // 
    // durch all durchiterieren
    // triangle 1 speichern
    // ist triangle n näher als triangle n-1?
    // 
    // Vermeidung von Selbst - Kollisionen(indem man minimale Entfernung festlegt)

	int trinagleCount = SceneModel.getTriangleCount();

	Vector nearestTriangleIntersection = Vector(0, 0, 0);
	int nearestTriangleIndex = -1;
	float nearestTriangleDistance = INFINITY;

    const Triangle* nearestTriangle = nullptr;

    for (size_t i = 0; i < trinagleCount; i++)
    {
		const Triangle &currentTriangle = SceneModel.getTriangle(i);
        float s = -1;

        if (o.triangleIntersection(d, currentTriangle.A, currentTriangle.B, currentTriangle.C, s)) {
			

            if (s < nearestTriangleDistance) {
				nearestTriangleDistance = s;
				nearestTriangleIntersection = o + (d * s);

				nearestTriangleIndex = i;
                nearestTriangle = &(SceneModel.getTriangle(i));
            }

        }

    }

    if (nearestTriangle == nullptr)
    {
		return Color(0, 0, 0);
    }

	return nearestTriangle->pMtrl->getDiffuseCoeff(nearestTriangleIntersection);


    
    // 2. Wenn kein Dreieck getroffen wird, gib eine Hintergrundfarbe zurück

	
    
    // 3. Berechne die lokale Beleuchtung am Treffpunkt(mit localIllumination)
    
    // 4. Falls Reflexion nötig ist und die Rekursionstiefe > 0:
    
        // Berechne den reflektierten Strahl
        
        // Rufe trace() für diesen Strahl rekursiv auf
        
        // Kombiniere die reflektierte Farbe mit der lokalen Beleuchtung
        
    // 5. Gib die resultierende Farbe zurück

    
	
}

