#include <stdio.h>
#include "data.h"

int main() {
    Request requests[MAX_REQUESTS];
    int size = 0;
    int choice;

    loadFromFile(requests, &size);

    do {
        printf("\n1. Добавить заявку\n");
        printf("2. Показать все\n");
        printf("3. Поиск\n");
        printf("4. Редактировать\n");
        printf("5. Сохранить\n");
        printf("0. Выход\n");

        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRequest(requests, &size); break;
            case 2: printRequests(requests, size); break;
            case 3: searchById(requests, size); break;
            case 4: editRequest(requests, size); break;
            case 5: saveToFile(requests, size); break;
        }

    } while (choice != 0);

    // автосохранение перед выходом
    saveToFile(requests, size);

    return 0;
}
