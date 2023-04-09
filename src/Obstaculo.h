#pragma once
#include <utility>
class Obstaculo {
public:
    Obstaculo(float x, float y, float ancho, float alto);

    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;

    std::pair<float, float> getPosicionRotada(int angulo) const;

private:
    float x, y, ancho, alto;
};
