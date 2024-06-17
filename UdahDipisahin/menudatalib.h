#ifndef MENUDATALIB_H
#define MENUDATALIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int no;
    char nama[50];
    char alamat[50];
    char kota[20];
    char tempat_lahir[20];
    char tanggal_lahir[30];
    int umur;
    long long no_bpjs;
    char id_pasien[20];
} Pasien;

void trimWhitespace(char* str);
void bacaData(Pasien pasien[], int *jumlah_pasien);
void hapusNewline(char *str);
void tambahPasien(Pasien pasien[], int *jumlah_pasien);
void hapusPasien(Pasien pasien[], int *jumlah_pasien);
void cariPasien(const Pasien pasien[], int jumlah_pasien);
void ubahPasien(Pasien pasien[], int jumlah_pasien);
void menuData(Pasien pasien[], int *jumlah_pasien);

#endif // DATALIB_H
