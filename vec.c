#include <math.h>
#include "vec.h"

VEC_T normalize(VEC_T v) {
   double mag = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
   v.x = v.x / mag;
   v.y = v.y / mag;
   v.z = v.z / mag;
   return v;
}

double dot(VEC_T v1, VEC_T v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
