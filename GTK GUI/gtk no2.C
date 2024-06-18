#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_STRING 100

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

Riwayat records[MAX_RECORDS];
int record_count = 0;

void bacaCSV(char *filename)
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
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s\n",
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

void tambahRiwayat(GtkWidget *widget, gpointer data)
{
    if (record_count >= MAX_RECORDS)
    {
        printf("Kapasitas penuh!\n");
        return;
    }

    GtkWidget **entries = (GtkWidget **)data;
    Riwayat new_record;

    new_record.no = atoi(gtk_entry_get_text(GTK_ENTRY(entries[0])));
    strcpy(new_record.tanggal, gtk_entry_get_text(GTK_ENTRY(entries[1])));
    strcpy(new_record.id_pasien, gtk_entry_get_text(GTK_ENTRY(entries[2])));
    strcpy(new_record.diagnosis, gtk_entry_get_text(GTK_ENTRY(entries[3])));
    strcpy(new_record.tindakan, gtk_entry_get_text(GTK_ENTRY(entries[4])));
    strcpy(new_record.kontrol, gtk_entry_get_text(GTK_ENTRY(entries[5])));
    strcpy(new_record.biaya, gtk_entry_get_text(GTK_ENTRY(entries[6])));

    records[record_count++] = new_record;
    printf("Riwayat ditambahkan!\n");
    simpanCSV("Riwayat.csv");
}

void ubahRiwayat(GtkWidget *widget, gpointer data)
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

void hapusRiwayat(GtkWidget *widget, gpointer data)
{
    int no = atoi(gtk_entry_get_text(GTK_ENTRY(data)));

    for (int i = 0; i < record_count; ++i)
    {
        if (records[i].no == no)
        {
            for (int j = i; j < record_count - 1; ++j)
            {
                records[j] = records[j + 1];
            }
            --record_count;
            printf("Riwayat dihapus!\n");
            simpanCSV("Riwayat.csv");
            return;
        }
    }
    printf("Riwayat tidak ditemukan!\n");
}

void cariRiwayat(GtkWidget *widget, gpointer data)
{
    const char *id_pasien = gtk_entry_get_text(GTK_ENTRY(data));

    int found = 0;
    for (int i = 0; i < record_count; ++i)
    {
        if (strcmp(records[i].id_pasien, id_pasien) == 0)
        {
            printf("\nRiwayat ke-%d\n", i + 1);
            printf("No: %d\n", records[i].no);
            printf("Tanggal: %s\n", records[i].tanggal);
            printf("ID Pasien: %s\n", records[i].id_pasien);
            printf("Diagnosis: %s\n", records[i].diagnosis);
            printf("Tindakan: %s\n", records[i].tindakan);
            printf("Kontrol: %s\n", records[i].kontrol);
            printf("Biaya (Rp): %s\n", records[i].biaya);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Riwayat tidak ditemukan!\n");
    }
}

void tampilkanMenu(GtkWidget *widget, gpointer data)
{
    GtkWidget **entries = (GtkWidget **)data;

    GtkWidget *window;
    GtkWidget *grid;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tambah Riwayat");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *label_no = gtk_label_new("No:");
    GtkWidget *label_tanggal = gtk_label_new("Tanggal:");
    GtkWidget *label_id_pasien = gtk_label_new("ID Pasien:");
    GtkWidget *label_diagnosis = gtk_label_new("Diagnosis:");
    GtkWidget *label_tindakan = gtk_label_new("Tindakan:");
    GtkWidget *label_kontrol = gtk_label_new("Kontrol:");
    GtkWidget *label_biaya = gtk_label_new("Biaya:");

    gtk_grid_attach(GTK_GRID(grid), label_no, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_tanggal, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_id_pasien, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_diagnosis, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_tindakan, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_kontrol, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_biaya, 0, 6, 1, 1);

    entries[0] = gtk_entry_new();
    entries[1] = gtk_entry_new();
    entries[2] = gtk_entry_new();
    entries[3] = gtk_entry_new();
    entries[4] = gtk_entry_new();
    entries[5] = gtk_entry_new();
    entries[6] = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), entries[0], 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[1], 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[2], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[3], 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[4], 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[5], 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entries[6], 1, 6, 1, 1);

    GtkWidget *button_tambah = gtk_button_new_with_label("Tambah");
    g_signal_connect(button_tambah, "clicked", G_CALLBACK(tambahRiwayat), entries);
    gtk_grid_attach(GTK_GRID(grid), button_tambah, 0, 7, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_tambah, *button_ubah, *button_hapus, *button_cari, *button_keluar;
    GtkWidget *entry_no, *entry_id_pasien;

    bacaCSV("Riwayat.csv");

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Riwayat");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_tambah = gtk_button_new_with_label("Tambah Riwayat");
    g_signal_connect(button_tambah, "clicked", G_CALLBACK(tampilkanMenu), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_tambah, 0, 0, 1, 1);

    button_ubah = gtk_button_new_with_label("Ubah Riwayat");
    g_signal_connect(button_ubah, "clicked", G_CALLBACK(ubahRiwayat), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_ubah, 0, 1, 1, 1);

    button_hapus = gtk_button_new_with_label("Hapus Riwayat");
    entry_no = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_no, 1, 2, 1, 1);
    g_signal_connect(button_hapus, "clicked", G_CALLBACK(hapusRiwayat), entry_no);
    gtk_grid_attach(GTK_GRID(grid), button_hapus, 0, 2, 1, 1);

    button_cari = gtk_button_new_with_label("Cari Riwayat");
    entry_id_pasien = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_id_pasien, 1, 3, 1, 1);
    g_signal_connect(button_cari, "clicked", G_CALLBACK(cariRiwayat), entry_id_pasien);
    gtk_grid_attach(GTK_GRID(grid), button_cari, 0, 3, 1, 1);

    button_keluar = gtk_button_new_with_label("Keluar");
    g_signal_connect_swapped(button_keluar, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button_keluar, 0, 4, 2, 1);

    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return 0;
}
