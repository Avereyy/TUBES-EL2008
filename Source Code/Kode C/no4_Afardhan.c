#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_RECORDS 1000

typedef struct {
    char tanggal[20];
    int biaya;
} Record;

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

int main() {
    calculateIncome();
    return 0;
}