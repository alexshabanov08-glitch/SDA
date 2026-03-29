#include <stdio.h>
#include <string.h>
#include "data.h"

/* Удаляет \n в конце строки */
static void clean_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

/* Читает строку в buf размером n, очищая буфер ДО чтения */
static void read_line(const char *prompt, char *buf, int n) {
    printf("%s", prompt);
    fflush(stdout);
   
    int c;
    
    if (fgets(buf, n, stdin)) {
        clean_newline(buf);
        
        if ((int)strlen(buf) == n - 1 && buf[n - 2] != '\n') {
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        buf[0] = '\0';
    }
}

/* Очищает буфер после scanf */
static void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addRequest(Request arr[], int *size) {
    if (*size >= MAX_REQUESTS) {
        printf("Ошибка: список переполнен!\n");
        return;
    }

    printf("Введите ID: ");
    if (scanf("%d", &arr[*size].id) != 1) {
        printf("Ошибка ввода ID!\n");
        clear_buffer();
        return;
    }
    clear_buffer(); 

    read_line("Описание проблемы: ",          arr[*size].description, 100);
    read_line("Статус (в обработке/завершено): ", arr[*size].status,      50);
    read_line("Дата подачи (ДД.ММ.ГГГГ): ",   arr[*size].date,        20);

    (*size)++;
    printf("--- Заявка успешно добавлена ---\n");
}

void printRequests(Request arr[], int size) {
    if (size == 0) {
        printf("\nЗаявок пока нет.\n");
        return;
    }
    printf("\n%-5s | %-25s | %-20s | %-12s\n",
           "ID", "Описание", "Статус", "Дата");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-5d | %-25s | %-20s | %-12s\n",
               arr[i].id, arr[i].description, arr[i].status, arr[i].date);
    }
}

void saveToFile(Request arr[], int size) {
    FILE *f = fopen("requests.txt", "w");
    if (!f) { perror("saveToFile"); return; }
    fprintf(f, "%d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(f, "%d|%s|%s|%s\n",
                arr[i].id, arr[i].description, arr[i].status, arr[i].date);
    }
    fclose(f);
    printf("Данные сохранены.\n");
}

void loadFromFile(Request arr[], int *size) {
    FILE *f = fopen("requests.txt", "r");
    if (!f) { *size = 0; return; }

    if (fscanf(f, "%d\n", size) != 1) { *size = 0; fclose(f); return; }

    for (int i = 0; i < *size; i++) {
        /* %[^|] — всё до символа '|'; %[^\n] — всё до конца строки */
        if (fscanf(f, "%d|%99[^|]|%49[^|]|%19[^\n]\n",
                   &arr[i].id,
                   arr[i].description,
                   arr[i].status,
                   arr[i].date) != 4) {
       
            *size = i;
            break;
        }
    }
    fclose(f);
    printf("Загружено заявок: %d\n", *size);
}
