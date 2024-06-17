#ifndef DIAGNOSISLIB_H
#define DIAGNOSISLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PASIEN 1000
#define MAX_DIAGNOSIS 100
#define MAX_BULAN 12
#define MAX_TAHUN 5

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

int parse_bulan(const char *bulan_str);

void parse_tanggal(const char *tanggal_str, int *tahun, int *bulan);

void sort_data_bulanan(MonthlyDiagnosisData *monthly_Data, int size);

void count_pasien_tahunan(MonthlyDiagnosisData *monthly_Data, int monthly_Data_Size, YearlyDiagnosisData *yearly_Data, int *yearly_Data_Size);

void sort_data_tahunan(YearlyDiagnosisData *yearly_Data, int size);

void menuRiwayatDiagnosis();

#endif // DIAGNOSISLIB_H
