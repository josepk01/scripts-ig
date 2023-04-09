#include "Obstaculo.h"
#include <regex>
#include <ofMath.h>

Obstaculo::Obstaculo(float x, float y, float ancho, float alto) : x(x), y(y), ancho(ancho), alto(alto) {}

float Obstaculo::getX() const {
    return x;
}

float Obstaculo::getY() const {
    return y;
}

float Obstaculo::getAncho() const {
    return ancho;
}

float Obstaculo::getAlto() const {
    return alto;
}

std::pair<float, float> Obstaculo::getPosicionRotada(int angulo) const {
    float radianes = ofDegToRad(angulo);
    float coseno = cos(radianes);
    float seno = sin(radianes);
    float xRotado = x * coseno - y * seno;
    float yRotado = x * seno + y * coseno;

    return std::make_pair(xRotado, yRotado);
}