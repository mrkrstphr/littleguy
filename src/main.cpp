#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <SDL/SDL.h>

#include "Application.h"

int main (int argc, char *argv[]) {
    srand(time(NULL));

    Application *app = new Application();
    
    app->run();

    delete app;

    return 0;
}
