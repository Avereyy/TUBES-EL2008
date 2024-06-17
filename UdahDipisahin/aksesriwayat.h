#ifndef AKSESRIWAYAT_H
#define AKSESRIWAYAT_H

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

extern Riwayat records[MAX_RECORDS];
extern int record_count = 0;

void bacaCSV(char *filename);
void simpanCSV(char *filename);
void tambahRiwayat();
void ubahRiwayat();
void hapusRiwayat();
void cariRiwayat();
void tampilkanMenu();
void menuRiwayat();

#endif // AKSESRIWAYAT_H
