#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_RECORDS 1000

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

typedef struct {
    char tanggal[20];
    int biaya;
} Record;

void bacaCSV(Pasien pasien[], int *jumlah_pasien) {
    FILE *file = fopen("Data.csv", "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        exit(EXIT_FAILURE);
    }
    char line[200]; 
    while (fgets(line, sizeof(line), file)) {
        if (*jumlah_pasien == 0) {
            (*jumlah_pasien)++;
            continue;
        }

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

void ubahPasien(Pasien pasien[], int jumlah_pasien) {
    char nama[50], alamat[50], kota[20], tempat_lahir[20], tanggal_lahir[30], id_pasien[20];
    int umur;
    long long no_bpjs;

    printf("Masukkan nama pasien yang ingin diubah: ");
    getchar();
    fgets(nama, sizeof(nama), stdin);  

    if (nama[strlen(nama) - 1] == '\n')
        nama[strlen(nama) - 1] = '\0';

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

void menuRiwayat() {
    int pilihan;
    do {
        printf("\nAkses Riwayat Pasien\n");
        printf("1. Tambah Riwayat\n");
        printf("2. Hapus Riwayat\n");
        printf("3. Ubah Riwayat\n");
        printf("4. Cari Riwayat\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Kembali ke Menu Utama..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}

int parseMonth(const char *monthStr) {
    char *months[] = {
        "Januari", "Jan",
        "Februari", "Feb",
        "Maret", "Mar",
        "April", "Apr",
        "Mei", "Mei",
        "Juni", "Jun",
        "Juli", "Jul",
        "Agustus", "Agu",
        "September", "Sep",
        "Oktober", "Okt",
        "November", "Nov",
        "Desember", "Des"
    };
    for (int i = 0; i < 24; i++) {
        if (strcmp(monthStr, months[i]) == 0) {
            return (i / 2) + 1;
        }
    }
    return -1; 
}

void parseTanggal(char *tanggalStr, int *day, int *month, int *year) {
    char monthStr[20];
    if (sscanf(tanggalStr, "%d %19s %d", day, monthStr, year) == 3) {
        *month = parseMonth(monthStr); 
    } else if (sscanf(tanggalStr, "%d-%3s-%2d", day, monthStr, year) == 3) {
        *month = parseMonth(monthStr); 
        *year += 2000;
    }
}

void calculateIncome() {
    FILE *file = fopen("Riwayat.csv", "r");
    if (file == NULL) {
        printf("Tidak bisa membuka file Riwayat.csv\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    Record records[MAX_RECORDS];
    int recordCount = 0;
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file) && recordCount < MAX_RECORDS) {
        sscanf(line, "%*[^,],%19[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d", records[recordCount].tanggal, &records[recordCount].biaya);
        recordCount++;
    }
    fclose(file);

    int pendapatan_bulanan[2][12] = {{0}}, pendapatan_tahunan[2] = {0};
    int yearCount[2] = {2022, 2023};

    for (int i = 0; i < recordCount; i++) {
        int day, month, year;
        parseTanggal(records[i].tanggal, &day, &month, &year);
        if (year == 2022 || year == 2023) {
            int idx = year - 2022;
            pendapatan_bulanan[idx][month - 1] += records[i].biaya;
            pendapatan_tahunan[idx] += records[i].biaya;
        }
    }

    for (int j = 0; j < 2; j++) {
        printf("Year %d Pendapatan Bulanan:\n", yearCount[j]);
        for (int i = 0; i < 12; i++) {
            printf("Month %d: %d\n", i + 1, pendapatan_bulanan[j][i]);
        }
        printf("Pendapatan Tahunan for %d: %d\n", yearCount[j], pendapatan_tahunan[j]);
        printf("Rata-rata Pendapatan Bulanan for %d: %d\n\n", yearCount[j], pendapatan_tahunan[j] / 12);
    }
}

void menuIncome() {
    int pilihan;
    do {
        printf("\nAkses Data Rumah Sakit\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data laporan pendapatan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Tambahkan implementasi untuk Tambah Data jika diperlukan
                break;
            case 2:
                calculateIncome();
                break;
            case 3:
                printf("Kembali ke Menu Utama..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}

int main() {
    Pasien pasien[100];
    int jumlah_pasien = 0;
    int pilihan;

    bacaCSV(pasien, &jumlah_pasien);

    do {
        printf("\nMenu Utama\n");
        printf("1. Akses Data Pasien\n");
        printf("2. Akses Riwayat Pasien\n");
        printf("3. Akses Data Rumah Sakit\n");
        printf("4. Keluar\n");
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
                printf("Keluar..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);

    return 0;
}