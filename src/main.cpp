
#include "app/App.h"

const int SCREEN_WIDTH = 1920 / 4;
const int SCREEN_HEIGHT = 1080 / 4;

int main(int argc, const char *argv[])
{
    if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, 3))
    {
        App::Singleton().Run();
    }
    return 0;
}

// TODO

// Study remove the NextGrid Data
// Better classes structure
// Swap if element is more dense than the one it is moving into (like water and sand)
// Add post processing methods
// Better water sim (water is very slow to move)
// Add brush circle shape
// Create clone points, when the space bar is pressed, a spawn of this element will be created

// For the future

// Add HSV color changes
// Add a way to save and load grids
// Add a way to create custom elements
// mix different fluid elements, to get a new one with different color
