#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
    ofSetupOpenGL(1024, 768, OF_WINDOW);  // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
/*
//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // Configurar GLFW para usar OpenGL 3.3 y crear una ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Topsy-Turvy World", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Hacer el contexto actual de la ventana
    glfwMakeContextCurrent(window);

    // Inicializar GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(glewError) << std::endl;
        glfwTerminate();
        return -1;
    }
    // Cargar el código fuente de los shaders
    std::string vertexShaderSource = cargarShader("vertexShader.glsl");
    std::string fragmentShaderSource = cargarShader("fragmentShader.glsl");

    // Compilar y vincular los shaders
    GLuint vertexShader = compilarShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = compilarShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
    GLuint shaderProgram = vincularShaders(vertexShader, fragmentShader);

    // Cargar textura del suelo
    Texturas texturas;
    GLuint texturaSuelo = texturas.cargarTextura("./assets/suelo.png");

    // Crear un objeto Jugador
    Jugador jugador1(100.0f, 100.0f, 50.0f, 50.0f);

    // Inicializar el mapa
    inicializarMapa();

    // Configurar matriz de proyección ortográfica
    glm::mat4 projection = glm::ortho(0.0f, 3000.f, 0.0f, 600.0f, -1.0f, 1.0f);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

    while (!glfwWindowShouldClose(window)) {
        // ...
        // Procesar entradas, actualizar
        // ...

        // Dibujar el mapa
        glUseProgram(shaderProgram);
        glBindVertexArray(mapaVAO);
        glBindTexture(GL_TEXTURE_2D, texturaSuelo);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Dibujar el jugador
        // Puedes crear una función similar a inicializarMapa y cargarTextura para inicializar y dibujar al jugador

        // ...
        //
    }

}

*/