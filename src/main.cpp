#include "app/App.h"

const bool DEBUG_MODE = false;

int main(int argc, const char *argv[])
{

    if (App::Singleton().Init(DEBUG_MODE))
    {
        App::Singleton().Run();
    }
    return 0;
}

