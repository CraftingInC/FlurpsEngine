
#include "flurpscore.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wchar.h>

GLFWwindow* window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

int createWindow(const char* title, int wWidth, int wHeight)
{
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(wWidth, wHeight, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    wprintf(L"ERROR : Failed to initialize OpenGL context !\n");
        glfwTerminate();
        return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	return 1;
}

void setBackgroundColor(float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
}

int isClosed()
{
    return !glfwWindowShouldClose(window);
}

void clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void updateWindow()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void closeWindow()
{
    glfwTerminate();
}
