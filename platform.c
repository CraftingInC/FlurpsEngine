
#include "flurpscore.h"
#include "logging.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>  // malloc()   free()

struct _WINDOW
{
    GLFWwindow* window;
    int width, height;
};

struct _WINDOW* win;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    win->width = width;
    win->height = height;
    clearScreen();
    updateWindow();
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int getWidth()
{
    return win->width;
}

int getHeight()
{
    return win->height;
}

void setWidth(int width)
{
    win->width = width;
}

void setHeight(int height)
{
    win->height = height;
}

int createWindow(const char* title, int width, int height)
{
    log("INFO : Initializing GLFW3 and Creating Window ...");
    if (!glfwInit())
        return -1;

    win = malloc(sizeof(struct _WINDOW));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!win->window)
    {
        glfwTerminate();
        return -1;
    }

    log("INFO : Window Created.");

    glfwMakeContextCurrent(win->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    log("ERROR : Failed to initialize OpenGL context !");
        glfwTerminate();
        return -1;
	}

	log("INFO : GLAD --> OpenGL Working.");
	log("INFO : OpenGL Version : %s", glGetString(GL_VERSION));

	glfwSetFramebufferSizeCallback(win->window, framebuffer_size_callback);
	glfwSetCursorPosCallback(win->window, mouse_callback);
	glfwSetMouseButtonCallback(win->window, mouse_button_callback);
	glfwSetScrollCallback(win->window, scroll_callback);

	return 1;
}

void setBackgroundColor(float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
}

int isClosed()
{
    return !glfwWindowShouldClose(win->window);
}

void clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void updateWindow()
{
    glfwSwapBuffers(win->window);
    glfwPollEvents();
}

void closeWindow()
{
    if(win){free(win);};
    glfwTerminate();
    log("INFO : Program terminated successfully.");
}
