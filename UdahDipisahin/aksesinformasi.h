#ifndef AKSESINFORMASI_H
#define AKSESINFORMASI_H


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

extern Riwayat records[MAX_RECORDS];
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


void bacaRiwayat(char *filename);
void cariInfo(Pasien pasien[], int jumlah_pasien);
void tampilkanMenu();
void runno3();

#endif // AKSESINFORMASI_H
