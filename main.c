#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codes.h"
#include "crypto.h"
#include "scenarios.h"

void printMenu() {
    printf("\033[32m=== Menu ===\033[0m\n");
    printf("1. Crypto (Encrypt/Decrypt)\n");
    printf("2. Explore Galois Field\n");
    printf("3. Add Elements in Galois Field\n");
    printf("4. Multiply Elements in Galois Field\n");
    printf("5. Exit\n");
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "crypto") == 0) {
            cryptoScenario();
        } else if (strcmp(argv[1], "explore") == 0) {
            if (argc < 4) {
                printf("\033[31mError: Missing arguments. Usage: %s explore <p> <n>\033[0m\n", argv[0]);
                return 1;
            }
            GF_TYPE p = atoi(argv[2]);
            GF_TYPE n = atoi(argv[3]);
            exploreScenario(p, n);
        } else if (strcmp(argv[1], "add") == 0) {
            if (argc < 4) {
                printf("\033[31mError: Missing arguments. Usage: %s add <p> <n>\033[0m\n", argv[0]);
                return 1;
            }
            GF_TYPE p = atoi(argv[2]);
            GF_TYPE n = atoi(argv[3]);
            addScenario(p, n);
        } else if (strcmp(argv[1], "multiply") == 0) {
            if (argc < 4) {
                printf("\033[31mError: Missing arguments. Usage: %s multiply <p> <n>\033[0m\n", argv[0]);
                return 1;
            }
            GF_TYPE p = atoi(argv[2]);
            GF_TYPE n = atoi(argv[3]);
            multiplyScenario(p, n);
        } else {
            printf("\033[31mError: Invalid command. Use 'crypto', 'explore', 'add', or 'multiply'.\033[0m\n");
        }
        return 0;
    }

    int choice;
    while (1) {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                cryptoScenario();
                break;
            case 2: {
                GF_TYPE p, n;
                printf("Enter p: ");
                scanf("%hhu", &p);
                printf("Enter n: ");
                scanf("%hhu", &n);
                exploreScenario(p, n);
                break;
            }
            case 3: {
                GF_TYPE p, n;
                printf("Enter p: ");
                scanf("%hhu", &p);
                printf("Enter n: ");
                scanf("%hhu", &n);
                addScenario(p, n);
                break;
            }
            case 4: {
                GF_TYPE p, n;
                printf("Enter p: ");
                scanf("%hhu", &p);
                printf("Enter n: ");
                scanf("%hhu", &n);
                multiplyScenario(p, n);
                break;
            }
            case 5:
                printf("\033[32mExiting...\033[0m\n");
                return 0;
            default:
                printf("\033[31mError: Invalid choice.\033[0m\n");
        }
    }

    return 0;
}