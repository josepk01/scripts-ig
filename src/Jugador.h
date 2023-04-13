#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Jugador {
public:
    Jugador();
    Jugador(float x, float y, float ancho, float alto, int teclaIzquierda, int teclaDerecha, int teclaArriba);
    bool teclaIzquierdaPresionada;
    bool teclaDerechaPresionada;

    glm::vec2 getPosicion() const;

    float getX() const;
    float getY() const;

    float getAncho() const;

    float getAlto() const;

    void setX(float x);
    void setY(float y);

    void keyPressed(int key);
    void keyReleased(int key);
    void update_aungulo(float ofAppAngulo);
    void updatePosicionConGravedad(float dt, float angulo, float gravedad, float camaraX, float camaraY);
    float getVelocidadX() const;
    float getVelocidadY() const;
    void setVelocidadY(float y);
    void setVelocidadX(float x);
    void update();
    void updateCamara(float camaraX, float camaraY);

private:
    glm::vec2 posicion;
    glm::vec2 velocidad;
    float ancho, alto;
    float gravedad;
    int teclaIzquierda;
    int teclaDerecha;
    float angulo;  
    int teclaArriba;
    float x;
    float y;
    float velocidadX;
    float velocidadY;
    float camaraX;
    float camaraY;
    float fuerza_salto;
};
