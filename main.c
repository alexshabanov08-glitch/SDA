#include <stdio.h>
#include "data.h"

int main(void) {
    Request requests[MAX_REQUESTS];
    int size  = 0;
    int choice;

    loadFromFile(requests, &size);

    do {
        printf("\n1. Добавить\n2. Показать\n0. Выход\nВыбор: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: addRequest(requests, &size);   break;
            case 2: printRequests(requests, size); break;
            case 0: break;
            default: printf("Неверный выбор.\n");
        }
    } while (choice != 0);

    saveToFile(requests, size);
    return 0;
}
