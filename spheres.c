#include <stdlib.h>  // for malloc, realloc, free
#include <stddef.h>  // for NULL
#include <math.h>    // for math functions like sqrt, dot, etc.
#include "spheres.h"

void worldInit(World *world) {
    world->size = 0;
    world->capacity = 1;
    world->spheres = malloc(world->capacity * sizeof(Sphere *));
}

void addSphere(World *world, Sphere *sphere) {
    if (world->size == world->capacity) {
        world->capacity *= 2;
        world->spheres = realloc(world->spheres, world->capacity * sizeof(Sphere *));
    }
    world->spheres[world->size++] = sphere;
}

Sphere *createSphere(float radius, Vec3 position, Vec3 color) {
    Sphere *sphere = malloc(sizeof(Sphere));
    if (sphere != NULL) {
        sphere->r = radius;
        sphere->pos = position;
        sphere->color = color;
    }
    return sphere;
}

void freeWorld(World *world) {
    for (int i = 0; i < world->size; i++) {
        free(world->spheres[i]);
    }
    free(world->spheres);
    world->spheres = NULL;
    world->size = 0;
    world->capacity = 0;
}


// Ray-Sphere Intersection check
int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t) {
    // Vector from ray origin to sphere center
    Vec3 oc = subtract(rayPos, sphere->pos);
    
    // Compute the coefficients for the quadratic equation
    float a = dot(rayDir, rayDir);
    float b = 2.0f * dot(oc, rayDir);
    float c = dot(oc, oc) - sphere->r * sphere->r;
    
    // Compute the discriminant
    float discriminant = b * b - 4.0f * a * c;
    
    // If the discriminant is negative, there is no intersection
    if (discriminant < 0) {
        return 0; // No intersection
    }
    
    // Compute the two solutions for t (the intersection points)
    float sqrtDiscriminant = sqrt(discriminant);
    float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
    float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
    
    // If t0 is positive, the intersection is in front of the ray
    if (t0 > 0) {
        *t = t0;
    } else if (t1 > 0) {
        // Otherwise, check if t1 is positive
        *t = t1;
    } else {
        return 0; // Intersection is behind the ray
    }
    
    return 1; // There is an intersection
}
//hello
