#include "color.h"
#include <stdio.h>
#include <math.h>

// Unpack RGB from hex (0xRRGGBB) format
Vec3 unpackRGB(unsigned int packedRGB) {
    // Extract RGB components from the packed HEX value
    float red = ((packedRGB >> 16) & 0xFF) / 255.0f;   // Extract red channel
    float green = ((packedRGB >> 8) & 0xFF) / 255.0f;  // Extract green channel
    float blue = (packedRGB & 0xFF) / 255.0f;          // Extract blue channel
   
    // Return as a Vec3
    return (Vec3){red, green, blue};
}


// Write a color to the PPM file
void writeColour(FILE *ppmFile, Vec3 color) {
    // Clamp each component to [0, 1] and convert to [0, 255] with rounding
    int r = (int)(roundf(fmin(1.0f, fmax(0.0f, color.x)) * 255));
    int g = (int)(roundf(fmin(1.0f, fmax(0.0f, color.y)) * 255));
    int b = (int)(roundf(fmin(1.0f, fmax(0.0f, color.z)) * 255));

    // Write the color in PPM format (space-separated)
    fprintf(ppmFile, "%d %d %d ", r, g, b);
}

// Compare two colors for sorting (useful for any sorting or comparison logic)


int compareColor(const void *a, const void *b)
{
    int a1 = 0, b1 = 0;
    for (int i = 0; i < sizeof(int); i++)
    {
        a1 |= (*((unsigned char*)a + i) & 0x0F) << (i * 8);
        b1 |= (*((unsigned char*)b + i) & 0x0F) << (i * 8);
    }
    
    return (a1 < b1) ? -1 : (b1 < a1) ? 1 : (*((int*)a) < *((int*)b)) ? -1 : (*((int*)a) > *((int*)b)) ? 1 : 0;
}
//hellos
