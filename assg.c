#include <stdio.h>
#include <stdlib.h>
#include "spheres.h"
#include "vector.h"
#include "color.h"
#include <math.h>

#define SHADOW_FACTOR 0.1
#define EPSILON 0.001

// Global variables
int imageWidth, imageHeight;
float viewportHeight, focalLength;
float viewportWidth;

Vec3 lightPosition;
float lightBrightness;
Vec3 backgroundColor = {0.0, 0.0, 0.0}; // Default background color
World world;

// Function to calculate viewport width
void calculateViewportWidth() {
    viewportWidth = viewportHeight * ((float)imageWidth / (float)imageHeight);
}

// Function to read input
void readInput(const char *inputFilePath) {
    FILE *file = fopen(inputFilePath, "r");
    if (file == NULL) {
        exit(1);
    }

    // Read image dimensions
    fscanf(file, "%d %d", &imageWidth, &imageHeight);

    // Read viewport dimensions
    fscanf(file, "%f", &viewportHeight);
    fscanf(file, "%f", &focalLength);

    // Calculate viewport width
    calculateViewportWidth();

    // Read light source position and brightness
    fscanf(file, "%f %f %f %f", &lightPosition.x, &lightPosition.y, &lightPosition.z, &lightBrightness);

    // Read number of colors
    int numColors;
    fscanf(file, "%d", &numColors);

    // Allocate memory for color list
    unsigned int *colors = malloc(numColors * sizeof(unsigned int));
    if (!colors) {
        fclose(file);
        exit(1);
    }

    // Read colors in HEX format
    for (int i = 0; i < numColors; i++) {
        fscanf(file, "%x", &colors[i]);
    }

    // Sort colors using qsort and compareColor
    qsort(colors, numColors, sizeof(unsigned int), compareColor);

    // Read background color index and assign background color
    int backgroundColorIndex;
    fscanf(file, "%d", &backgroundColorIndex);
    backgroundColor = unpackRGB(colors[backgroundColorIndex]);

    // Initialize the world to store spheres
    worldInit(&world);

    // Read number of spheres
    int numSpheres;
    fscanf(file, "%d", &numSpheres);

    // Read each sphere's properties and add to the world
    for (int i = 0; i < numSpheres; i++) {
        Vec3 position;
        float radius;
        int colorIndex;

        // Read sphere details
        fscanf(file, "%f %f %f %f %d", &position.x, &position.y, &position.z, &radius, &colorIndex);

        // Convert color index to RGB and create sphere
        Vec3 sphereColor = unpackRGB(colors[colorIndex]);
        Sphere *sphere = createSphere(radius, position, sphereColor);
        addSphere(&world, sphere);
    }

    // Free allocated memory for colors
    free(colors);

    fclose(file);
}

// Ray structure
typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

Vec3 traceRay(Ray ray) {
    float t = INFINITY;
    Sphere *hitSphere = NULL;

    // Find the closest intersection with any sphere
    for (int i = 0; i < world.size; i++) {
        Sphere *sphere = world.spheres[i];
        float tempT;
        if (doesIntersect(sphere, ray.origin, ray.direction, &tempT) && tempT < t) {
            t = tempT;
            hitSphere = sphere;
        }
    }

    if (hitSphere == NULL) {
        return backgroundColor;
    }

    // Calculate intersection point and normal
    Vec3 intersectionPoint = add(ray.origin, scalarMultiply(t, ray.direction));
    Vec3 normal = normalize(subtract(intersectionPoint, hitSphere->pos));

    // Basic lighting calculation (Diffuse only)
    Vec3 lightDir = normalize(subtract(lightPosition, intersectionPoint));
    float diffuseIntensity = fmax(0.0, dot(normal, lightDir));

    // Calculate distance from the light source to the intersection point
    float lightDistance = length(subtract(lightPosition, intersectionPoint));

    // Apply inverse square law for light intensity
    float intensity = (lightBrightness * diffuseIntensity) / (lightDistance * lightDistance); // Inverse square law

    // Clamp intensity to the range [0, 1]
    intensity = fmin(fmax(intensity, 0.0), 1.0);

    Vec3 surfaceLightingColor = scalarMultiply(intensity, hitSphere->color);

    // Shadow calculation
    Vec3 offsetIntersection = add(intersectionPoint, scalarMultiply(EPSILON, normal));
    float lightDistanceToIntersection = length(subtract(lightPosition, offsetIntersection));
    for (int i = 0; i < world.size; i++) {
        Sphere *sphere = world.spheres[i];
        float shadowT;
        if (doesIntersect(sphere, offsetIntersection, lightDir, &shadowT) && shadowT < lightDistanceToIntersection) {
            surfaceLightingColor = scalarMultiply(SHADOW_FACTOR, surfaceLightingColor);
            break;
        }
    }

    return surfaceLightingColor;
}

void renderImage(FILE *outputFile) {
    Vec3 cameraOrigin = {0.0, 0.0, 0.0};

    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", imageWidth, imageHeight);
    fprintf(outputFile, "255\n");

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            Vec3 pixelColor = {0.0, 0.0, 0.0};
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    float u = (((float)x + (dx + 0.5f) / 3.0f ) + 0.5f) / imageWidth * viewportWidth - viewportWidth / 2.0f;
                    float v = (((float)y + (dy + 0.5f) / 3.0f) + 0.5f) / imageHeight * viewportHeight - viewportHeight / 2.0f;
                    Vec3 rayDirection = normalize((Vec3){u, -v, -focalLength});
                    Ray ray = {cameraOrigin, rayDirection};
                    pixelColor = add(pixelColor, traceRay(ray));
                }
            }
            pixelColor = scalarDivide(pixelColor, 9.0);
            writeColour(outputFile, pixelColor);
        }
        fprintf(outputFile, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        return 1;
    }

    readInput(argv[1]);
    renderImage(outputFile);

    freeWorld(&world);
    fclose(outputFile);

    return 0;
}
//hello
