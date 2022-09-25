
#include "app/App.h"

const int SCREEN_WIDTH = 384;
const int SCREEN_HEIGHT = 216;

int main(int argc, const char *argv[])
{
    if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, 4))
    {
        App::Singleton().Run();
    }
    return 0;
}

// TODO

// Better classes structure
// Add post processing methods
// Better water sim (water is very slow to move)
// Add brush circle shape
// Create clone points, when the space bar is pressed, a spawn of this element will be created
