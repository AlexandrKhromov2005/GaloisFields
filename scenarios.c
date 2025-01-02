#include "scenarios.h"


void cryptoScenario() {
    GF galoisField;
    initGF(2, 6, &galoisField);
    Dict dictionary;
    initDict(&dictionary);

    size_t alphaNum, bettaNum;
    printf("\033[32m=== Galois Field GF(2^6) ===\033[0m\n");
    printGF(&galoisField);

    printf("Enter alpha key (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &alphaNum);
    printf("Enter betta key (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &bettaNum);

    if (alphaNum < 1 || alphaNum >= galoisField.size || bettaNum < 1 || bettaNum >= galoisField.size) {
        printf("\033[31mError: Invalid key numbers.\033[0m\n");
        return;
    }

    char input[100];
    printf("Enter your message: ");
    getchar(); // Очистка буфера
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Убираем символ новой строки

    // Динамическое выделение памяти для output
    char* output = (char*)malloc((strlen(input) + 1) * sizeof(char));
    if (output == NULL) {
        printf("\033[31mError: Memory allocation failed.\033[0m\n");
        return;
    }

    int choice;
    printf("Choose action:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        encryptString(&dictionary, &galoisField, input, output, alphaNum, bettaNum);
        printf("\033[32m=== Encrypted Message ===\033[0m\n");
    } else if (choice == 2) {
        decryptString(&dictionary, &galoisField, input, output, alphaNum, bettaNum);
        printf("\033[32m=== Decrypted Message ===\033[0m\n");
    } else {
        printf("\033[31mError: Invalid choice.\033[0m\n");
        free(output); // Освобождаем память в случае ошибки
        return;
    }
    printf("%s\n", output);

    free(output); // Освобождаем память после использования
}

void exploreScenario(GF_TYPE p, GF_TYPE n) {
    GF galoisField;
    initGF(p, n, &galoisField);

    printf("\033[32m=== Galois Field GF(%d^%d) ===\033[0m\n", p, n);
    printGF(&galoisField);

    findCycleGroup(&galoisField);
}

void addScenario(GF_TYPE p, GF_TYPE n) {
    GF galoisField;
    initGF(p, n, &galoisField);

    printf("\033[32m=== Galois Field GF(%d^%d) ===\033[0m\n", p, n);
    printGF(&galoisField);

    size_t index1, index2;
    printf("Enter the number of the first element (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &index1);
    printf("Enter the number of the second element (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &index2);

    if (index1 < 1 || index1 >= galoisField.size || index2 < 1 || index2 >= galoisField.size) {
        printf("\033[31mError: Invalid element numbers.\033[0m\n");
        return;
    }

    GFElement result = addGFE(&galoisField.field[index1], &galoisField.field[index2], p);
    printf("\033[34mResult of addition:\033[0m ");
    printGFE(&result, n);
}

void multiplyScenario(GF_TYPE p, GF_TYPE n) {
    GF galoisField;
    initGF(p, n, &galoisField);

    printf("\033[32m=== Galois Field GF(%d^%d) ===\033[0m\n", p, n);
    printGF(&galoisField);

    size_t index1, index2;
    printf("Enter the number of the first element (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &index1);
    printf("Enter the number of the second element (1 to %zu): ", galoisField.size - 1);
    scanf("%zu", &index2);

    if (index1 < 1 || index1 >= galoisField.size || index2 < 1 || index2 >= galoisField.size) {
        printf("\033[31mError: Invalid element numbers.\033[0m\n");
        return;
    }

    GFElement result = multiplyGFE(&galoisField.field[index1], &galoisField.field[index2], &galoisField.irreduciblePoly, p);
    printf("\033[34mResult of multiplication:\033[0m ");
    printGFE(&result, n);
}