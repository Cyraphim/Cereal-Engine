#include "Settings.h"

int Settings::FPS = 60;
std::string Settings::title = "Cereal Engine";
int Settings::width = 1280;
int Settings::height = 720;
int Settings::numKeys = 144;
// THIS IS OUR FIELD OF VIEW, DOESNT WORK ABOVE 100
// 60 IS ALOT, 70 IS NORMAL, 90 IS ALOT
// THIS DOESNT MAKE ANY SENSE BUT JUST GO WITH IT
float Settings::FOV = 70;
