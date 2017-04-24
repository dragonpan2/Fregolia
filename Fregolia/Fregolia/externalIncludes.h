#ifndef EXTERNALINCLUDES_H_INCLUDED
#define EXTERNALINCLUDES_H_INCLUDED

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glew.h>

#include <SDL.h>
#include <SDL_mixer.h>

#include <SOIL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <typeinfo>
#include <string>

//#pragma GCC poison setPos

#define CONSTANTE_GRAVITE 9.8f
#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 768.0f

/// Obtenir le signe d'un nombre; TEMPORAIRE
template <typename T> int signe(T nb) {
    return ((T)0 < nb) - (nb < (T)0);
}

#endif // EXTERNALINCLUDES_H_INCLUDED
