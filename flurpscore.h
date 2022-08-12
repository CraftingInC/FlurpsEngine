#ifndef _PLATFORM_H_
#define _PLATFORM_H_

int getWidth(void);
int getHeight(void);
void setWidth(int width);
void setHeight(int hidth);

int createWindow(const char* title, int width, int height);
void setBackgroundColor(float red, float green, float blue);
int isClosed(void);
void clearScreen(void);
void updateWindow(void);
void closeWindow(void);

#endif // _PLATFORM_H_
