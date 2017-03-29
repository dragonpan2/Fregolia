#ifndef EXTERNALINCLUDES_H_INCLUDED
#define EXTERNALINCLUDES_H_INCLUDED

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glew.h>

#include <SDL.h>
#include <SDL_mixer.h>

#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#define CONSTANTE_GRAVITE 9.8f
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

/// Obtenir le signe d'un nombre; TEMPORAIRE
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#define CONSTANTE_GRAVITE 9.8f
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#endif // EXTERNALINCLUDES_H_INCLUDED
