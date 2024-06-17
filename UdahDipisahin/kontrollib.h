#ifndef KONTROLLIB_H
#define KONTROLLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_STRING 100

typedef struct
{
    int no;
    char tanggal[MAX_STRING];
    char id_pasien[MAX_STRING];
    char diagnosis[MAX_STRING];
    char tindakan[MAX_STRING];
    char kontrol[MAX_STRING];
    char biaya[MAX_STRING];
} Riwayat;

extern Riwayat records[MAX_RECORDS];  // External declaration of global array
extern int record_count;              // External declaration of global count

void cariKontrol();
void tampilkanMenu();
void runno6();

#endif // KONTROLLIB_H
