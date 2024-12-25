#include "galoisField.h"

void initGFE(GFElement* poly, GF_TYPE length, GF_TYPE coeffs[MAX_N]) {
    poly->length = length;
    for (int i = 0; i < MAX_N; i++) {
        poly->coeffs[i] = 0;
    }

    for (int j = 0; j < poly->length; j++) {
        poly->coeffs[j] = coeffs[j];
    }
}

void printGFE(GFElement* poly, GF_TYPE n) {
    GF_TYPE l = (n > poly->length)? n : poly->length;
    for (size_t i = l - 1; i > 0; i--) {
        printf("%d ", poly->coeffs[i]);
    }
    printf("%d\n", poly->coeffs[0]); 
}

void updateLength(GFElement* poly) {
    poly->length = 1;
    for (size_t i = MAX_N - 1; i > 0; i--) {
        if (poly->coeffs[i] != 0) {
            poly->length = i + 1;
            return;
        }
    }
}

GFElement addGFE(GFElement* poly1, GFElement* poly2, GF_TYPE p) {
    GFElement result;
    GF_TYPE array[MAX_N];
    initGFE(&result, 0, array);

    for (size_t i = 0; i < MAX_N; i++) {
        result.coeffs[i] = (poly1->coeffs[i] + poly2->coeffs[i]) % p;
    }

    updateLength(&result);
    return result;
}

GFElement substractGFE(GFElement* poly1, GFElement* poly2, GF_TYPE p) {
    GFElement result;
    GF_TYPE array[MAX_N];
    initGFE(&result, 0, array);

    for (size_t i = 0; i < MAX_N; i++) {
        result.coeffs[i] = (p + poly1->coeffs[i] - poly2->coeffs[i]) % p;
    }

    updateLength(&result);
    return result;
}

void increaseGFE(GFElement* poly, GF_TYPE p) {
    size_t i = 0;
    GF_TYPE carry = 1;

    while (carry == 1 && i < MAX_N) {
        poly->coeffs[i] = (poly->coeffs[i] + carry) % p;
        carry = (poly->coeffs[i] == 0) ? 1 : 0;
        i++;
    }

    if (carry == 1) {
        printf("Error: Polynomial overflow, cannot increase further.\n");
    } else if (i > poly->length) {
        poly->length = i;
    }

    updateLength(poly);
}

void leftShiftGFE(GFElement* poly) {
    for (GF_TYPE i = poly->length; i > 0; i--) {
        poly->coeffs[i] = poly->coeffs[i - 1];
    }
    poly->coeffs[0] = 0;
    poly->length += 1;
}

void rightShiftGFE(GFElement* poly) {
    for (GF_TYPE i = 0; i < poly->length; i++) {
        poly->coeffs[i] = poly->coeffs[i + 1];
    }
    poly->coeffs[poly->length] = 0;
    poly->length -= 1;
}

void elimLeadCoeff(GFElement* poly1, GFElement* poly2, GF_TYPE p) {
    GF_TYPE index = poly1->length;
    while (poly1->coeffs[index - 1] != 0 && poly1->length == poly2->length) {
        *poly1 = substractGFE(poly1, poly2, p);
        updateLength(poly1);
    }
}

GFElement modGFE(GFElement* poly1, GFElement* poly2, GF_TYPE p) {
    GFElement remainder;
    initGFE(&remainder, poly1->length, poly1->coeffs);
    GFElement devisor;
    initGFE(&devisor, poly2->length, poly2->coeffs);

    while (remainder.length > devisor.length) {
        leftShiftGFE(&devisor);
    }

    while (devisor.length > poly2->length) {
        elimLeadCoeff(&remainder, &devisor, p);
        rightShiftGFE(&devisor);
    }
    elimLeadCoeff(&remainder, &devisor, p);
    return remainder;
}

GFElement multiplyGFE(GFElement* poly1, GFElement* poly2, GFElement* irrpoly, GF_TYPE p) {
    GFElement result;
    GF_TYPE initArr[MAX_N] = {0};  
    initGFE(&result, irrpoly->length - 1, initArr);

    for (size_t i = 0; i < poly1->length; i++) {
        for (size_t j = 0; j < poly2->length; j++) { 
            result.coeffs[i + j] = (result.coeffs[i + j] + (poly1->coeffs[i] * poly2->coeffs[j]) % p) % p;
        }
    }
    updateLength(&result);
    return modGFE(&result, irrpoly, p);
}

void initGF(GF_TYPE p, GF_TYPE n, GF* galoisField) {
    galoisField->p = p;
    galoisField->n = n;
    size_t size = 1;

    for (size_t i = 0; i < n; i++) {
        size *= p;
    }

    galoisField->size = size;
    galoisField->field = (GFElement*)malloc(galoisField->size * sizeof(GFElement));
    if (galoisField->field == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    GFElement unitPol;
    GF_TYPE initArr[MAX_N] = {0}; 
    initGFE(&unitPol, 1, initArr); 

    for (size_t i = 0; i < galoisField->size; i++) {
        initGFE(&galoisField->field[i], unitPol.length, unitPol.coeffs);
        increaseGFE(&unitPol, p);
    }
    //part for finding irreducible poly
    GF_TYPE initIrrPol[MAX_N] = {0};
    initIrrPol[n] = 1;
    initGFE(&galoisField->irreduciblePoly, n + 1, initIrrPol);
    bool flag = false;
    while(!flag){
        //printf("Before increase: ");
        //printGFE(&galoisField->irreduciblePoly);
        increaseGFE(&galoisField->irreduciblePoly, p);
        //printf("After increase: ");
        //printGFE(&galoisField->irreduciblePoly);        
        flag = true;
        for(size_t i = p; i < galoisField->size; i++){
            //printf("Element %zu: ", i);
            //printGFE(&galoisField->field[i]);
            GFElement remainder = modGFE(&galoisField->irreduciblePoly, &galoisField->field[i], p);
            //printf("Remainder: ");
            //printGFE(&remainder);
            if (remainder.coeffs[0] == 0 && remainder.length == 1){
                flag = false;
                break;
            }
        }
    }
}

void printGF(GF* galoisField) {
    printf("Irreducible Polinomial: ");
    printGFE(&galoisField->irreduciblePoly, galoisField->n);
    for (size_t i = 0; i < galoisField->size; i++) {
        printf("Element %zu: ", i);
        printGFE(&galoisField->field[i], galoisField->n);
    }
}
