
#include "app/App.h"

const int SCREEN_WIDTH = 384;
const int SCREEN_HEIGHT = 216;

int main(int argc, const char *argv[])
{
    if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, 5))
    {
        App::Singleton().Run();
    }
    return 0;
}
