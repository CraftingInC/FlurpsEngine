
#include "ogl.h"
#include "logging.h"
#include "flurpscore.h"
#include <GLFW/glfw3.h>

unsigned int VAO1;
unsigned int FBO;
unsigned int mainTexture = 0;

int textureImageWidth;
int textureImageHeight;

float textureRed   = 1.0f;
float textureGreen = 1.0f;
float textureBlue  = 1.0f;
float textureAlpha = 1.0f;

float mainClearscreenRed      = 0.0f;
float mainClearscreenGreen    = 0.0f;
float mainClearscreenBlue     = 0.0f;

float textureClearscreenRed   = 0.0f;
float textureClearscreenGreen = 0.0f;
float textureClearscreenBlue  = 0.0f;
float textureClearscreenAlpha = 0.0f;

float mainRectRed   = 0.0f;
float mainRectGreen = 0.0f;
float mainRectBlue  = 0.0f;
float mainRectAlpha = 0.0f;

void setTextureColors(float r, float g, float b, float a)
{
    textureRed   = r;
    textureGreen = g;
    textureBlue  = b;
    textureAlpha = a;
}

void setMainRectColor(float r, float g, float b, float a)
{
    mainRectRed   = r;
    mainRectGreen = g;
    mainRectBlue  = b;
    mainRectAlpha = a;
}

unsigned int createImage()
{
    unsigned int texture = 0;
    BMPIMAGE mImage;
    if(loadBMPImage(&mImage, "test.bmp") == 0)
    {
        wprintf(L"TEST.BMP failed to load.\n");
    } else {
        textureImageWidth  = mImage.width;
        textureImageHeight = mImage.height;
     //   glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImageWidth, textureImageHeight, 0,  GL_BGRA, GL_UNSIGNED_BYTE, mImage.pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        cleanBMPImage();
    }
    return texture;
}

void drawTextureScreen()
{
    unsigned int texture = createImage();
    glClearColor(textureClearscreenRed, textureClearscreenGreen, textureClearscreenBlue, textureClearscreenAlpha);
    glViewport(0, 0, textureImageWidth, textureImageHeight);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    useTextureShader();
    int vertexColorLocation = glGetUniformLocation(getTextureShaderProgramID(), "texColor");
    glUniform4f(vertexColorLocation, textureRed, textureGreen, textureBlue, textureAlpha);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &mainTexture);
    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImageWidth, textureImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mainTexture, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        wprintf(L"You got issues with your framebuffer\n");
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    int noderect = glGetUniformLocation(getNodeShaderProgramID(), "iNodeRect");
    useNodeShader();
    glUniform4f(noderect, 250, 250, 100, 75);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO2);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteTextures(1, &texture);
    glViewport(0, 0, getWidth(), getHeight());
    glClearColor(mainClearscreenRed, mainClearscreenGreen, mainClearscreenBlue, 1.0);
}

void drawMainScreen(float winX, float winY)
{
    glViewport(winX, winY, textureImageWidth, textureImageHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    useMainShader();
    int vertexColorLocation = glGetUniformLocation(getMainShaderProgramID(), "Color");
    glUniform4f(vertexColorLocation, mainRectRed, mainRectGreen, mainRectBlue, mainRectAlpha);
    glBindVertexArray(VAO1);
    glBindTexture(GL_TEXTURE_2D, mainTexture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void generateObjects()
{
    if(VAO1)
    {
        glDeleteVertexArrays(1, &VAO1);
    }
    glGenVertexArrays(1, &VAO1);
}

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
	logging("INFO : GLAD --> OpenGL Working.");
	logging("INFO : OpenGL Version : %s", glGetString(GL_VERSION));
}


void setMainClearscreenColor(float mred, float mgreen, float mblue)
{
    mainClearscreenRed   = mred;
    mainClearscreenGreen = mgreen;
    mainClearscreenBlue  = mblue;
}

void setTextureClearscreenColor(float tred, float tgreen, float tblue, float talpha)
{
    textureClearscreenRed   = tred;
    textureClearscreenGreen = tgreen;
    textureClearscreenBlue  = tblue;
    textureClearscreenAlpha = talpha;
}

void enableBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void cleanupOjects()
{
    glDeleteVertexArrays(1, &VAO1);
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &mainTexture);
}

