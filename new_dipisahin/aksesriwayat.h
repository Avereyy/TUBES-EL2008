#ifndef AKSESRIWAYAT_H
#define AKSESRIWAYAT_H

#include "mainbaru.h"

//extern Riwayat records[MAX_RECORDS];
//extern int record_count = 0;

void bacaCSV(char *filename);
void simpanCSV(char *filename);
void tambahRiwayat();
void ubahRiwayat();
void hapusRiwayat();
void cariRiwayat();
void menuRiwayat();

#endif // AKSESRIWAYAT_H
