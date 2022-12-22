#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <cglm/cglm.h> // TODO : Find a better spot for this.
#include "images.h"    // TODO : Find a better spot for this.
#include "ogl.h"

float getRX(void);
float getRY(void);
int getMousePosX(void);
int getMousePosY(void);
int getIsMouseDown(void);

void setMainClearscreenColor(float mred, float mgreen, float mblue);
void setTextureClearscreenColor(float tred, float tgreen, float tblue, float talpha);
void showGLLoggingVersion(void);
void enableBlending(void);
void setVSync(int v);

int  getWidth(void);
int  getHeight(void);

int  isMouseMoved(void);
void setMouseMovedFalse(void);
void zeroMouseLeftReleased(void);
void zeroMouseMiddleReleased(void);
void zeroMouseRightReleased(void);

int  createWindow(const char* title, int width, int height);
int  isClosed(void);
void clearScreen(void);
void updateWindow();
void closeWindow(void);
void processInput(float fvX, float fvY);

#endif // _PLATFORM_H_
