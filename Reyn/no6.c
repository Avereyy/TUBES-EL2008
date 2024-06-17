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

Riwayat records[MAX_RECORDS];
int record_count = 0;

void bacaRiwayat(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    char buffer[1024];
    int row = 0;
    int column = 0;

    while (fgets(buffer, 1024, file))
    {
        if (row == 0)
        {
            row++;
            continue;
        }

        Riwayat new_record;
        char *token = strtok(buffer, ",");
        column = 0;

        while (token)
        {
            switch (column)
            {
            case 0:
                new_record.no = atoi(token);
                break;
            case 1:
                strcpy(new_record.tanggal, token);
                break;
            case 2:
                strcpy(new_record.id_pasien, token);
                break;
            case 3:
                strcpy(new_record.diagnosis, token);
                break;
            case 4:
                strcpy(new_record.tindakan, token);
                break;
            case 5:
                strcpy(new_record.kontrol, token);
                break;
            case 6:
                strcpy(new_record.biaya, token);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
            column++;
        }
        records[record_count++] = new_record;
        row++;
    }

    fclose(file);
    printf("Data dari %s berhasil dibaca.\n", filename);
}

void simpanCSV(char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    for (int i = 0; i < record_count; ++i)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s",
                records[i].no,
                records[i].tanggal,
                records[i].id_pasien,
                records[i].diagnosis,
                records[i].tindakan,
                records[i].kontrol,
                records[i].biaya);
    }

    fclose(file);
    printf("Data berhasil disimpan ke %s.\n", filename);
}

void cariKontrol()
{
    char id_pasien[MAX_STRING];
    printf("Masukkan ID Pasien yang dicari: ");
    getchar(); 
    fgets(id_pasien, MAX_STRING, stdin);
    id_pasien[strcspn(id_pasien, "\n")] = 0;

    int found = 0;
    int j = 0;
    for (int i = 0; i < record_count; ++i)
    {
        if (strcmp(records[i].id_pasien, id_pasien) == 0)
        {
            printf("\nke-%d\n", j + 1);
            printf("Tanggal Kontrol: %s", records[i].kontrol);
            found = 1;
            j =+ 1;
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

int main()
{
    bacaRiwayat("Riwayat.csv");

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

    return 0;
}
