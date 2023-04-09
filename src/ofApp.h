#pragma once
#include "ofMain.h"
#include "Jugador.h"
#include "Mapa.h"
#include "Texturas.h"
#include "ofMain.h"
#include "ofImage.h"
#include "Obstaculo.h"
#include "Enemigo.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void actualizarColorFondo();
    glm::vec2 calcularCamaraPosicion();
    void update();
    void draw();
    void penalizarJugador(int jugador, int penalizacion);
    void verificarColisiones();
    ofApp();
    void keyPressed(int key);
    void keyReleased(int key);
    //---
    void agregarObstaculos();
    bool colisionaObstaculo(const Jugador& jugador, const Obstaculo& obstaculo) const;
    //---
    bool colisionaEnemigo(const Jugador& jugador, const Enemigo& enemigo) const;
    void agregarEnemigos();
    void checkSalidaPantalla();
    void resetJuego();

private:
    Jugador jugador1;
    Jugador jugador2;
    Mapa mapa;
    std::vector<Obstaculo> obstaculos;
    ofColor colorFondo;
    std::vector<Enemigo> enemigos;
    int angulo;
    int puntuacionJugador1;
    int puntuacionJugador2;
    int vidasJugador1;
    int vidasJugador2;
    float tiempoAnterior;
    float jugadorRadio;
    float camaraX;
    float camaraY;
};
