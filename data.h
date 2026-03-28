#ifndef DATA_H
#define DATA_H

#define MAX_REQUESTS 100

typedef struct {
    int id;
    char description[100];
    char status[20]; // "в обработке" или "завершено"
    char date[20];
} Request;

// функции
void addRequest(Request arr[], int *size);
void printRequests(Request arr[], int size);
void saveToFile(Request arr[], int size);
void loadFromFile(Request arr[], int *size);
void searchById(Request arr[], int size);
void editRequest(Request arr[], int size);

#endif
