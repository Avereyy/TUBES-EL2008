#include "diagnosislib.h"
#include <stdio.h>

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

void menuRiwayatDiagnosis() {
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

    return 0;
}
