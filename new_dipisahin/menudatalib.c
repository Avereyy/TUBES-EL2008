#include "menudatalib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void hapusNewline(char *str) {
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void tambahPasien(Pasien pasien[], int *jumlah_pasien) {
    Pasien new_pasien;
    int nomor_valid = 0;

    while (!nomor_valid) {
        printf("Masukkan Nomor: ");
        scanf("%d", &new_pasien.no);
        getchar();

        nomor_valid = 1;
        for (int i = 0; i < *jumlah_pasien; i++) {
            if (pasien[i].no == new_pasien.no) {
                printf("Nomor pasien sudah ada, masukkan nomor yang lain.\n");
                nomor_valid = 0;
                break;
            }
        }
    }
    printf("Masukkan Nama Lengkap: ");
    fgets(new_pasien.nama, sizeof(new_pasien.nama), stdin);
    hapusNewline(new_pasien.nama);

    printf("Masukkan Alamat: ");
    fgets(new_pasien.alamat, sizeof(new_pasien.alamat), stdin);
    hapusNewline(new_pasien.alamat);

    printf("Masukkan Kota: ");
    fgets(new_pasien.kota, sizeof(new_pasien.kota), stdin);
    hapusNewline(new_pasien.kota);

    printf("Masukkan Tempat Lahir: ");
    fgets(new_pasien.tempat_lahir, sizeof(new_pasien.tempat_lahir), stdin);
    hapusNewline(new_pasien.tempat_lahir);

    printf("Masukkan Tanggal Lahir: ");
    fgets(new_pasien.tanggal_lahir, sizeof(new_pasien.tanggal_lahir), stdin);
    hapusNewline(new_pasien.tanggal_lahir);

    printf("Masukkan Umur: ");
    scanf("%d", &new_pasien.umur);

    printf("Masukkan Nomor BPJS: ");
    scanf("%lld", &new_pasien.no_bpjs);
    getchar();

    printf("Masukkan ID Pasien: ");
    fgets(new_pasien.id_pasien, sizeof(new_pasien.id_pasien), stdin);
    hapusNewline(new_pasien.id_pasien);

    pasien[*jumlah_pasien] = new_pasien;
    (*jumlah_pasien)++;

    FILE *file = fopen("Data.csv", "a");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%lld,%s\n",
            new_pasien.no,
            new_pasien.nama,
            new_pasien.alamat,
            new_pasien.kota,
            new_pasien.tempat_lahir,
            new_pasien.tanggal_lahir,
            new_pasien.umur,
            new_pasien.no_bpjs,
            new_pasien.id_pasien);

    fclose(file);

    printf("Pasien berhasil ditambahkan.\n");
}

void hapusPasien(Pasien pasien[], int *jumlah_pasien) {
    char nama[100];
    printf("Masukkan Nama Pasien yang akan dihapus: ");
    getchar();
    fgets(nama, sizeof(nama), stdin);

    hapusNewline(nama);

    int i;
    int jumlah_di_hapus = 0;
    FILE *file = fopen("Data.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file == NULL || temp == NULL) {
        printf("File tidak dapat dibuka.\n");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*[^,],%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*lld,%[^,]", pasien[*jumlah_pasien].nama, pasien[*jumlah_pasien].id_pasien);
        if (strcmp(pasien[*jumlah_pasien].nama, nama) != 0) {
            fprintf(temp, "%s", line);
        } else {
            jumlah_di_hapus++;
        }
    }
    fclose(file);
    fclose(temp);
    remove("Data.csv");
    rename("temp.csv", "Data.csv");

    if (jumlah_di_hapus > 0) {
        printf("%d pasien dengan nama '%s' berhasil dihapus.\n", jumlah_di_hapus, nama);
    } else {
        printf("Tidak ada pasien dengan nama '%s' ditemukan.\n", nama);
    }
}

void cariPasien(const Pasien pasien[], int jumlah_pasien) {
    char nama[100];
    printf("Masukkan ID Pasien yang akan dicari: ");
    getchar();
    fgets(nama, sizeof(nama), stdin);

    hapusNewline(nama);

    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].nama, nama) == 0) {
            printf("Data Pasien:\n");
            printf("Nama: %s\n", pasien[i].nama);
            printf("Alamat: %s\n", pasien[i].alamat);
            printf("Kota: %s\n", pasien[i].kota);
            printf("Tempat Lahir: %s\n", pasien[i].tempat_lahir);
            printf("Tanggal Lahir: %s\n", pasien[i].tanggal_lahir);
            printf("Umur: %d\n", pasien[i].umur);
            printf("Nomor BPJS: %lld\n", pasien[i].no_bpjs);
            printf("ID Pasien: %s\n", pasien[i].id_pasien);
            return;
        }
    }
    printf("ID pasien tidak ditemukan.\n");
}

void ubahPasien(Pasien pasien[], int jumlah_pasien) {
    char nama[50], alamat[50], kota[20], tempat_lahir[20], tanggal_lahir[30], id_pasien[20];
    int umur;
    long long no_bpjs;

    printf("Masukkan nama pasien yang ingin diubah: ");
    getchar();
    fgets(nama, sizeof(nama), stdin);

    hapusNewline(nama);

    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].nama, nama) == 0) {
            printf("Masukkan data baru untuk pasien %s:\n", nama);

            printf("Alamat: ");
            fgets(alamat, sizeof(alamat), stdin);
            hapusNewline(alamat);

            printf("Kota: ");
            fgets(kota, sizeof(kota), stdin);
            hapusNewline(kota);

            printf("Tempat Lahir: ");
            fgets(tempat_lahir, sizeof(tempat_lahir), stdin);
            hapusNewline(tempat_lahir);

            printf("Tanggal Lahir: ");
            fgets(tanggal_lahir, sizeof(tanggal_lahir), stdin);
            hapusNewline(tanggal_lahir);

            printf("Umur: ");
            scanf("%d", &umur);

            printf("No. BPJS: ");
            scanf("%lld", &no_bpjs);

            printf("ID Pasien: ");
            getchar();
            fgets(id_pasien, sizeof(id_pasien), stdin);

            strcpy(pasien[i].alamat, alamat);
            strcpy(pasien[i].kota, kota);
            strcpy(pasien[i].tempat_lahir, tempat_lahir);
            strcpy(pasien[i].tanggal_lahir, tanggal_lahir);
            pasien[i].umur = umur;
            pasien[i].no_bpjs = no_bpjs;
            strcpy(pasien[i].id_pasien, id_pasien);

            FILE *file = fopen("Data.csv", "w");
            if (file == NULL) {
                printf("File tidak dapat dibuka.\n");
                exit(EXIT_FAILURE);
            }
            fprintf(file, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien\n");
            for (int j = 0; j < jumlah_pasien; j++) {
                if (pasien[j].no != 0){
                    fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%lld,%s",
                        pasien[j].no,
                        pasien[j].nama,
                        pasien[j].alamat,
                        pasien[j].kota,
                        pasien[j].tempat_lahir,
                        pasien[j].tanggal_lahir,
                        pasien[j].umur,
                        pasien[j].no_bpjs,
                        pasien[j].id_pasien);
                }
            }
            fclose(file);

            printf("Data pasien %s telah diubah.\n", nama);
            return;
        }
    }
    printf("Pasien dengan nama %s tidak ditemukan.\n", nama);
}

void menuData(Pasien pasien[], int *jumlah_pasien) {
    int pilihan;
    do {
        printf("\nAkses Data Pasien\n");
        printf("1. Tambah Pasien\n");
        printf("2. Hapus Pasien\n");
        printf("3. Cari Pasien\n");
        printf("4. Ubah Data Pasien\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahPasien(pasien, jumlah_pasien);
                break;
            case 2:
                hapusPasien(pasien, jumlah_pasien);
                break;
            case 3:
                cariPasien(pasien, *jumlah_pasien);
                break;
            case 4:
                ubahPasien(pasien, *jumlah_pasien);
                break;
            case 5:
                printf("Kembali ke Menu Utama..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 5);
}
