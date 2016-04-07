#include "vec.h"

#ifndef OBJ_H
#define OBJ_H

typedef struct {
    VEC_T origin;
    VEC_T direction;
} RAY_T;

typedef struct {
    VEC_T center;
    double radius;
} SPHERE_T;

typedef struct {
    double r;
    double g;
    double b;
} COLOR_T;

typedef struct OBJ {
    SPHERE_T sphere;
    COLOR_T color;
    struct OBJ *next;
} OBJ_T;

void read_objs(OBJ_T **list);
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t);
COLOR_T cast(RAY_T ray, OBJ_T *list);

#endif
