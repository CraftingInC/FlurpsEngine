#ifndef _PLATFORM_H_
#define _PLATFORM_H_

int createWindow(const char* title, int wWidth, int wHeight);
void setBackgroundColor(float red, float green, float blue);
int isClosed(void);
void clearScreen(void);
void updateWindow(void);
void closeWindow(void);

#endif // _PLATFORM_H_
