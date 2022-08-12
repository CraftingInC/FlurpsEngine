
#include "ogl.h"
#include "logging.h"

#include <GLFW/glfw3.h>

int initGLAD()
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

}

void setGLViewport(int width, int height)
{
    glViewport(0, 0, width, height);
}

void showGLLoggingVersion()
{
	logs("INFO : GLAD --> OpenGL Working.");
	logs("INFO : OpenGL Version : %s", glGetString(GL_VERSION));
}


void setBackgroundColor(float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
}

void clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

// TODO : Add Shader loading here
