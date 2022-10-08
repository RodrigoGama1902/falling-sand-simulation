
#include "app/App.h"

const bool DEBUG_MODE = true;

int main(int argc, const char *argv[])
{

    if (App::Singleton().Init(DEBUG_MODE))
    {
        App::Singleton().Run();
    }
    return 0;
}

//------------------------------------------------
// TODO
//------------------------------------------------

// GENERAL ---------------------------------------

// Better main app.cpp structure
// Fix #include different name styles, organize and remove unused #includes
// Optimization

// ELEMENTS STRUCTURE ----------------------------

// Add move and render method that will be called from update method.
// Add Gas Element

// SIMULATION ------------------------------------

// Liquid density (Less dense liquids should swap with more dense liquids)
// Add gravity

// RENDER ----------------------------------------

// Liquid color fade in is changing green only, refactor to change all colors, and make it fade in with different speeds

// BUGS ------------------------------------------

// When drawing, if draw out of the app screen, it crashes for some reason

// FOR THE FUTURE -------------------------------

// Add HSV color changes
// Add a way to save and load grids
// Add a way to create custom elements
// mix different fluid elements, to get a new one with different color
// Add post processing methods
// Create clone points, when the space bar is pressed, a spawn of this element will be created
