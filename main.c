
#define UNICODE
#include "flurpscore.h"

int main(void)
{
    if(createWindow("Flurps Engine - Testing Prototype", 800, 600) == 1)
    {
        setBackgroundColor(0.2f, 0.2f, 0.2f);
        while (isClosed())
        {
            processInput();

            // Game Logic here

            updateWindow();
        }
        closeWindow();
        return 0;
    }
    return -1;
}
