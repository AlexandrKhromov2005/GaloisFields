#include "crypto.h"

size_t findInverse(GF* galoisField, size_t number) {
    for (size_t i = 1; i < galoisField->size; i++) {
        GFElement temp = multiplyGFE(&galoisField->field[number], &galoisField->field[i], &galoisField->irreduciblePoly, galoisField->p);
        if (temp.length == 1 && temp.coeffs[0] == 1) {
            return i;
        }
    }
    return 0;
}

void encryptAffine(Dict* dict, unsigned char* symbol, GF* galoisField, size_t alphaNum, size_t bettaNum) {
    GFElement* gfe = getGFEFromSymbol(dict, *symbol);
    if (gfe == NULL) {
        printf("Error: Symbol not found in dictionary.\n");
        return;
    }
    GFElement temp = multiplyGFE(gfe, &galoisField->field[alphaNum], &galoisField->irreduciblePoly, galoisField->p);
    temp = addGFE(&temp, &galoisField->field[bettaNum], galoisField->p);
    *symbol = getSymbolFromGFE(dict, &temp);
}

void decryptAffine(Dict* dict, unsigned char* symbol, GF* galoisField, size_t alphaNum, size_t bettaNum) {
    GFElement* gfe = getGFEFromSymbol(dict, *symbol);
    if (gfe == NULL) {
        printf("Error: Symbol not found in dictionary.\n");
        return;
    }
    GFElement temp = substractGFE(gfe, &galoisField->field[bettaNum], galoisField->p);
    size_t inverseAlpha = findInverse(galoisField, alphaNum);
    if (inverseAlpha == 0) {
        printf("Error: Inverse for alpha not found.\n");
        return;
    }
    temp = multiplyGFE(&temp, &galoisField->field[inverseAlpha], &galoisField->irreduciblePoly, galoisField->p);
    *symbol = getSymbolFromGFE(dict, &temp);
}

void encryptString(Dict* dict, GF* galoisField, const char* input, char* output, size_t alphaNum, size_t bettaNum) {
    for (size_t i = 0; i < strlen(input); i++) {
        unsigned char symbol = input[i];
        encryptAffine(dict, &symbol, galoisField, alphaNum, bettaNum);
        output[i] = symbol;
    }
    output[strlen(input)] = '\0';
}

void decryptString(Dict* dict, GF* galoisField, const char* input, char* output, size_t alphaNum, size_t bettaNum) {
    for (size_t i = 0; i < strlen(input); i++) {
        unsigned char symbol = input[i];
        decryptAffine(dict, &symbol, galoisField, alphaNum, bettaNum);
        output[i] = symbol;
    }
    output[strlen(input)] = '\0';
}