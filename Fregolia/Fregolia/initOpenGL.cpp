#include "initOpenGL.h"

int initOpenGL(SDL_Window** mainWindow, SDL_GLContext* mainContext)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Quit();

        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    *mainWindow = SDL_CreateWindow("Fregolia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_HIDDEN /*| SDL_WINDOW_FULLSCREEN*/ | SDL_WINDOW_OPENGL);
    if(*mainWindow == 0)
    {
        SDL_Quit();
        return -1;
    }

    *mainContext = SDL_GL_CreateContext(*mainWindow);
    if(*mainContext == 0)
    {
        SDL_DestroyWindow(*mainWindow);
        SDL_Quit();
        return -1;
    }

    GLenum inGlew( glewInit() );
    if (inGlew != GLEW_OK)
    {
        SDL_GL_DeleteContext(*mainContext);
        SDL_DestroyWindow(*mainWindow);
        SDL_Quit();
        return -1;
    }

    /// Si tout s'est bien passé, on peut afficher la fenêtre
    SDL_ShowWindow(*mainWindow);

    return 0;
}
