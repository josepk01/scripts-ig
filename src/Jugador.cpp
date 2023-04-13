#include "Jugador.h"
#include <ofEvents.h>
#include <ofAppRunner.h>
#include <ofMath.h>
#include "ofApp.h"

Jugador::Jugador() : Jugador(0, 0, 10, 10, 0, 0, 0) {}

Jugador::Jugador(float x, float y, float ancho, float alto, int teclaIzquierda, int teclaDerecha, int teclaArriba)
    : posicion(x, y), velocidad(0.0f, 0.0f), ancho(ancho), alto(alto), gravedad(1),
    teclaIzquierda(teclaIzquierda), teclaDerecha(teclaDerecha), teclaArriba(teclaArriba),
    teclaIzquierdaPresionada(false), teclaDerechaPresionada(false), angulo(0),fuerza_salto(16.0f) {}  // Add angulo(0)

void Jugador::update() {

    float dt = ofGetLastFrameTime();

    if (teclaIzquierdaPresionada && !teclaDerechaPresionada) {
        velocidad.x = -5.0f;
    }
    else if (teclaDerechaPresionada && !teclaIzquierdaPresionada) {
        velocidad.x = 5.0f;
    }
    else {
        velocidad.x *= 0.95f; // Añade un factor de fricción para frenar suavemente al jugador en el eje X
    }

    updatePosicionConGravedad(dt, angulo, gravedad, camaraX, camaraY);

    // Comprobar la colisión con el suelo
    if (posicion.y + alto > ofGetHeight() * 2 / 3) {
        posicion.y = ofGetHeight() * 2 / 3 - alto;
        velocidad.y = 0.0f;
    }
}

void Jugador::updateCamara(float camaraX, float camaraY) {
    this->camaraX = camaraX;
    this->camaraY = camaraY;
}
void Jugador::keyPressed(int key) {
    if (key == teclaIzquierda) {
        teclaIzquierdaPresionada = true;
    }
    else if (key == teclaDerecha) {
        teclaDerechaPresionada = true;
    }
    else if (key == teclaArriba) {
        // Salto
        glm::vec2 salto;
        if (angulo == 0 ) {
            salto = glm::vec2(0.0f, -fuerza_salto);
        }
        else if (angulo == 90)
        {
            salto = glm::vec2(-fuerza_salto,0.0f);
        }
        else if (angulo == 180) {
            salto = glm::vec2(0.0f, fuerza_salto);
        }
        else
        {
            salto = glm::vec2(fuerza_salto, 0.0f);
        }

        velocidad += salto;
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
void Jugador::update_aungulo(float ofAppAngulo)
{
    angulo = ofAppAngulo;
}

void Jugador::updatePosicionConGravedad(float dt, float angulo, float gravedad, float camaraX, float camaraY) {
    float anguloRadianes = ofDegToRad(angulo);
    float gravedadX = gravedad * sin(anguloRadianes);
    float gravedadY = gravedad * cos(anguloRadianes);

    velocidad.x += gravedadX;
    velocidad.y += gravedadY;

    posicion += velocidad;
    //posicion.y += velocidad.y;
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