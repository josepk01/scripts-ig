#include "Enemigo.h"

Enemigo::Enemigo(float x, float y, float ancho, float alto)
    : x(x), y(y), ancho(ancho), alto(alto) {
    velocidadX = 0.0f; // Ajusta la velocidad en el eje X
}

void Enemigo::update() {
    x += velocidadX;
}

void Enemigo::draw() {
    ofFill();
    ofSetColor(0, 0, 0); // Color rojo
    ofDrawTriangle(x, y + alto, x + ancho/2, y, x + ancho, y + alto);
}

float Enemigo::getX() const {
    return x;
}

float Enemigo::getY() const {
    return y;
}

float Enemigo::getAncho() const {
    return ancho;
}

float Enemigo::getAlto() const {
    return alto;
}
