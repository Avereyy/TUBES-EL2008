#ifndef DIAGNOSISLIB_H
#define DIAGNOSISLIB_H

#include "mainbaru.h"

int parse_bulan(const char *bulan_str);

void parse_tanggal(const char *tanggal_str, int *tahun, int *bulan);

void sort_data_bulanan(MonthlyDiagnosisData *monthly_Data, int size);

void count_pasien_tahunan(MonthlyDiagnosisData *monthly_Data, int monthly_Data_Size, YearlyDiagnosisData *yearly_Data, int *yearly_Data_Size);

void sort_data_tahunan(YearlyDiagnosisData *yearly_Data, int size);

void menuRiwayatDiagnosis();

#endif // DIAGNOSISLIB_H
