#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aksesinformasi.h"
#include "aksesriwayat.h"
#include "diagnosislib.h"
#include "incomelib.h"
#include "kontrollib.h"
#include "main.h"
#include "menudatalib.h"

#define MAX_LINE_LENGTH 1024
#define MAX_RECORDS 1000
#define MAX_STRING 100
#define MAX_LINE_LENGTH 1024
#define MAX_PASIEN 1000
#define MAX_DIAGNOSIS 100
#define MAX_BULAN 12
#define MAX_TAHUN 5

Riwayat records[MAX_RECORDS];
int record_count = 0;

int main() {
    Pasien pasien[100];
    int jumlah_pasien = 0;
    int pilihan;

    bacaData(pasien, &jumlah_pasien);

    do {
        printf("\nMenu Utama\n");
        printf("1. Akses Data Pasien\n");
        printf("2. Akses Riwayat Pasien\n");
        printf("3. Akses Data Rumah Sakit\n");
        printf("4. Akses Informasi Pasien dan Riwayat\n");
        printf("5. Akses Data Riwayat Diagnosis\n");
        printf("6. Akses Informasi Pasien Perlu kontrol\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                menuData(pasien, &jumlah_pasien);
                break;
            case 2:
                menuRiwayat();
                break;
            case 3:
                menuIncome();
                break;
            case 4:
                runno3();
                break;
            case 5:
                menuRiwayatDiagnosis();
                break;
            case 6:
                runno6();
                break;
            case 7:
                printf("Keluar..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 7);

    return 0;
}
