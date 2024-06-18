#ifndef MENUDATALIB_H
#define MENUDATALIB_H

#include "mainbaru.h"

void trimWhitespace(char* str);
void bacaData(Pasien pasien[], int *jumlah_pasien);
void hapusNewline(char *str);
void tambahPasien(Pasien pasien[], int *jumlah_pasien);
void hapusPasien(Pasien pasien[], int *jumlah_pasien);
void cariPasien(const Pasien pasien[], int jumlah_pasien);
void ubahPasien(Pasien pasien[], int jumlah_pasien);
void menuData(Pasien pasien[], int *jumlah_pasien);

#endif // DATALIB_H
