#ifndef _OGL_H_
#define _OGL_H_

#include <glad/glad.h>

int initGLAD(void);
void setGLViewport(int width, int height);
void checkCompileErrors(unsigned int shader);

#endif // _OGL_H_
