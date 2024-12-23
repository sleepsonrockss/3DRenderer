#ifndef ASSG_H
#define ASSG_H

#include "vector.h"
#include "spheres.h"
#include "color.h"

// Global variables for light and background color
extern Vec3 lightPosition;
extern float lightBrightness;
extern Vec3 backgroundColor;

// Functions for ray tracing
void calculateColor(FILE *ppmFile, int width, int height);

#endif

//hello
