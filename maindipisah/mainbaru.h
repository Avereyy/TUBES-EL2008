#ifndef MAINBARU_H
#define MAINBARU_H


#define MAX_LINE_LENGTH 1024
#define MAX_RECORDS 1000
#define MAX_STRING 100
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
    char tanggal[20];
    int biaya;
} Record;

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

Riwayat records[MAX_RECORDS];
int record_count = 0;

#endif // MAINBARU_H
