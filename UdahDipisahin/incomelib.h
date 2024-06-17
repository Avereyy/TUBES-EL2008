#ifndef INCOMELIB_H
#define INCOMELIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_RECORDS 1000

typedef struct {
    char tanggal[20];
    int biaya;
} Record;

int parseMonth(const char *monthStr);
void parseTanggal(char *tanggalStr, int *day, int *month, int *year);
void calculateIncome();

#endif // INCOMELIB_H
