#include "Mapa.h"
#include "ofApp.h"

void Mapa::inicializarMapa(ofApp* app) {

    suelo = app->getSuelo();
    techo = app->getTecho();
    mapaAncho = 3200.0f; // Establecer un valor de ancho personalizado para el mapa
}

void Mapa::dibujarMapa() {
    // Dibujar el suelo y el techo
    ofSetColor(139, 69, 19); // Establecer el color a marrón claro
    ofFill(); // Activar el relleno
    ofDrawRectangle(0, ofGetHeight() * 2 / 3, mapaAncho, suelo);// Dibujar el suelo
    ofDrawRectangle(0, 0, mapaAncho, techo); // Dibujar el techo
    
}
