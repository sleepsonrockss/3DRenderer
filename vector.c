#include "vector.h"
#include <math.h>

// Subtract two vectors component-wise
Vec3 subtract(Vec3 v1, Vec3 v2) {
    Vec3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
} 

// Add two vectors component-wise
Vec3 add(Vec3 v1, Vec3 v2) {
    Vec3 sum;
    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    sum.z = v1.z + v2.z;
    return sum;
}

// Multiply each component of a vector by a scalar
Vec3 scalarMultiply(float s, Vec3 v) {
    Vec3 scaled;
    scaled.x = v.x * s;
    scaled.y = v.y * s;
    scaled.z = v.z * s;
    return scaled;
}

// Divide each component of a vector by a scalar
Vec3 scalarDivide(Vec3 v, float d) {
    Vec3 divided;
    divided.x = v.x / d;
    divided.y = v.y / d;
    divided.z = v.z / d;
    return divided;
}

// Calculate the Euclidean distance between two vectors
float distance(Vec3 v1, Vec3 v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// Compute the dot product of two vectors
float dot(Vec3 v1, Vec3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// Calculate the length (magnitude) of a vector
float length(Vec3 v) {
    return sqrt(dot(v, v));
}

// Normalize a vector to make its length equal to 1
Vec3 normalize(Vec3 v) {
    float len = length(v);
    Vec3 normalized;
    normalized.x = v.x / len;
    normalized.y = v.y / len;
    normalized.z = v.z / len;
    return normalized;
}


//hello
