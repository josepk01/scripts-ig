#pragma once
#include "ofMain.h"

class ofApp;

class Mapa {
public:
    void inicializarMapa(ofApp* app);
    void dibujarMapa();

    float getMapa();

private:
    float mapaAncho;
    float suelo, techo;
};
