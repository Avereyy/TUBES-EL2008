#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data);

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void show_entry_text(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(data);
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));

    GtkWidget *label = gtk_label_new(text);

    GtkWidget *parent_window = gtk_widget_get_ancestor(entry, GTK_TYPE_WINDOW);
    if (parent_window) {
        GtkWidget *container = gtk_widget_get_parent(entry);
        gtk_box_append(GTK_BOX(container), label);
        gtk_widget_set_visible(label,TRUE);
    }
}

static void open_entry_window(GtkWidget *widget, gpointer data) {
    GtkWidget *entry_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(entry_window), "Tambah Data Pasien");
    gtk_window_set_default_size(GTK_WINDOW(entry_window), 400, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(entry_window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(vbox), entry);

    GtkWidget *show_button = gtk_button_new_with_label("Tampilkan Teks");
    g_signal_connect(show_button, "clicked", G_CALLBACK(show_entry_text), entry);
    gtk_box_append(GTK_BOX(vbox), show_button);

    gtk_window_present(GTK_WINDOW(entry_window));
}

static void return_to_main_menu(GtkWidget *widget, gpointer data) {
    activate(GTK_APPLICATION(data), NULL); 
}

static void print_button1(GtkWidget *widget, gpointer data) {
    GtkWidget *window = gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);  
    
    gtk_window_set_child(GTK_WINDOW(window), grid);

    GtkWidget *sub_button1 = gtk_button_new_with_label("Tambah Data Pasien");
    g_signal_connect(sub_button1, "clicked", G_CALLBACK(open_entry_window), NULL);
    gtk_grid_attach(GTK_GRID(grid), sub_button1, 0, 0, 1, 1);

    GtkWidget *sub_button2 = gtk_button_new_with_label("Hapus Data Pasien");
    g_signal_connect(sub_button2, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), sub_button2, 0, 1, 1, 1);

    GtkWidget *sub_button3 = gtk_button_new_with_label("Cari Data Pasien");
    g_signal_connect(sub_button3, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), sub_button3, 0, 2, 1, 1);

    GtkWidget *sub_button4 = gtk_button_new_with_label("Ubah Data Pasien");
    g_signal_connect(sub_button4, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_grid_attach(GTK_GRID(grid), sub_button4, 0, 3, 1, 1);

    GtkWidget *return_button = gtk_button_new_with_label("Kembali ke Menu Utama");
    g_signal_connect(return_button, "clicked", G_CALLBACK(return_to_main_menu), data); 
    gtk_grid_attach(GTK_GRID(grid), return_button, 0, 4, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

static void print_button2(GtkWidget *widget, gpointer data) {
    g_print("Akses Riwayat Pasien clicked\n");
}

static void print_button3(GtkWidget *widget, gpointer data) {
    g_print("Akses Informasi Pasien clicked\n");
}

static void print_button4(GtkWidget *widget, gpointer data) {
    g_print("Akses Informasi Finansial clicked\n");
}

static void print_button5(GtkWidget *widget, gpointer data) {
    g_print("Informasi Penyakit clicked\n");
}

static void print_button6(GtkWidget *widget, gpointer data) {
    g_print("Informasi Kontrol clicked\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button1, *button2, *button3, *button4, *button5, *button6;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Aplikasi Data Rumah Sakit");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400); 

    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE); 
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);   
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button1 = gtk_button_new_with_label("Akses Data Pasien");
    g_signal_connect(button1, "clicked", G_CALLBACK(print_button1), app);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);

    button2 = gtk_button_new_with_label("Akses Riwayat Pasien");
    g_signal_connect(button2, "clicked", G_CALLBACK(print_button2), NULL);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);

    button3 = gtk_button_new_with_label("Akses Informasi Pasien");
    g_signal_connect(button3, "clicked", G_CALLBACK(print_button3), NULL);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 2, 1, 1);

    button4 = gtk_button_new_with_label("Akses Informasi Finansial");
    g_signal_connect(button4, "clicked", G_CALLBACK(print_button4), NULL);
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 0, 1, 1);

    button5 = gtk_button_new_with_label("Informasi Penyakit");
    g_signal_connect(button5, "clicked", G_CALLBACK(print_button5), NULL);
    gtk_grid_attach(GTK_GRID(grid), button5, 1, 1, 1, 1);

    button6 = gtk_button_new_with_label("Informasi Kontrol");
    g_signal_connect(button6, "clicked", G_CALLBACK(print_button6), NULL);
    gtk_grid_attach(GTK_GRID(grid), button6, 1, 2, 1, 1);

    gtk_widget_set_hexpand(GTK_WIDGET(grid), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(grid), TRUE);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
