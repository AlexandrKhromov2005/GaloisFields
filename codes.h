#ifndef CODES_H
#define CODES_H

#include "galoisField.h"
#include <stdlib.h>
#include <string.h>

#define DICT_SIZE 64

// Макрос для инициализации массива basic_chars
#define BASIC_CHARS_INIT \
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', \
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', \
    '@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', \
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_'

extern const unsigned char basic_chars[DICT_SIZE];

typedef struct {
    unsigned char symbols[DICT_SIZE];
    GFElement GFE[DICT_SIZE];
} Dict;

void initDict(Dict* dictionary);
unsigned char getSymbolFromGFE(const Dict* dictionary, GFElement* gfe);
GFElement* getGFEFromSymbol(Dict* dictionary, unsigned char symbol);

#endif // CODES_H