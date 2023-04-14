#include "ofApp.h"
#include <glm/glm.hpp>
#include <thread>

void ofApp::setup() {
    angulo = 0;
    colorFondo.set(0, 0, 0); // Inicializa el color de fondo a negro

    techoAltura = ofGetHeight() / 7.0f;
    sueloY = (ofGetHeight() * 2 / 3) - 50;
    // Inicializar el mapa
    mapa.inicializarMapa(this);

    puntuacionJugador1 = 0;
    puntuacionJugador2 = 0;
    tiempoAnterior = ofGetElapsedTimef();

    agregarObstaculos(); // Agregar obstáculos al mapa
    agregarEnemigos();// Agregar enemigos al mapa
    // Inicializar vidas
    vidasJugador1 = 3;
    vidasJugador2 = 3;
    jugadorRadio = 25.0f;
    // Inicializar Jugador, Texturas, Shaders, etc.
    jugador1 = Jugador(0.0f, ofGetHeight() * 2 / 3, 50.0f, 50.0f, 'a', 'd', 'w');
    jugador2 = Jugador(0.0f, ofGetHeight() * 2 / 3, 50.0f, 50.0f, OF_KEY_LEFT, OF_KEY_RIGHT, OF_KEY_UP);
    salioGanador = false;
}
void ofApp::actualizarColorFondo() {
    // Modificar este valor para controlar la velocidad a la que cambia el color
    float velocidadColor = 0.01;

    // Calcular el nuevo color del fondo
    float hue = ofMap(sin(ofGetElapsedTimef() * velocidadColor), -1, 1, 0, 255);
    colorFondo = ofColor::fromHsb(hue, 255, 255);
}
glm::vec2 ofApp::calcularCamaraPosicion() {
    float mediaX = (jugador1.getX() + jugador2.getX()) / 2;
    float mediaY = (jugador1.getY() + jugador2.getY()) / 2;

    // Limitar la posición Y de la cámara para evitar mostrar demasiado espacio vacío arriba del suelo
    float limiteY = ofGetHeight() * 2 / 3 - 100; // Ajustar el valor 100 según sea necesario
    if (mediaY > limiteY) {
        mediaY = limiteY;
    }
    float lerpFactor = 0.1f; // Ajusta este valor para controlar la suavidad del seguimiento de la cámara
    camaraX = camaraX + lerpFactor * (mediaX - camaraX);
    camaraY = camaraY + lerpFactor * (mediaY - camaraY);

    return glm::vec2(camaraX, camaraY);
}
void ofApp::update() {
    jugador1.updateCamara(camaraX, camaraY);
    jugador2.updateCamara(camaraX, camaraY);
    jugador1.update();
    jugador2.update();

    if (inicio == false)
    {
        vidasJugador1 = vidasJugador2 = 3;
        jugador1.setX(200);
        jugador2.setX(200);
        jugador1.setY(ofGetHeight() * 2 / 3);
        jugador2.setY(ofGetHeight() * 2 / 3);
    }
    // Calcular la posición media de los jugadores
    glm::vec2 camaraPosicion = calcularCamaraPosicion();
    camaraX = camaraPosicion.x;
    camaraY = camaraPosicion.y;

    // Verificar colisiones y mantener a los jugadores en la pantalla
    verificarColisiones();

    checkSalidaPantalla();

    // Actualizar el color de fondo
    actualizarColorFondo();
    // Verificar si un jugador ha salido por la parte de atrás y reposicionar
    if (jugador1.getX() < -camaraX) {
        jugador1.setX((jugador2.getX() - camaraX) / 2);
        penalizarJugador(1, 10); // Penaliza al jugador 1 con 10 puntos
    }
    if (jugador2.getX() < -camaraX) {
        jugador2.setX((jugador1.getX() - camaraX) / 2);
        penalizarJugador(2, 10); // Penaliza al jugador 2 con 10 puntos
    }
    float tiempoActual = ofGetElapsedTimef();
    if (tiempoActual - tiempoAnterior >= 1.0f) { // Aumenta la puntuación cada segundo
        puntuacionJugador1++;
        puntuacionJugador2++;
        tiempoAnterior = tiempoActual;
    }

    // Actualizar el color de fondo
    float tiempo = ofGetElapsedTimef();
    float r = (sin(tiempo * 0.5) + 1) * 127;
    float g = (sin(tiempo * 0.5 + (2 * PI / 3)) + 1) * 127;
    float b = (sin(tiempo * 0.5 + (4 * PI / 3)) + 1) * 127;
    colorFondo.set(r, g, b);



    if (vidasJugador1 <= 0 || vidasJugador2 <= 0) {
        if (salioGanador)
        {
            // Pausa la ejecución del programa durante 5 segundos
            std::this_thread::sleep_for(std::chrono::seconds(5));
            resetJuego();
            salioGanador = false;

        }

    }
    if (jugador1.getX() == jugador2.getX() && jugador1.getY() == jugador2.getY()) {//parche feo para arreglar el problema del inicio
        inicio = true;
    }
}
void ofApp::agregarEnemigos() {
    //Oleada 1 
    enemigos.push_back(Enemigo(400, ofGetHeight() * 2 / 3 - 50, 50, 50));
    enemigos.push_back(Enemigo(600, ofGetHeight() * 2 / 3 - 50, 50, 50));

    //Oleada 2
    enemigos.push_back(Enemigo(1000, ofGetHeight() * 2 / 3 - 50, 50, 50));
    enemigos.push_back(Enemigo(1100, ofGetHeight() * 2 / 3 - 50, 50, 50));
    enemigos.push_back(Enemigo(1200, ofGetHeight() * 2 / 3 - 50, 50, 50));

    //Oleada 3
    enemigos.push_back(Enemigo(1600, ofGetHeight() * 2 / 3 - 50, 50, 50));
    enemigos.push_back(Enemigo(1700, ofGetHeight() * 2 / 3 - 50, 50, 50));
}
bool ofApp::colisionaEnemigo(const Jugador& jugador, const Enemigo& enemigo) const {
    float distanciaX = jugador.getX() + jugador.getAncho() / 2 - (enemigo.getX() + enemigo.getAncho() / 2);
    float distanciaY = jugador.getY() + jugador.getAlto() / 2 - (enemigo.getY() + enemigo.getAlto() / 2);
    float distanciaCentros = sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
    float sumaRadios = jugador.getAncho() / 2 + enemigo.getAncho() / 2;
    return distanciaCentros <= sumaRadios;
}
void ofApp::checkSalidaPantalla() {
    bool salir = false;
    bool jugador_1 = false;
    if (jugador1.getX() < camaraX - (ofGetWidth()/2) + 50) {
        vidasJugador1--;
        salir = true;
        jugador_1 = true;
    }
    if (jugador2.getX() < camaraX -(ofGetWidth() / 2) + 50) {
        vidasJugador2--;
        salir = true;
    }
    if (salir) {
        if (vidasJugador1 <= 0 || vidasJugador2 <= 0) {

            if (salioGanador)
            {
                // Pausa la ejecución del programa durante 5 segundos
                std::this_thread::sleep_for(std::chrono::seconds(5));
                resetJuego();
                salioGanador = false;
            }
        }
        else {
            float centerX = (jugador1.getX() + jugador2.getX()) / 2;
            float centerY = (jugador1.getY() + jugador2.getY()) / 2;
            if (jugador_1)
            {
                jugador1.setX(centerX - jugadorRadio);
                jugador1.setY(centerY - jugadorRadio);
            }
            else {
                jugador2.setX(centerX + jugadorRadio);
                jugador2.setY(centerY - jugadorRadio);
            }


        }
    }
}
void ofApp::draw() {
    // Mover la cámara en función de la posición media de los jugadores
    ofPushMatrix();

    // Establecer el color de fondo actualizado
    ofBackground(colorFondo);

    // Calcular la posición de la cámara
    glm::vec2 camaraPosicion = calcularCamaraPosicion();

    // Aplicar la rotación y la traslación de la cámara antes de dibujar los objetos en la escena
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateZDeg(angulo);
    ofTranslate(-camaraPosicion.x, -camaraPosicion.y);

    // Dibujar el mapa
    ofSetColor(255, 255, 255); // Establece el color a blanco
    mapa.dibujarMapa();

    // Dibujar el jugador1 con borde negro
    ofSetColor(0, 0, 255); // Establecer el color de relleno a azul
    ofFill(); // Activar el relleno
    ofDrawRectangle(jugador1.getX(), jugador1.getY(), 50, 50); // Dibujar el rectángulo con relleno azul
    ofSetColor(0, 0, 0); // Establecer el color del borde a negro
    ofNoFill(); // Desactivar el relleno para dibujar solo el borde
    ofDrawRectangle(jugador1.getX(), jugador1.getY(), 50, 50); // Dibujar el borde negro

    // Dibujar el jugador2 con borde negro
    ofSetColor(255, 0, 255); // Establecer el color de relleno a magenta
    ofFill(); // Activar el relleno
    ofDrawRectangle(jugador2.getX(), jugador2.getY(), 50, 50); // Dibujar el rectángulo con relleno magenta
    ofSetColor(0, 0, 0); // Establecer el color del borde a negro
    ofNoFill(); // Desactivar el relleno para dibujar solo el borde
    ofDrawRectangle(jugador2.getX(), jugador2.getY(), 50, 50); // Dibujar el borde negro

    // Dibujar los obstáculos con borde negro
    ofSetColor(255, 255, 255); // Establecer el color de relleno a blanco
    for (const auto& obstaculo : obstaculos) {
        ofSetColor(255, 0, 0); // Establecer el color de relleno a rojo
        ofFill(); // Activar el relleno
        ofDrawRectangle(obstaculo.getX(), obstaculo.getY(), obstaculo.getAncho(), obstaculo.getAlto()); // Dibujar el rectángulo con relleno rojo

        ofSetColor(0, 0, 0); // Establecer el color del borde a negro
        ofNoFill(); // Desactivar el relleno para dibujar solo el borde
        ofDrawRectangle(obstaculo.getX(), obstaculo.getY(), obstaculo.getAncho(), obstaculo.getAlto()); // Dibujar el borde negro
    }
    // Dibuja los enemigos
    for (int i = 0; i < enemigos.size(); i++) {
        enemigos[i].draw();
    }

    // Regresar al sistema de coordenadas original
    ofPopMatrix();

    // Dibujar vidas de los jugadores
    ofSetColor(0, 0, 255); // Establecer el color del texto al mismo color que el jugador 1
    string vidasTextoJugador1 = "Vidas Jugador 1: " + ofToString(vidasJugador1);
    ofDrawBitmapString(vidasTextoJugador1, 10, 20); // Dibujar el texto en la parte superior izquierda

    ofSetColor(255, 0, 255); // Establecer el color del texto al mismo color que el jugador 2
    string vidasTextoJugador2 = "Vidas Jugador 2: " + ofToString(vidasJugador2);
    ofDrawBitmapString(vidasTextoJugador2, 10, 40); // Dibujar el texto un poco más abajo del texto del jugador 1

    if (vidasJugador1 == 0) {
        mostrarMensajeGanador("Jugador 2");
    }
    else if (vidasJugador2 == 0) {
        mostrarMensajeGanador("Jugador 1");
    }


}
void ofApp::penalizarJugador(int jugador, int penalizacion) {
    if (jugador == 1) {
        puntuacionJugador1 -= penalizacion;
        puntuacionJugador1 = std::max(0, puntuacionJugador1); // Evita puntuaciones negativas
    }
    else if (jugador == 2) {
        puntuacionJugador2 -= penalizacion;
        puntuacionJugador2 = std::max(0, puntuacionJugador2); // Evita puntuaciones negativas
    }
}
void ofApp::verificarColisiones() {

    // Verificar colisiones con el suelo
    if (jugador1.getY() > sueloY) {
        jugador1.setY(sueloY);
    }
    if (jugador2.getY() > sueloY) {
        jugador2.setY(sueloY );
    }
    // Verificar colisiones con el techo
    if (jugador1.getY() < techoAltura) {
        jugador1.setY(techoAltura);
        jugador1.setVelocidadY(0);
    }
    if (jugador2.getY() < techoAltura) {
        jugador2.setY(techoAltura);
        jugador2.setVelocidadY(0);
    }

    // Comprobar la colisión con obstáculos
    for (const auto& obstaculo : obstaculos) {
        if (colisionaObstaculo(jugador1, obstaculo)) {
            // Resuelve la colisión (por ejemplo, detén el movimiento del jugador)
            float diferenciaY = std::abs(jugador1.getY() + jugador1.getAlto() - obstaculo.getY());
            if (diferenciaY < 5) { // Ajuste este valor según sea necesario
                jugador1.setY(obstaculo.getY() - jugador1.getAlto());
                jugador1.setVelocidadY(0);
            }
            else {
                if (jugador1.getX() < obstaculo.getX()) {
                    jugador1.setX(obstaculo.getX() - jugador1.getAncho());
                }
                else {
                    jugador1.setX(obstaculo.getX() + obstaculo.getAncho());
                }
                jugador1.setVelocidadX(0);
            }
        }
        if (colisionaObstaculo(jugador2, obstaculo)) {
            // Resuelve la colisión
            float diferenciaY = std::abs(jugador2.getY() + jugador2.getAlto() - obstaculo.getY());
            if (diferenciaY < 5) { // Ajuste este valor según sea necesario
                jugador2.setY(obstaculo.getY() - jugador2.getAlto());
                jugador2.setVelocidadY(0);
            }
            else {
                if (jugador2.getX() < obstaculo.getX()) {
                    jugador2.setX(obstaculo.getX() - jugador2.getAncho());
                }
                else {
                    jugador2.setX(obstaculo.getX() + obstaculo.getAncho());
                }
                jugador2.setVelocidadX(0);
            }
        }
    }
    // Comprobar la colisión con enemigos
    for (const auto& enemigo : enemigos) {
        if (colisionaEnemigo(jugador1, enemigo)) {
            vidasJugador1--;
            jugador1.setX(ofGetWidth() / 2 - jugadorRadio);
            jugador1.setY(ofGetHeight() / 2 - jugadorRadio);
        }
        if (colisionaEnemigo(jugador2, enemigo)) {
            vidasJugador2--;
            jugador2.setX(ofGetWidth() / 2 + jugadorRadio);
            jugador2.setY(ofGetHeight() / 2 - jugadorRadio);
        }
    }
    // Mantener a los jugadores dentro de la ventana de la aplicación
    jugador1.setX(std::max(0.0f, std::min(3000.f - 50.0f, jugador1.getX())));
    jugador2.setX(std::max(0.0f, std::min(3000.f - 50.0f, jugador2.getX())));
}
ofApp::ofApp()
{
}
void ofApp::resetJuego() {
    inicio = false;
    vidasJugador1 = 3;
    vidasJugador2 = 3;
    puntuacionJugador1 = 0;
    puntuacionJugador2 = 0;
    jugador1.setX(0);
    jugador1.setY(ofGetHeight() / 2 - jugadorRadio);
    jugador2.setX(0);
    jugador2.setY(ofGetHeight() / 2 - jugadorRadio);
}
void ofApp::mostrarMensajeGanador(string ganador) {
    string mensaje = ganador + " ha ganado!";

    // Establece el color del texto a blanco
    ofSetColor(255, 255, 255);

    // Calcular el ancho y alto del texto
    float textWidth = mensaje.length() * 8; // 8 pixels de ancho por caracter
    float textHeight = 14; // 14 pixels de alto por caracter

    // Calcular las coordenadas (x, y) para centrar el texto en la pantalla
    float posX = (ofGetWidth() - textWidth) / 2.0f;
    float posY = (ofGetHeight() - textHeight) / 2.0f;

    // Dibujar el mensaje de ganador centrado en la pantalla
    ofDrawBitmapString(mensaje, posX, posY);

    salioGanador = true;
}



void ofApp::keyPressed(int key) {
    jugador1.keyPressed(key); // Propaga la tecla presionada al objeto jugador1
    jugador2.keyPressed(key); // Propaga la tecla presionada al objeto jugador2

    if (key == ' ' || key == '1') {
        angulo += 90;
        if (angulo >= 360) {
            angulo = 0;
        }
        jugador1.update_aungulo(angulo);
        jugador2.update_aungulo(angulo);
    }
}
void ofApp::keyReleased(int key) {
    jugador1.keyReleased(key); // Propaga la tecla liberada al objeto jugador1
    jugador2.keyReleased(key); // Propaga la tecla liberada al objeto jugador2
}
void ofApp::agregarObstaculos() {
    obstaculos.emplace_back(200, ofGetHeight() * 2 / 3 - 100, 50, 50);
    obstaculos.emplace_back(250, ofGetHeight() * 2 / 3 - 100, 50, 100);
    obstaculos.emplace_back(250, ofGetHeight() * 2 / 3 - 400, 100, 200);
    obstaculos.emplace_back(400, ofGetHeight() * 2 / 3 - 200, 300, 50);
    obstaculos.emplace_back(550, ofGetHeight() * 2 / 3 - 250, 100, 50);
    obstaculos.emplace_back(600, ofGetHeight() * 2 / 3 - 250, 50, 150);
    obstaculos.emplace_back(500, ofGetHeight() * 2 / 3 - 50, 50, 50);
    obstaculos.emplace_back(700, ofGetHeight() * 2 / 3 - 100, 500, 50);
    obstaculos.emplace_back(750, ofGetHeight() * 2 / 3 - 500, 50, 150);
    obstaculos.emplace_back(850, ofGetHeight() * 2 / 3 - 500, 50, 150);
    obstaculos.emplace_back(950, ofGetHeight() * 2 / 3 - 500, 50, 100);
    obstaculos.emplace_back(1000, ofGetHeight() * 2 / 3 - 250, 50, 50);
    obstaculos.emplace_back(1200, ofGetHeight() * 2 / 3 - 250, 50, 100);
    obstaculos.emplace_back(1100, ofGetHeight() * 2 / 3 - 350, 100, 50);
    obstaculos.emplace_back(1400, ofGetHeight() * 2 / 3 - 100, 50, 100);
    obstaculos.emplace_back(1350, ofGetHeight() * 2 / 3 - 400, 50, 150);
    obstaculos.emplace_back(1350, ofGetHeight() * 2 / 3 - 400, 200, 50);
    obstaculos.emplace_back(1500, ofGetHeight() * 2 / 3 - 200, 100, 200);
    obstaculos.emplace_back(1550, ofGetHeight() * 2 / 3 - 400, 50, 150);
    obstaculos.emplace_back(1600, ofGetHeight() * 2 / 3 - 500, 50, 250);
    obstaculos.emplace_back(1600, ofGetHeight() * 2 / 3, 50, 200);
}
bool ofApp::colisionaObstaculo(const Jugador& jugador, const Obstaculo& obstaculo) const {
    float jugadorX = jugador.getX();
    float jugadorY = jugador.getY();
    float jugadorAncho = jugador.getAncho();
    float jugadorAlto = jugador.getAlto();
    float obstaculoX = obstaculo.getX();
    float obstaculoY = obstaculo.getY();
    float obstaculoAncho = obstaculo.getAncho();
    float obstaculoAlto = obstaculo.getAlto();

    bool colisionaEnX = jugadorX + jugadorAncho > obstaculoX && jugadorX < obstaculoX + obstaculoAncho;
    bool colisionaEnY = jugadorY + jugadorAlto > obstaculoY && jugadorY < obstaculoY + obstaculoAlto;

    return colisionaEnX && colisionaEnY;
}
glm::vec2 ofApp::convertirCoordenadas(float x, float y, float angulo, float camaraX, float camaraY) {
    glm::vec2 centroPantalla(ofGetWidth() / 2, ofGetHeight() / 2);
    glm::vec2 posicionRelativa(x - camaraX, y - camaraY);
    float radianes = glm::radians(-angulo);
    glm::vec2 rotado(
        posicionRelativa.x * cos(radianes) - posicionRelativa.y * sin(radianes),
        posicionRelativa.x * sin(radianes) + posicionRelativa.y * cos(radianes)
    );
    return centroPantalla + rotado;
}
float ofApp::getTecho()
{
    return techoAltura;
}
float ofApp::getSuelo()
{
    return sueloY;
}
