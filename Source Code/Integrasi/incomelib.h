#ifndef INCOMELIB_H
#define INCOMELIB_H

#include "main.h"

int parseMonth(const char *monthStr);
void parseTanggal(char *tanggalStr, int *day, int *month, int *year);
void calculateIncome();
void menuIncome();

#endif // INCOMELIB_H
