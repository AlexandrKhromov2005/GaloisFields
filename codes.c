#include "codes.h"

const unsigned char basic_chars[DICT_SIZE] = { BASIC_CHARS_INIT };

void initDict(Dict* dictionary) {
    memcpy(dictionary->symbols, basic_chars, DICT_SIZE * sizeof(unsigned char));

    GF galoisField;
    initGF(2, 6, &galoisField);

    for (size_t i = 0; i < DICT_SIZE; i++) {
        dictionary->GFE[i] = galoisField.field[i];
    }
}

unsigned char getSymbolFromGFE(const Dict* dictionary, GFElement* gfe) {
    for (size_t i = 0; i < DICT_SIZE; i++) {
        if (memcmp(&dictionary->GFE[i], gfe, sizeof(GFElement)) == 0) {
            return dictionary->symbols[i];
        }
    }
    return '\0'; 
}

GFElement* getGFEFromSymbol(Dict* dictionary, unsigned char symbol) {
    for (size_t i = 0; i < DICT_SIZE; i++) {
        if (dictionary->symbols[i] == symbol) {
            return &dictionary->GFE[i];
        }
    }
    return NULL;
}