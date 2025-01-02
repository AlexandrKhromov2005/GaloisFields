#ifndef GALOISFIELDEXPLORE_H
#define GALOISFIELDEXPLORE_H

#include "galoisField.h"
#include <stdlib.h>
#include <string.h>

GF_TYPE findOrder(GFElement* poly, GFElement* irrPoly, GF_TYPE p, size_t size);
void findCycleGroup(GF* galoisField);

#endif //GALOISFIELDEXPLORE_H
