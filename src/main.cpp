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

//------------------------------------------------
// TODO
//------------------------------------------------

// ELEMENTS ----------------------------

// Add Gas Element

// SIMULATION ------------------------------------

// Liquid liquid_density (Less dense liquids should swap with more dense liquids)
// Add gravity

// OPTIMIZATION ---------------------------------

// Do not use vector
// Do not use new keyword (use stack instead)

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
