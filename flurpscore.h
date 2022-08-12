#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <cglm/cglm.h> // TODO : Find a better spot for this.

#include "fonts.h"     // TODO : Find a better spot for this.

void setBackgroundColor(float red, float green, float blue);
void showGLLoggingVersion(void);
void clearScreen(void);

int getWidth(void);
int getHeight(void);
void setWidth(int width);
void setHeight(int hidth);

int isMouseMoved(void);
void setMouseMovedFalse(void);
void zeroMouseLeftReleased(void);
void zeroMouseMiddleReleased(void);
void zeroMouseRightReleased(void);

int createWindow(const char* title, int width, int height);
int isClosed(void);
void clearScreen(void);
void updateWindow(void);
void closeWindow(void);
void processInput(void);

#endif // _PLATFORM_H_
