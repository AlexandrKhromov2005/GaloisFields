#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GF_TYPE unsigned char
#define MAX_N 21

typedef struct {
    GF_TYPE coeffs[MAX_N];
    GF_TYPE length;
} GFElement;

typedef struct {
    GF_TYPE n;
    GF_TYPE p;
    size_t size;
    GFElement irreduciblePoly;
    GFElement* field;
}GF;

void initGFE(GFElement* poly, GF_TYPE length, GF_TYPE coeffs[MAX_N]);
void printGFE(GFElement* poly, GF_TYPE n);
GFElement addGFE(GFElement* poly1, GFElement* poly2, GF_TYPE p);
GFElement substractGFE(GFElement* poly1, GFElement* poly2, GF_TYPE p);
void increaseGFE(GFElement* poly, GF_TYPE p);
void leftShiftGFE(GFElement* poly);
void rightShiftGFE(GFElement* poly);
void elimLeadCoeff(GFElement* poly1, GFElement* poly2, GF_TYPE p);
GFElement modGFE (GFElement* poly1, GFElement* poly2, GF_TYPE p);
GFElement multiplyGFE(GFElement* poly1, GFElement* poly2, GFElement* irrpoly, GF_TYPE p);
void initGF(GF_TYPE p, GF_TYPE n, GF* galoisField);
void printGF(GF* galoisField);

#endif //GALOISFIELD_H