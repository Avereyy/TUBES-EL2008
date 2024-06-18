#include "kontrollib.h"
#include "aksesriwayat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cariKontrol()
{
    char id_pasien[MAX_STRING];
    printf("Masukkan ID Pasien yang dicari: ");
    getchar(); // Consume any newline character left in the input buffer
    fgets(id_pasien, MAX_STRING, stdin);
    id_pasien[strcspn(id_pasien, "\n")] = 0; // Remove newline character

    int found = 0;
    for (int i = 0; i < record_count; ++i)
    {
        if (strcmp(records[i].id_pasien, id_pasien) == 0)
        {
            printf("\nke-%d\n", i + 1);
            printf("Tanggal Kontrol: %s\n", records[i].kontrol);
            found = 1;
        }
    }
    if (!found)
    {
        printf("tidak ditemukan!\n");
    }
}

void tampilkanMenu()
{
    printf("1. Cari Kontrol\n");
    printf("2. Keluar\n");
    printf("Pilih menu: ");
}

void runno6()
{
    baca_CSV("Riwayat.csv");

    int pilihan;
    do
    {
        tampilkanMenu();
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            cariKontrol();
            break;
        case 2:
            printf("Keluar dari Program");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 2);
}
