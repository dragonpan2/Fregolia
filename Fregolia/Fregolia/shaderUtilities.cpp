#include "shaderUtilities.h"

GLuint createShader(std::string pShaderPath, GLenum pShaderType)
{
    GLuint shader = glCreateShader(pShaderType);

    std::ifstream fichier;
    fichier.open(pShaderPath);
    std::string shaderCode, curLine;

    while(std::getline(fichier, curLine))
    {
        shaderCode.append(curLine);
        shaderCode.append("\n");
    }

    const char* shaderConvertedCode = shaderCode.c_str();
    glShaderSource(shader, 1, &(shaderConvertedCode), NULL);

    glCompileShader(shader);

    GLint compileCheck = GL_FALSE;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileCheck);
    if(!compileCheck)
    {
        glDeleteShader(shader);
        return -1;
    }

    return shader;
}

GLuint createProgram(std::string pVertexShaderPath, std::string pFragmentShaderPath)
{
    GLuint program = glCreateProgram();

    GLuint vertShader = createShader(pVertexShaderPath, GL_VERTEX_SHADER);
    if(vertShader == -1) return -1;
    GLuint fragShader = createShader(pFragmentShaderPath, GL_FRAGMENT_SHADER);
    if(fragShader == -1) return -2;

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);


    GLint linkCheck = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linkCheck);
    if(!linkCheck)
    {
        glDetachShader(program, vertShader);
        glDetachShader(program, fragShader);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        glDeleteProgram(program);
        return -3;
    }

    return program;
}


