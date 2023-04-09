#include "Mapa.h"
#include "ofApp.h"

void Mapa::inicializarMapa(ofApp* app) {
    float sueloAltura = ofGetHeight() / 3.0f;
    mapaAncho = 1600.0f; // Establecer un valor de ancho personalizado para el mapa

    float mapaVertices[] = {
        0.0f, ofGetHeight() - sueloAltura,  0.0f, 0.0f,
        mapaAncho, ofGetHeight() - sueloAltura,  1.0f, 0.0f,
        mapaAncho, ofGetHeight(),  1.0f, 1.0f,
        0.0f, ofGetHeight(),  0.0f, 1.0f
    };

    // Agregar rectángulo para el techo
    float techoAltura = ofGetHeight() / 6.0f;
    float techoVertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        mapaAncho, 0.0f, 1.0f, 0.0f,
        mapaAncho, techoAltura, 1.0f, 1.0f,
        0.0f, techoAltura, 0.0f, 1.0f
    };

}

void Mapa::dibujarMapa() {
    // Dibujar el suelo y el techo
    ofSetColor(139, 69, 19); // Establecer el color a marrón claro
    ofFill(); // Activar el relleno
    ofDrawRectangle(0, ofGetHeight() * 2 / 3, mapaAncho, ofGetHeight() / 3);
    ofDrawRectangle(0, 0, mapaAncho, ofGetHeight() / 6); // Dibujar el techo
}
