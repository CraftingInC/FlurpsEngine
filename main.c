
#define UNICODE
#include "flurpscore.h"

struct _vec2
{
    float x, y;
} fvec2;

int main(void)
{
    if(createWindow("Flurps Graphics Engine - Testing Prototype", 1280, 720) == 1)
    {
        setVSync(1);
        setMainClearscreenColor(0.1f, 0.1f, 0.1f);    // Set main clear screen color
        setTextureClearscreenColor(0.1f, 0.1f, 0.9f, 1.0); // Set texture clear screen color
        setTextureColors(1.0f, 1.0f, 1.0f, 1.0f);
        setMainRectColor(1.0f, 1.0f, 1.0f, 1.0f);
        enableBlending();
        drawTextureScreen();   // Draw image to the targetted buffer image

        fvec2.x = 300;
        fvec2.y = 100;

        while (isClosed())
        {
            processInput(fvec2.x, fvec2.y);
            if(getIsMouseDown())
            {
                fvec2.x = (float)getMousePosX() - getRX();
                fvec2.y = (float)getMousePosY() - getRY();
            }
            drawMainScreen(fvec2.x, fvec2.y);  // Draw targetted buffer image to main buffer
            updateWindow();
        }

        closeWindow();
        return 0;
    }
    return -1;
}
