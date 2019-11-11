#ifndef COLOR_H_
#define COLOR_H_

#include "vector3d.h"

using Color = Vector3D;

const Color Black = {0, 0, 0};
const Color White = {1, 1, 1};

const Color Gray = {0.5, 0.5, 0.5};
const Color Lightgray = {0.9, 0.9, 0.9};

const Color Red = {0.8, 0.2, 0.2};
const Color Green = {0.2, 0.8, 0.2};
const Color Blue = {0.2, 0.2, 0.8};

const Color Orange = {1.0, 0.5, 0.0};
const Color Yellow = {1.0, 1.0, 0.0};
const Color Fuschia = {1.0, 0.0, 1.0};

const Color Sun = {1.0, 1.0, 0.95};

#endif // COLOR_H_
