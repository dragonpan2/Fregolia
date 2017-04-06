#ifndef SHADERUTILITIES_H_INCLUDED
#define SHADERUTILITIES_H_INCLUDED

#include "ExternalIncludes.h"

GLuint createProgram(std::string pVertexShaderPath, std::string pFragmentShaderPath);
GLuint createShader(std::string pShaderPath, GLenum pShaderType);

#endif // SHADERUTILITIES_H_INCLUDED
