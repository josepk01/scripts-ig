#pragma once
#include "ofMain.h"

class Enemigo {
public:
    Enemigo(float x, float y, float ancho, float alto);
    void update();
    void draw();
    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;

private:
    float x, y, ancho, alto;
    float velocidadX;
};
