#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void bacaCSV(Pasien pasien[], int *jumlah_pasien) {
    FILE *file = fopen("Data.csv", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        exit(EXIT_FAILURE);
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%lld,%s",
               &pasien[*jumlah_pasien].no,
               pasien[*jumlah_pasien].nama,
               pasien[*jumlah_pasien].alamat,
               pasien[*jumlah_pasien].kota,
               pasien[*jumlah_pasien].tempat_lahir,
               pasien[*jumlah_pasien].tanggal_lahir,
               &pasien[*jumlah_pasien].umur,
               &pasien[*jumlah_pasien].no_bpjs,
               pasien[*jumlah_pasien].id_pasien);
               
               sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*lld,%[^,]",
               pasien[*jumlah_pasien].id_pasien);
               

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

    printf("Masukkan Nomor: ");
    scanf("%d", &new_pasien.no);
    getchar(); 

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

void cariPasien(Pasien pasien[], int jumlah_pasien) {
    char nama[100];
    printf("Masukkan Nama Pasien yang akan dicari: ");
    getchar(); 
    fgets(nama, sizeof(nama), stdin);

    hapusNewline(nama);
    size_t len = strlen(nama);
    if (nama[len - 1] == '\n') {
        nama[len - 1] = '\0';
    }

    int i;
    for (i = 0; i < jumlah_pasien; i++) {
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
    printf("Nomor pasien tidak ditemukan.\n");
}


int main() {
    Pasien pasien[100];
    int jumlah_pasien = 0;
    int pilihan;

    bacaCSV(pasien, &jumlah_pasien);

    do {
        printf("\nMenu\n");
        printf("1. Tambah Pasien\n");
        printf("2. Hapus Pasien\n");
        printf("3. Cari Pasien\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahPasien(pasien, &jumlah_pasien);
                break;
            case 2:
                hapusPasien(pasien, &jumlah_pasien);
                break;
            case 3:
                cariPasien(pasien, jumlah_pasien);
                break;
 
            case 4:
                printf("Keluar..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);

    return 0;
}

