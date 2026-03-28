#include <stdio.h>
#include <string.h>
#include "data.h"

void addRequest(Request arr[], int *size) {
    if (*size >= MAX_REQUESTS) {
        printf("Список заполнен\n");
        return;
    }

    Request r;

    printf("Введите ID: ");
    scanf("%d", &r.id);
    getchar();

    printf("Описание: ");
    fgets(r.description, 100, stdin);

    printf("Статус (в обработке/завершено): ");
    fgets(r.status, 20, stdin);

    printf("Дата: ");
    fgets(r.date, 20, stdin);

    arr[*size] = r;
    (*size)++;
}

void printRequests(Request arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("\nID: %d\n", arr[i].id);
        printf("Описание: %s", arr[i].description);
        printf("Статус: %s", arr[i].status);
        printf("Дата: %s", arr[i].date);
    }
}

void saveToFile(Request arr[], int size) {
    FILE *f = fopen("requests.txt", "w");
    if (!f) {
        printf("Ошибка открытия файла\n");
        return;
    }

    fprintf(f, "%d\n", size);

    for (int i = 0; i < size; i++) {
        fprintf(f, "%d|%s|%s|%s",
            arr[i].id,
            arr[i].description,
            arr[i].status,
            arr[i].date);
    }

    fclose(f);
}

void loadFromFile(Request arr[], int *size) {
    FILE *f = fopen("requests.txt", "r");
    if (!f) return;

    fscanf(f, "%d\n", size);

    for (int i = 0; i < *size; i++) {
        fscanf(f, "%d|", &arr[i].id);
        fgets(arr[i].description, 100, f);
        strtok(arr[i].description, "|");

        fgets(arr[i].status, 20, f);
        strtok(arr[i].status, "|");

        fgets(arr[i].date, 20, f);
    }

    fclose(f);
}

void searchById(Request arr[], int size) {
    int id;
    printf("Введите ID для поиска: ");
    scanf("%d", &id);

    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            printf("Найдено:\n");
            printf("%s", arr[i].description);
            return;
        }
    }
    printf("Не найдено\n");
}

void editRequest(Request arr[], int size) {
    int id;
    printf("Введите ID для редактирования: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < size; i++) {
        if (arr[i].id == id) {
            printf("Новое описание: ");
            fgets(arr[i].description, 100, stdin);
            printf("Новый статус: ");
            fgets(arr[i].status, 20, stdin);
            return;
        }
    }

    printf("Не найдено\n");
}
