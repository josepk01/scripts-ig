#include "Jugador.h"
#include <ofEvents.h>
#include <ofAppRunner.h>
#include <ofMath.h>
#include "ofApp.h"

Jugador::Jugador() : Jugador(0, 0, 10, 10, 0, 0, 0) {}

Jugador::Jugador(float x, float y, float ancho, float alto, int teclaIzquierda, int teclaDerecha, int teclaArriba)
    : posicion(x, y), velocidad(0.0f, 0.0f), ancho(ancho), alto(alto), gravedad(0.5),
    teclaIzquierda(teclaIzquierda), teclaDerecha(teclaDerecha), teclaArriba(teclaArriba),
    teclaIzquierdaPresionada(false), teclaDerechaPresionada(false), angulo(0) {}  // Add angulo(0)


void Jugador::update() {
    if (teclaIzquierdaPresionada && !teclaDerechaPresionada) {
        velocidad.x = -5.0f;
    }
    else if (teclaDerechaPresionada && !teclaIzquierdaPresionada) {
        velocidad.x = 5.0f;
    }
    else {
        velocidad.x = 0.0f;
    }

    // Actualizar la posición en función de la velocidad
    posicion += velocidad;

    // Aplicar gravedad
    float angle_radians = -ofDegToRad(angulo);
    float gravity_x = gravedad * sin(angle_radians);
    float gravity_y = gravedad * cos(angle_radians);

    velocidad.x += gravity_x;
    velocidad.y += gravity_y;

    // Comprobar la colisión con el suelo
    if (posicion.y + alto > ofGetHeight() * 2 / 3) {
        posicion.y = ofGetHeight() * 2 / 3 - alto;
        velocidad.y = 0.0f;
    }
}


void Jugador::keyPressed(int key) {
    if (key == teclaIzquierda) {
        teclaIzquierdaPresionada = true;
    }
    else if (key == teclaDerecha) {
        teclaDerechaPresionada = true;
    }
    else if (key == teclaArriba) {
        velocidad.y = -8.0;  // Salto
    }
}

void Jugador::keyReleased(int key) {
    if (key == teclaIzquierda) {
        teclaIzquierdaPresionada = false;
    }
    else if (key == teclaDerecha) {
        teclaDerechaPresionada = false;
    }
}



glm::vec2 Jugador::getPosicion() const {
    return posicion;
}

float Jugador::getX() const {
    return posicion.x;
}

float Jugador::getY() const {
    return posicion.y;
}

float Jugador::getAncho() const {
    return ancho;
}

float Jugador::getAlto() const {
    return alto;
}

void Jugador::setX(float x) {
    posicion.x = x;
}

void Jugador::setY(float y) {
    posicion.y = y;
}

float Jugador::getVelocidadX() const {
    return velocidad.x;
}

float Jugador::getVelocidadY() const {
    return velocidad.y;
}

void Jugador::setVelocidadY(float y) {
    velocidad.y = y;
}
void Jugador::setVelocidadX(float x) {
    velocidad.x = x;
}