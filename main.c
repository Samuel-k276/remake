#include <stdio.h>
#include <stdlib.h>


#include "main.h"

int main() {
    ListNode headNode = NULL;
    HashMap carMap = createCarHashMap();
    Time time = time0();

    char c = getchar();
    while (c != 'q') {
        switch(c) {
            case 'p':
                if (getchar() == '\n')
                    commandP0(headNode);
                else {
                    inputToCommandP1(&headNode);
                }
                break;
            case 'e':
                inputToCommandEntryOrExit(&headNode, &carMap, &time, ENTRY);
                break;
            case 's':
                inputToCommandEntryOrExit(&headNode, &carMap, &time, EXIT);
                break;
            case 'v':
                inputToCommandV(carMap);
                break;
            case 'f':
                inputToCommandF(headNode, time.date);
                break;
            case 'r':
                inputToCommandR(&headNode, &carMap);
                break;
            default:
                break;
        }

        c = getchar();
    }

    freeAll(headNode, carMap);
    return 0;
}

void freeAll(ListNode headNode, HashMap carMap) {
    if (carMap != NULL) freeCarHashMap(carMap);
    if (headNode != NULL) freeList(headNode);
}

void inputToCommandP1(ListNode *headNode) {
    char *name = readName();
    
    int capacity;
    PricesType x, y, z;
    scanf("%d %f %f %f", &capacity, &x, &y, &z);
    commandP1(headNode, name, capacity, x, y, z);
}

void inputToCommandEntryOrExit(ListNode *headNode, HashMap *carMap,
    Time *time, short type) {

    getchar();
    char *name = readName();
    getchar();
    char license[LICENSESIZE];
    int day, month, year, hours, minutes;
    scanf("%c%c-%c%c-%c%c %d-%d-%d %d:%d", &license[0], &license[1],
                 &license[2], &license[3], &license[4], &license[5],
                 &day, &month, &year, &hours, &minutes);
    license[6] = '\0';
    Time new = newTime(day, month, year, hours, minutes);
    if (type == ENTRY) commandE(headNode, carMap, time, name, license, new);
    if (type == EXIT) commandS(headNode, carMap, time, name, license, new);
}

void inputToCommandV(HashMap carMap) {
    getchar();
    char license[LICENSESIZE];
    scanf("%c%c-%c%c-%c%c", &license[0], &license[1], &license[2], 
                            &license[3], &license[4], &license[5]);
    license[6] = '\0';
    commandV(carMap, license);
}

void inputToCommandF(ListNode headNode, Date currentDate) {
    getchar();
    char *name = readName();
    if (getchar() == '\n') {
        commandF0(headNode, name);
    } else {
        int day, month, year;
        scanf("%d-%d-%d", &day, &month, &year);
        Date date = newDate(day, month, year);
        commandF1(headNode, name, date, currentDate);
    }
}

void inputToCommandR(ListNode *headNode, HashMap *carMap) {
    getchar();
    char *name = readName();
    commandR(headNode, name, carMap);
    free(name);
}

char* readName() {
    char c = getchar(); 
    char end1 = ' ';
    char end2 = '\n';
    char *name = (char *)malloc(sizeof(char));;
    int i;
    if (c == '"') {
        end1 = '"';
        end2 = '"';
        c = getchar();
    }

    for (i = 0; c != end1 && c != end2; i++) {
        name[i] = c;
        c = getchar();
        name = (char *)realloc(name, (i+2)* sizeof(char));
    }
    if (end1 == '"') c = getchar();
    if (c == '\n' || c == ' ') ungetc(c, stdin);
    name[i] = '\0';
    return name;
}
