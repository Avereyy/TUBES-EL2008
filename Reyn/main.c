#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PASIEN 1000
#define MAX_DIAGNOSIS 100
#define MAX_BULAN 12
#define MAX_TAHUN 5

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
    int tahun;
    int bulan;
    char diagnosis[100];
} Diagpasien;

typedef struct {
    char diagnosis[100];
    int count;
} DiagnosisCount;

typedef struct {
    int tahun;
    int bulan;
    DiagnosisCount diagnosisCounts[MAX_DIAGNOSIS];
    int diagnosisCountSize;
    int total_pasien; // Total patients for this month
} MonthlyDiagnosisData;

typedef struct {
    int tahun;
    DiagnosisCount diagnosisCounts[MAX_DIAGNOSIS];
    int diagnosisCountSize;
    int total_pasien; // Total patients for this year
} YearlyDiagnosisData;

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
        printf("5. Lihat Riwayat Diagnosis\n");
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
                menuRiwayatDiagnosis();
            case 6;
                printf("Kembali ke Menu Utama..\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}



int parse_bulan(const char *bulan_str) {
    if (strcasecmp(bulan_str, "jan") == 0 || strcasecmp(bulan_str, "januari") == 0) return 1;
    if (strcasecmp(bulan_str, "feb") == 0 || strcasecmp(bulan_str, "februari") == 0) return 2;
    if (strcasecmp(bulan_str, "mar") == 0 || strcasecmp(bulan_str, "maret") == 0) return 3;
    if (strcasecmp(bulan_str, "apr") == 0 || strcasecmp(bulan_str, "april") == 0) return 4;
    if (strcasecmp(bulan_str, "may") == 0 || strcasecmp(bulan_str, "mei") == 0) return 5;
    if (strcasecmp(bulan_str, "jun") == 0 || strcasecmp(bulan_str, "juni") == 0) return 6;
    if (strcasecmp(bulan_str, "jul") == 0 || strcasecmp(bulan_str, "juli") == 0) return 7;
    if (strcasecmp(bulan_str, "aug") == 0 || strcasecmp(bulan_str, "agustus") == 0) return 8;
    if (strcasecmp(bulan_str, "sep") == 0 || strcasecmp(bulan_str, "september") == 0) return 9;
    if (strcasecmp(bulan_str, "oct") == 0 || strcasecmp(bulan_str, "oktober") == 0) return 10;
    if (strcasecmp(bulan_str, "nov") == 0 || strcasecmp(bulan_str, "november") == 0) return 11;
    if (strcasecmp(bulan_str, "dec") == 0 || strcasecmp(bulan_str, "desember") == 0) return 12;
    return -1;
}

void parse_tanggal(const char *tanggal_str, int *tahun, int *bulan) {
    int hari;
    char bulan_str[20];
    if (sscanf(tanggal_str, "%d-%3s-%d", &hari, bulan_str, tahun) == 3 || sscanf(tanggal_str, "%d %s %d", &hari, bulan_str, tahun) == 3) {
        *bulan = parse_bulan(bulan_str);
        if (*tahun < 100) {
            *tahun += (*tahun < 50) ? 2000 : 1900;
        }
    } else {
        fprintf(stderr, "Error menguraikan tanggal: %s\n", tanggal_str);
    }
}

int cari_index_diagnosis(DiagnosisCount *diagnosisCounts, int size, const char *diagnosis) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(diagnosisCounts[i].diagnosis, diagnosis) == 0) {
            return i;
        }
    }
    return -1;
}

void sort_data_bulanan(MonthlyDiagnosisData *monthly_Data, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (monthly_Data[j].total_pasien < monthly_Data[j + 1].total_pasien) {
                MonthlyDiagnosisData temp = monthly_Data[j];
                monthly_Data[j] = monthly_Data[j + 1];
                monthly_Data[j + 1] = temp;
            }
        }
    }
}

void count_pasien_tahunan(MonthlyDiagnosisData *monthly_Data, int monthly_Data_Size, YearlyDiagnosisData *yearly_Data, int *yearly_Data_Size) {
    for (int i = 0; i < monthly_Data_Size; ++i) {
        int tahun = monthly_Data[i].tahun;
        int total_pasien = monthly_Data[i].total_pasien;

        int l;
        for (l = 0; l < *yearly_Data_Size; ++l) {
            if (yearly_Data[l].tahun == tahun) {
                break;
            }
        }

        if (l == *yearly_Data_Size) {
            if (*yearly_Data_Size >= MAX_TAHUN) {
                printf("Melewati Batas Tahun.\n");
                return;
            }
            yearly_Data[l].tahun = tahun;
            yearly_Data[l].diagnosisCountSize = 0;
            yearly_Data[l].total_pasien = 0;
            (*yearly_Data_Size)++;
        }

        yearly_Data[l].total_pasien += total_pasien;

        for (int j = 0; j < monthly_Data[i].diagnosisCountSize; ++j) {
            const char *diagnosis = monthly_Data[i].diagnosisCounts[j].diagnosis;
            int count = monthly_Data[i].diagnosisCounts[j].count;

            int index_diagnosis = cari_index_diagnosis(yearly_Data[l].diagnosisCounts, yearly_Data[l].diagnosisCountSize, diagnosis);

            if (index_diagnosis == -1) {
                if (yearly_Data[l].diagnosisCountSize >= MAX_DIAGNOSIS) {
                    printf("Melewati Batas Maksimum.\n");
                    return;
                }
                strcpy(yearly_Data[l].diagnosisCounts[yearly_Data[l].diagnosisCountSize].diagnosis, diagnosis);
                yearly_Data[l].diagnosisCounts[yearly_Data[l].diagnosisCountSize].count = count;
                yearly_Data[l].diagnosisCountSize++;
            } else {
                yearly_Data[l].diagnosisCounts[index_diagnosis].count += count;
            }
        }
    }
}

void sort_data_tahunan(YearlyDiagnosisData *yearly_Data, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (yearly_Data[j].total_pasien < yearly_Data[j + 1].total_pasien) {
                YearlyDiagnosisData temp = yearly_Data[j];
                yearly_Data[j] = yearly_Data[j + 1];
                yearly_Data[j + 1] = temp;
            }
        }
    }
}

void menuRiwayatDiagnosis(){
    FILE *file = fopen("Riwayat.csv", "r");
    if (!file) {
        perror("Tidak dapat membuka file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Diagpasien pasiens[MAX_PASIEN];
    int pasien_count = 0;

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *token;
        char tanggal_str[30];
        char diagnosis[100];
        int tahun, bulan;

        token = strtok(line, ",");
        token = strtok(NULL, ",");
        strcpy(tanggal_str, token);

        for (int i = 0; i < 1; ++i) {
            token = strtok(NULL, ",");
        }
        token = strtok(NULL, ",");
        strcpy(diagnosis, token);
                diagnosis[strcspn(diagnosis, "\n")] = '\0'; //

        parse_tanggal(tanggal_str, &tahun, &bulan);


        pasiens[pasien_count].tahun = tahun;
        pasiens[pasien_count].bulan = bulan;
        strcpy(pasiens[pasien_count].diagnosis, diagnosis);
        pasien_count++;
    }

    fclose(file);

    MonthlyDiagnosisData monthly_Data[MAX_TAHUN * MAX_BULAN] = {0};
    int monthly_Data_Size = 0;

    for (int i = 0; i < pasien_count; ++i) {
        int tahun = pasiens[i].tahun;
        int bulan = pasiens[i].bulan;
        char *diagnosis = pasiens[i].diagnosis;

        int j;
        for (j = 0; j < monthly_Data_Size; ++j) {
            if (monthly_Data[j].tahun == tahun && monthly_Data[j].bulan == bulan) {
                break;
            }
        }

        if (j == monthly_Data_Size) {
            monthly_Data[j].tahun = tahun;
            monthly_Data[j].bulan = bulan;
            monthly_Data[j].diagnosisCountSize = 0;
            monthly_Data[j].total_pasien = 0;
            monthly_Data_Size++;
        }

        int index_diagnosis = cari_index_diagnosis(monthly_Data[j].diagnosisCounts, monthly_Data[j].diagnosisCountSize, diagnosis);

        if (index_diagnosis == -1) {
            strcpy(monthly_Data[j].diagnosisCounts[monthly_Data[j].diagnosisCountSize].diagnosis, diagnosis);
            monthly_Data[j].diagnosisCounts[monthly_Data[j].diagnosisCountSize].count = 1;
            monthly_Data[j].diagnosisCountSize++;
        } else {
            monthly_Data[j].diagnosisCounts[index_diagnosis].count++;
        }

        monthly_Data[j].total_pasien++;
    }

    sort_data_bulanan(monthly_Data, monthly_Data_Size);

    YearlyDiagnosisData yearly_Data[MAX_TAHUN] = {0};
    int yearly_Data_Size = 0;

    count_pasien_tahunan(monthly_Data, monthly_Data_Size, yearly_Data, &yearly_Data_Size);

    sort_data_tahunan(yearly_Data, yearly_Data_Size);

    printf("Data Diagnosis Per Bulan:\n");
    for (int i = 0; i < monthly_Data_Size; ++i) {
        printf("Tahun: %d, Bulan: %02d, Total Pasien: %d\n", monthly_Data[i].tahun, monthly_Data[i].bulan, monthly_Data[i].total_pasien);
        for (int j = 0; j < monthly_Data[i].diagnosisCountSize; ++j) {
            printf("  Diagnosis: %s, Jumlah: %d\n", monthly_Data[i].diagnosisCounts[j].diagnosis, monthly_Data[i].diagnosisCounts[j].count);
        }
    }

    printf("\nData Diagnosis Per Tahun:\n");
    for (int i = 0; i < yearly_Data_Size; ++i) {
        printf("Tahun: %d, Total Pasien: %d\n", yearly_Data[i].tahun, yearly_Data[i].total_pasien);
        for (int j = 0; j < yearly_Data[i].diagnosisCountSize; ++j) {
            printf("  Diagnosis: %s, Jumlah: %d\n", yearly_Data[i].diagnosisCounts[j].diagnosis, yearly_Data[i].diagnosisCounts[j].count);
        }
    }
}

void menuIncome() {
    int pilihan;
    do {
        printf("\nAkses Data Rumah Sakit\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                break;
            case 2:
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
