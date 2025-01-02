#ifndef CRYPTO_H
#define CRYPTO_H

#include "codes.h"

size_t findInverse(GF* galoisField, size_t number);
void encryptAffine(Dict* dict, unsigned char* symbol, GF* galoisField, size_t alphaNum, size_t bettaNum);
void decryptAffine(Dict* dict, unsigned char* symbol, GF* galoisField, size_t alphaNum, size_t bettaNum);
void encryptString(Dict* dict, GF* galoisField, const char* input, char* output, size_t alphaNum, size_t bettaNum);
void decryptString(Dict* dict, GF* galoisField, const char* input, char* output, size_t alphaNum, size_t bettaNum);

#endif // CRYPTO_H