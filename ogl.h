#ifndef _OGL_H_
#define _OGL_H_

#include <glad/gl.h>

#include "images.h"

void initGLAD(void);
void setGLViewport(int width, int height);
void generateObjects(void);
void drawTextureScreen(void);
void drawMainScreen(float winX, float winY);
void cleanupOjects(void);

// Shader Functions
void useTextureShader(void);
void useMainShader(void);
void useNodeShader(void);
void shaderCleanUp(void);
void installShaders(void);
int loadShaderFromFile(const char* fileName, int shaderType);
unsigned int initShaders(const char* vert, const char* frag);

unsigned int getMainProgramID(void);
void checkCompileErrors(unsigned int shader);
unsigned int getTextureShaderProgramID(void);
unsigned int getMainShaderProgramID(void);
unsigned int getNodeShaderProgramID(void);

// image test
unsigned int createImage();
void setTextureColors(float r, float g, float b, float a);
void setMainRectColor(float r, float g, float b, float a);

#endif // _OGL_H_
