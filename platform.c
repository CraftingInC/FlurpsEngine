
#include "flurpscore.h"
#include "ogl.h"
#include <GLFW/glfw3.h>

#include "logging.h"
#include <stdlib.h>  // malloc()   free()

struct _RECT         // TODO : Verify if this is where this belongs
{
    int x, y;
    int width, height;
};

struct _RECT* RECT;

struct _WINDOW
{
    GLFWwindow* window;
    int width, height;
};

struct _MSTATS {
    int xpos;
    int ypos;
    int mouseMoved;
    int isLeftMouseDown;
    int isMiddleMouseDown;
    int isRightMouseDown;
    int isLeftMouseReleased;
    int isMiddleMouseReleased;
    int isRightMouseReleased;
    int wheelState;
} MOUSESTATS;

struct _WINDOW* win;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    win->width = width;
    win->height = height;
    setGLViewport(win->width, win->height);
    clearScreen();
    updateWindow();
}

int isMouseMoved()
{
    return MOUSESTATS.mouseMoved;
}

void setMouseMovedFalse()
{
    MOUSESTATS.mouseMoved = 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    MOUSESTATS.xpos = (int)(xposIn);
    MOUSESTATS.ypos = (int)(yposIn);

    MOUSESTATS.mouseMoved = 1;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        MOUSESTATS.isLeftMouseDown = 1;
        MOUSESTATS.isLeftMouseReleased = 0;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        MOUSESTATS.isLeftMouseDown = 0;
        MOUSESTATS.isLeftMouseReleased = 1;
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        MOUSESTATS.isMiddleMouseDown = 1;
        MOUSESTATS.isMiddleMouseReleased = 0;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        MOUSESTATS.isMiddleMouseDown = 0;
        MOUSESTATS.isMiddleMouseReleased = 1;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        MOUSESTATS.isRightMouseDown = 1;
        MOUSESTATS.isRightMouseReleased = 0;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        MOUSESTATS.isRightMouseDown = 0;
        MOUSESTATS.isRightMouseReleased = 1;
    }
}

void zeroMouseLeftReleased()
{
    MOUSESTATS.isLeftMouseReleased = 0;
}

void zeroMouseMiddleReleased()
{
    MOUSESTATS.isMiddleMouseReleased = 0;
}

void zeroMouseRightReleased()
{
    MOUSESTATS.isRightMouseReleased = 0;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset < 0)
    {
        MOUSESTATS.wheelState = -1;
    } else if(yoffset > 0)
    {
        MOUSESTATS.wheelState = 1;
    }
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

void processInput()
{
    if(glfwGetKey(win->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(win->window, 1);
    }

    if(isMouseMoved() && MOUSESTATS.isLeftMouseDown)
    {
        wprintf(L"X: %d / Y: %d\n", MOUSESTATS.xpos, MOUSESTATS.ypos);
    }

    if(MOUSESTATS.isLeftMouseDown)
    {
        wprintf(L"LEFT BUTTON DOWN\n");
    }
    if(MOUSESTATS.isMiddleMouseDown)
    {
        wprintf(L"MIDDLE BUTTON DOWN\n");
    }
    if(MOUSESTATS.isRightMouseDown)
    {
        wprintf(L"RIGHT BUTTON DOWN\n");
    }

    if(MOUSESTATS.isLeftMouseReleased)
    {
        wprintf(L"LEFT BUTTON RELEASED\n");
        zeroMouseLeftReleased();
    }
    if(MOUSESTATS.isMiddleMouseReleased)
    {
        wprintf(L"MIDDLE BUTTON RELEASED\n");
        zeroMouseMiddleReleased();
    }
    if(MOUSESTATS.isRightMouseReleased)
    {
        wprintf(L"RIGHT BUTTON RELEASED\n");
        zeroMouseRightReleased();
    }

    if(MOUSESTATS.wheelState == -1)
    {
        wprintf(L"MOUSE WHEEL -1\n");
        MOUSESTATS.wheelState = 0;
    } else if(MOUSESTATS.wheelState == 1)
    {
        wprintf(L"MOUSE WHEEL 1\n");
        MOUSESTATS.wheelState = 0;
    }
}

int createWindow(const char* title, int width, int height)
{
    logs("INFO : Initializing GLFW3 and Creating Window ...");
    if (!glfwInit())
        return -1;

    win = malloc(sizeof(struct _WINDOW));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!win->window)
    {
        closeWindow();
        return -1;
    }

    logs("INFO : Window Created.");

    glfwMakeContextCurrent(win->window);
    if(!initGLAD())
    {
	    logs("ERROR : Failed to initialize OpenGL context !");
        closeWindow();
        return -1;
	}

	showGLLoggingVersion();

	glfwSetFramebufferSizeCallback(win->window, framebuffer_size_callback);
	glfwSetCursorPosCallback(win->window, mouse_callback);
	glfwSetMouseButtonCallback(win->window, mouse_button_callback);
	glfwSetScrollCallback(win->window, scroll_callback);

	return 1;
}

int isClosed()
{
    return !glfwWindowShouldClose(win->window);
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
    logs("INFO : Program terminated successfully.");
}
