#include "aksesriwayat.h"

Riwayat records[MAX_RECORDS];
int record_count = 0;

void baca_CSV(char *filename)
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
            // Skip header
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

void tambahRiwayat()
{
    Riwayat new_record;
    if (record_count >= MAX_RECORDS)
    {
        printf("Kapasitas penuh!\n");
        return;
    }

    int nomor_valid = 0;
    while (!nomor_valid) {
        printf("Masukkan Nomor: ");
        scanf("%d", &new_record.no);
        getchar(); 

        nomor_valid = 1;
        for (int i = 0; i < record_count; i++) {
            if (new_record.no == records[i].no) { 
                printf("Nomor pasien sudah ada, masukkan nomor yang lain.\n");
                nomor_valid = 0;
                break;
            }
        }
    }

    printf("Masukkan No: ");
    scanf("%d", &new_record.no);
    getchar(); 

    printf("Masukkan Tanggal: ");
    fgets(new_record.tanggal, MAX_STRING, stdin);
    new_record.tanggal[strcspn(new_record.tanggal, "\n")] = 0;

    printf("Masukkan ID Pasien: ");
    fgets(new_record.id_pasien, MAX_STRING, stdin);
    new_record.id_pasien[strcspn(new_record.id_pasien, "\n")] = 0;

    printf("Masukkan Diagnosis: ");
    fgets(new_record.diagnosis, MAX_STRING, stdin);
    new_record.diagnosis[strcspn(new_record.diagnosis, "\n")] = 0;

    printf("Masukkan Tindakan: ");
    fgets(new_record.tindakan, MAX_STRING, stdin);
    new_record.tindakan[strcspn(new_record.tindakan, "\n")] = 0;

    printf("Masukkan Kontrol: ");
    fgets(new_record.kontrol, MAX_STRING, stdin);
    new_record.kontrol[strcspn(new_record.kontrol, "\n")] = 0;

    printf("Masukkan Biaya (Rp): ");
    fgets(new_record.biaya, MAX_STRING, stdin);
    new_record.biaya[strcspn(new_record.biaya, "\n")] = 0;

    records[record_count++] = new_record;
    printf("Riwayat ditambahkan!\n");
    simpanCSV("Riwayat.csv");
}
void ubahRiwayat()
{
    int no;
    printf("Masukkan No yang akan diubah: ");
    scanf("%d", &no);
    getchar(); // untuk mengonsumsi newline

    for (int i = 0; i < record_count; ++i)
    {
        if (records[i].no == no)
        {
            printf("Masukkan Tanggal baru: ");
            fgets(records[i].tanggal, MAX_STRING, stdin);
            records[i].tanggal[strcspn(records[i].tanggal, "\n")] = 0;

            printf("Masukkan ID Pasien baru: ");
            fgets(records[i].id_pasien, MAX_STRING, stdin);
            records[i].id_pasien[strcspn(records[i].id_pasien, "\n")] = 0;

            printf("Masukkan Diagnosis baru: ");
            fgets(records[i].diagnosis, MAX_STRING, stdin);
            records[i].diagnosis[strcspn(records[i].diagnosis, "\n")] = 0;

            printf("Masukkan Tindakan baru: ");
            fgets(records[i].tindakan, MAX_STRING, stdin);
            records[i].tindakan[strcspn(records[i].tindakan, "\n")] = 0;

            printf("Masukkan Kontrol baru: ");
            fgets(records[i].kontrol, MAX_STRING, stdin);
            records[i].kontrol[strcspn(records[i].kontrol, "\n")] = 0;

            printf("Masukkan Biaya (Rp) baru: ");
            fgets(records[i].biaya, MAX_STRING, stdin);
            records[i].biaya[strcspn(records[i].biaya, "\n")] = 0;

            printf("Riwayat diubah!\n");
            simpanCSV("Riwayat.csv");
            return;
        }
    }
    printf("tidak ditemukan!\n");
}

void hapusRiwayat()
{
    int no;
    printf("Masukkan No yang akan dihapus: ");
    scanf("%d", &no);
    getchar(); // untuk mengonsumsi newline

    for (int i = 0; i < record_count; ++i)
    {
        if (records[i].no == no)
        {
            for (int j = i; j < record_count - 1; ++j)
            {
                records[j] = records[j + 1];
            }
            --record_count;
            printf("dihapus!\n");
            simpanCSV("Riwayat.csv");
            return;
        }
    }
    printf("tidak ditemukan!\n");
}

void cariRiwayat()
{
    char id_pasien[MAX_STRING];
    printf("Masukkan ID Pasien yang dicari: ");
    getchar(); // untuk mengonsumsi newline
    fgets(id_pasien, MAX_STRING, stdin);
    id_pasien[strcspn(id_pasien, "\n")] = 0;

    int found = 0;
    int j = 0;
    for (int i = 0; i < record_count; ++i)
    {
        if (strcmp(records[i].id_pasien, id_pasien) == 0)
        {
            printf("\nke-%d\n", j + 1);
            printf("No: %d\n", records[i].no);
            printf("Tanggal: %s\n", records[i].tanggal);
            printf("ID Pasien: %s\n", records[i].id_pasien);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Tindakan: %s\n", records[i].tindakan);
            printf("Kontrol: %s\n", records[i].kontrol);
            printf("Biaya (Rp): %s\n", records[i].biaya);
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
    printf("1. Tambah Riwayat\n");
    printf("2. Ubah Riwayat\n");
    printf("3. Hapus Riwayat\n");
    printf("4. Cari Riwayat\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}
void menuRiwayat() {
    baca_CSV("Riwayat.csv");
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

        switch (pilihan)
        {
        case 1:
            tambahRiwayat();
            break;
        case 2:
            ubahRiwayat();
            break;
        case 3:
            hapusRiwayat();
            break;
        case 4:
            cariRiwayat();
            break;
        case 5:
            printf("Kembali ke Menu Utama..\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 5);
}
