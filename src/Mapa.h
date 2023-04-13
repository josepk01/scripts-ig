#pragma once
#include "ofMain.h"

class ofApp;

class Mapa {
public:
    void inicializarMapa(ofApp* app);
    void dibujarMapa();

private:
    float mapaAncho = 3000.f;
    float suelo, techo;
};
