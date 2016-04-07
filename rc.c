#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rc.h"

int main() {
    OBJ_T *list = NULL;
    read_objs(&list);
    OBJ_T *curr = list;
    COLOR_T pixel;
    RAY_T ray;
    double t;
    ray.origin.x = 0, ray.origin.y = 0, ray.origin.z = 0;
    int x, y;
    for (y = 0; y < 1000; y++) {
        for (x = 0; x < 1000; x++) {
            // set ray
            ray.direction.x = -0.5 + x / 1000.0;
            ray.direction.y = 0.5 - y / 1000.0;
            ray.direction.z = 1;

            ray.direction = normalize(ray.direction);

            if (intersect_sphere(ray, curr->sphere, &t)) {
                pixel = curr->color;
            }
            printf("%c %c %c", (unsigned char)(pixel.r*255), (unsigned char)(pixel.g*255), (unsigned char)(pixel.b*255));

        }
    }
}

COLOR_T cast(RAY_T ray, OBJ_T *list) {
    OBJ_T *curr;
    double min_t = 1000; // no bueno
    double t;
    COLOR_T color;
    for (curr = list; curr != NULL; curr = curr->next) {
        if (intersect_sphere(ray, curr->sphere, &t)) {
            if (t < min_t) {
                color = curr->color;
                min_t = t;
            }
        }
    }
    return color;
}

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t) {
    double A, B, C;
    A = 1;
    B = 2 * ((ray.origin.x * (ray.origin.x - sphere.center.x)) +
             (ray.origin.y * (ray.origin.y - sphere.center.y)) +
             (ray.origin.z * (ray.origin.z - sphere.center.z)));
    C = pow(ray.origin.x - sphere.center.x, 2) +
        pow(ray.origin.y - sphere.center.y, 2) +
        pow(ray.origin.z - sphere.center.z, 2);
    double discriminant = pow(B, 2) - 4*A*C;
    if (discriminant < 0) {
        return 0;
    }
    float t_0 = -B + sqrt(discriminant) / 2*A;
    float t_1 = -B - sqrt(discriminant) / 2*A;
    *t = t_0 < t_1 ? t_0 : t_1;
    return 1;
}

void read_objs(OBJ_T **list) {
    double center_x,
           center_y,
           center_z,
           radius,
           r,
           g,
           b;
    OBJ_T *new;
    while (scanf("%lf %lf %lf %lf %lf %lf %lf", &center_x, &center_y, &center_z, &radius, &r, &g, &b) == 7) {
        new = (OBJ_T *)malloc(sizeof(OBJ_T));
        new->sphere.center.x = center_x;
        new->sphere.center.y = center_y;
        new->sphere.center.z = center_z;
        new->sphere.radius = radius;
        new->color.r = r;
        new->color.g = g;
        new->color.b = b;
        new->next = *list;
        *list = new;
    }
}
