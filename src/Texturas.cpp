#include "Texturas.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>
#include <iostream>
GLuint Texturas::cargarTextura(const char* ruta)
{
    GLuint texturaID;
    glGenTextures(1, &texturaID);

    int ancho, alto, canales;
    unsigned char* imagen = stbi_load(ruta, &ancho, &alto, &canales, 0);
    if (imagen) {
        GLenum formato;
        if (canales == 1)
            formato = GL_RED;
        else if (canales == 3)
            formato = GL_RGB;
        else if (canales == 4)
            formato = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texturaID);
        glTexImage2D(GL_TEXTURE_2D, 0, formato, ancho, alto, 0, formato, GL_UNSIGNED_BYTE, imagen);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Error al cargar textura: " << ruta << std::endl;
    }
    stbi_image_free(imagen);
    return texturaID;
}