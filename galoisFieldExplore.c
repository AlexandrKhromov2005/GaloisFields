#include "galoisFieldExplore.h"

GF_TYPE findOrder(GFElement* poly, GFElement* irrPoly, GF_TYPE p, size_t size){
    GFElement polyFactor, polyRes;
    initGFE(&polyFactor, poly->length, poly->coeffs);
    initGFE(&polyRes, poly->length, poly->coeffs);
    for(GF_TYPE result = 1; result < size; result++ ){
        if (polyRes.length == 1 && polyRes.coeffs[0] == 1){return result;}
        polyRes = multiplyGFE(&polyRes, &polyFactor, irrPoly, p);
    }
    return 255;
}

void findCycleGroup(GF* galoisField){
    printf("\033[32m\n===Cycle Groups===\n\033[0m");

    GF_TYPE* degreeArr = (GF_TYPE*)calloc(galoisField->size - 1, sizeof(GF_TYPE));
    for(size_t i = 1; i < galoisField->size; i++){
        degreeArr[i - 1] = findOrder(&galoisField->field[i],&galoisField->irreduciblePoly, galoisField->p, galoisField->size);
    }

    for(size_t i = 0; i < galoisField->size - 1; i++ ){
        printf("\033[34mpoly #%d: \033[0m", i + 1);
        printGFE(&galoisField->field[i + 1], galoisField->n);
        printf("order for  poly #%d: %d", i+1 , degreeArr[i]);
        if (degreeArr[i] == galoisField->size - 1 ){
            printf("\033[31m <--- forming!\033[0m");
        }
        printf("\n");
    }

    size_t index;

    printf("\033[32mChoose number of forming poly:\033[0m");
    scanf("%zu", &index);
    printf("\033[32m\n===Expansion in powers===\033[0m\n");
    GFElement* cyclePolys = (GFElement*)calloc(galoisField->size - 1, sizeof(GFElement));
    initGFE(&cyclePolys[0], galoisField->field[1].length, galoisField->field[1].coeffs);
    initGFE(&cyclePolys[1], galoisField->field[index].length, galoisField->field[index].coeffs);
    for(size_t i = 2; i < galoisField->size - 1; i++){
        cyclePolys[i] = multiplyGFE(&cyclePolys[i-1], &cyclePolys[1], &galoisField->irreduciblePoly, galoisField->p);
    }

    for(size_t i = 0; i < galoisField->size - 1; i++){
        printf("\033[34mx^%d = \033[0m", i);
        printGFE(&cyclePolys[i], galoisField->n);
        printf("order = %d\n", findOrder(&cyclePolys[i], &galoisField->irreduciblePoly, galoisField->p, galoisField->size));
    }
}