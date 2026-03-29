#ifndef DATA_H
#define DATA_H

#define MAX_REQUESTS 100

typedef struct {
    int id;
    char description[100];
    char status[50];   /* "в обработке/завершено" = 18 симв. */
    char date[20];
} Request;

void addRequest(Request arr[], int *size);
void printRequests(Request arr[], int size);
void saveToFile(Request arr[], int size);
void loadFromFile(Request arr[], int *size);

#endif
