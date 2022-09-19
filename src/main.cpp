
#include <iostream>
#include "app/App.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

int main(int argc, const char *argv[])
{
    if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, 3))
    {
        App::Singleton().Run();
    }
    //
    return 0;
}
