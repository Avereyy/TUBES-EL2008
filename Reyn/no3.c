#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void trimWhitespace(char* str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';
}

void bacaData(Pasien pasien[], int *jumlah_pasien) {
    FILE *file = fopen("Data.csv", "r");
    if (file == NULL) {
        printf("File tidak dapat ditemukan.\n");
        exit(EXIT_FAILURE);
    }
    char line[200]; 
    *jumlah_pasien = -1;  
    while (fgets(line, sizeof(line), file)) {
        if (*jumlah_pasien == -1) {
            *jumlah_pasien = 0;  
            continue;
        }

        char *token = strtok(line, ",");
        int column = 0;

        while (token) {
            switch (column) {
                case 0:
                    pasien[*jumlah_pasien].no = atoi(token);
                    break;
                case 1:
                    strcpy(pasien[*jumlah_pasien].nama, token);
                    break;
                case 2:
                    strcpy(pasien[*jumlah_pasien].alamat, token);
                    break;
                case 3:
                    strcpy(pasien[*jumlah_pasien].kota, token);
                    break;
                case 4:
                    strcpy(pasien[*jumlah_pasien].tempat_lahir, token);
                    break;
                case 5:
                    strcpy(pasien[*jumlah_pasien].tanggal_lahir, token);
                    break;
                case 6:
                    pasien[*jumlah_pasien].umur = atoi(token);
                    break;
                case 7:
                    pasien[*jumlah_pasien].no_bpjs = atoll(token);
                    break;
                case 8:
                    strcpy(pasien[*jumlah_pasien].id_pasien, token);
                    trimWhitespace(pasien[*jumlah_pasien].id_pasien);
                    break;
            }
            token = strtok(NULL, ",");
            column++;
        }


        (*jumlah_pasien)++;
    }

    fclose(file);
}

void cariInfo(Pasien pasien[], int jumlah_pasien)
{
    char id_pasien[MAX_STRING];
    printf("Masukkan ID Pasien yang dicari: ");
    getchar(); 
    fgets(id_pasien, MAX_STRING, stdin);
    id_pasien[strcspn(id_pasien, "\n")] = 0;

    int found = 0;
    int i;

    for (i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].id_pasien, id_pasien) == 0) {
            printf("Data Pasien:\n");
            printf("Nama: %s\n", pasien[i].nama);
            printf("Alamat: %s\n", pasien[i].alamat);
            printf("Kota: %s\n", pasien[i].kota);
            printf("Tempat Lahir: %s\n", pasien[i].tempat_lahir);
            printf("Tanggal Lahir: %s\n", pasien[i].tanggal_lahir);
            printf("Umur: %d\n", pasien[i].umur);
            printf("Nomor BPJS: %lld\n", pasien[i].no_bpjs);
            printf("ID Pasien: %s\n", pasien[i].id_pasien);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Data pasien dengan ID %s tidak ditemukan.\n", id_pasien);
    }

    found = 0;
    int j = 0;
    for (int i = 0; i < record_count; ++i) {
        if (strcmp(records[i].id_pasien, id_pasien) == 0) {
            if (j == 0) {
                printf("\nRiwayat Medis:\n");
            }
            printf("\nke-%d\n", j + 1);
            printf("No: %d\n", records[i].no);
            printf("Tanggal: %s\n", records[i].tanggal);
            printf("ID Pasien: %s\n", records[i].id_pasien);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Tindakan: %s\n", records[i].tindakan);
            printf("Kontrol: %s\n", records[i].kontrol);
            printf("Biaya (Rp): %s\n", records[i].biaya);
            found = 1;
            j++;
        }
    }

    if (!found) {
        printf("Riwayat medis untuk ID pasien %s tidak ditemukan.\n", id_pasien);
    }
}

void tampilkanMenu()
{
    printf("1. Cari Info\n");
    printf("6. Keluar\n");
    printf("Pilih menu: ");
}

int main()
{
    Pasien pasien[100];
    int jumlah_pasien = 0;
    
    bacaData(pasien, &jumlah_pasien);
    bacaRiwayat("Riwayat.csv");

    int pilihan;
    do
    {
        tampilkanMenu();
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
            cariInfo(pasien, jumlah_pasien);
            break;
        case 6:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}
