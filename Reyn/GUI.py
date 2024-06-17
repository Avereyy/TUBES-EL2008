import tkinter as tk
from tkinter import messagebox, Text
from tkinter import simpledialog
import csv
from dataclasses import dataclass, field
from typing import List
from collections import defaultdict
from PIL import Image, ImageTk

@dataclass
class Patient:
    no: int
    nama: str
    alamat: str
    kota: str
    tempat_lahir: str
    tanggal_lahir: str
    umur: int
    no_bpjs: int
    id_pasien: str

patients: List[Patient] = []

@dataclass
class Riwayat:
    no: int
    tanggal: str
    id_pasien: str
    diagnosis: str
    tindakan: str
    kontrol: str
    biaya: str

daftar_riwayat: List[Riwayat] = []


def bacaData():
    try:
        with open('Data.csv', newline='') as csvfile:
            reader = csv.reader(csvfile)
            next(reader)  
            for row in reader:
                patients.append(Patient(int(row[0]), row[1], row[2], row[3], row[4], row[5], int(row[6]), int(row[7]), row[8]))
    except FileNotFoundError:
        messagebox.showerror("Error", "File tidak dapat ditemukan.")

def bacaRiwayat():
    try:
        with open('Riwayat.csv', newline='') as csvfile:
            reader = csv.reader(csvfile)
            next(reader)  
            for row in reader:
                daftar_riwayat.append(Riwayat(int(row[0]), row[1], row[2], row[3], row[4], row[5],row[6]))
    except FileNotFoundError:
        messagebox.showerror("Error", "File tidak dapat ditemukan.")

def saveData():
    with open('Data.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['No', 'Nama Lengkap', 'Alamat', 'Kota', 'Tempat Lahir', 'Tanggal Lahir', 'Umur (th)', 'No BPJS', 'ID Pasien'])
        for patient in patients:
            writer.writerow([patient.no, patient.nama, patient.alamat, patient.kota, patient.tempat_lahir, patient.tanggal_lahir, patient.umur, patient.no_bpjs, patient.id_pasien])

def saveRiwayat():
    with open('Riwayat.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['No', 'Tanggal', 'ID Pasien', 'Diagnosis', 'Tindakan', 'Kontrol', 'Biaya (Rp)'])
        for riwayat in daftar_riwayat:
            writer.writerow([riwayat.no, riwayat.tanggal, riwayat.id_pasien, riwayat.diagnosis, riwayat.tindakan, riwayat.kontrol, riwayat.biaya])

def tambahPasien():
    no = int(simpledialog.askstring("Input", "Masukkan Nomor:"))
    for patient in patients:
        if patient.no == no:
            messagebox.showerror("Error", "Nomor pasien sudah ada, masukkan nomor yang lain.")
            return
    
    def submitForm():
        nama = entry_nama.get()
        alamat = entry_alamat.get()
        kota = entry_kota.get()
        tempat_lahir = entry_tempat_lahir.get()
        tanggal_lahir = entry_tanggal_lahir.get()
        umur = int(entry_umur.get())
        no_bpjs = int(entry_no_bpjs.get())
        id_pasien = entry_id_pasien.get()

        new_patient = Patient(no, nama, alamat, kota, tempat_lahir, tanggal_lahir, umur, no_bpjs, id_pasien)
        patients.append(new_patient)
        saveData()
        messagebox.showinfo("Success", "Pasien berhasil ditambahkan.")
        form.destroy()
    
    form = tk.Toplevel()
    form.title("Formulir Data Riwayat")
    form.geometry("600x400") 

    image = Image.open("menu.png")
    image = image.resize((600, 400), Image.LANCZOS)  
    background_image = ImageTk.PhotoImage(image)

    background_label = tk.Label(form, image=background_image)
    background_label.place(x=0, y=0, relwidth=1, relheight=1)

    background_label.image = background_image  

    padding_options = {'padx': 10, 'pady': 5}

    tk.Label(form, text="Nama Lengkap").grid(row=0, column=0, sticky="e", **padding_options)
    entry_nama = tk.Entry(form)
    entry_nama.grid(row=0, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Alamat").grid(row=1, column=0, sticky="e", **padding_options)
    entry_alamat = tk.Entry(form)
    entry_alamat.grid(row=1, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Kota").grid(row=2, column=0, sticky="e", **padding_options)
    entry_kota = tk.Entry(form)
    entry_kota.grid(row=2, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Tempat Lahir").grid(row=3, column=0, sticky="e", **padding_options)
    entry_tempat_lahir = tk.Entry(form)
    entry_tempat_lahir.grid(row=3, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Tanggal Lahir").grid(row=0, column=2, sticky="e", **padding_options)
    entry_tanggal_lahir = tk.Entry(form)
    entry_tanggal_lahir.grid(row=0, column=3, sticky="ew", **padding_options)

    tk.Label(form, text="Umur").grid(row=1, column=2, sticky="e", **padding_options)
    entry_umur = tk.Entry(form)
    entry_umur.grid(row=1, column=3, sticky="ew", **padding_options)

    tk.Label(form, text="Nomor BPJS").grid(row=2, column=2, sticky="e", **padding_options)
    entry_no_bpjs = tk.Entry(form)
    entry_no_bpjs.grid(row=2, column=3, sticky="ew", **padding_options)

    tk.Label(form, text="ID Pasien").grid(row=3, column=2, sticky="e", **padding_options)
    entry_id_pasien = tk.Entry(form)
    entry_id_pasien.grid(row=3, column=3, sticky="ew", **padding_options)

    submit_button = tk.Button(form, text="Submit", command=submitForm)
    submit_button.grid(row=4, columnspan=5, pady=10)

    tk.Label(form, text="").grid(row=0, column=4, rowspan=5)

    form.columnconfigure(1, weight=1)
    form.columnconfigure(3, weight=1)
    form.columnconfigure(4, weight=1)

    for i in range(5):
        form.rowconfigure(i, weight=1)

def hapusPasien():
    id = simpledialog.askstring("Input", "Masukkan ID Pasien yang akan dihapus:")
    to_remove = [patient for patient in patients if patient.id_pasien == id]
    if to_remove:
        for patient in to_remove:
            patients.remove(patient)
        saveData()
        messagebox.showinfo("Success", f"{len(to_remove)} pasien dengan ID '{id}' berhasil dihapus.")
    else:
        messagebox.showerror("Error", f"Tidak ada pasien dengan ID '{id}' ditemukan.")

def cariPasien():
    id_pasien = simpledialog.askstring("Input", "Masukkan ID Pasien yang akan dicari:")
    found = False

    for patient in patients:
        if patient.id_pasien == id_pasien:
            info = (
                f"Nama: {patient.nama}\n"
                f"Alamat: {patient.alamat}\n"
                f"Kota: {patient.kota}\n"
                f"Tempat Lahir: {patient.tempat_lahir}\n"
                f"Tanggal Lahir: {patient.tanggal_lahir}\n"
                f"Umur: {patient.umur}\n"
                f"Nomor BPJS: {patient.no_bpjs}\n"
                f"ID Pasien: {patient.id_pasien}"
            )
            found = True
            break

    if found:
        report_window = tk.Toplevel()
        report_window.title(f"Informasi Pasien dengan ID {id_pasien}")

        report_text = Text(report_window, height=10, width=60)
        report_text.pack(padx=20, pady=20)

        report_text.insert(tk.END, f"{'Informasi Pasien':<20} {'Detail':>20}\n")
        report_text.insert(tk.END, "-"*40 + "\n")

        info_lines = info.split('\n')
        for line in info_lines:
            field, value = line.split(': ')
            report_text.insert(tk.END, f"{field:<20} {value:>20}\n")

        report_text.config(state=tk.DISABLED)

    else:
        messagebox.showerror("Error", "Pasien tidak ditemukan.")

def ubahPasien():
    id = simpledialog.askstring("Input", "Masukkan ID Pasien yang ingin diubah:")
    for patient in patients:
        if patient.id_pasien == id:
            form = tk.Toplevel()
            form.title("Ubah Data Pasien")
            form.geometry("600x400")  

            image = Image.open("menu.png")  
            image = image.resize((600, 400), Image.LANCZOS)

            background_image = ImageTk.PhotoImage(image)

            canvas = tk.Canvas(form, width=600, height=400)
            canvas.pack(fill="both", expand=True)

            canvas.create_image(0, 0, anchor="nw", image=background_image)

            tk.Label(form, text="Nama Lengkap", bg='white').place(relx=0.1, rely=0.1)
            entry_nama = tk.Entry(form)
            entry_nama.insert(0, patient.nama)
            entry_nama.place(relx=0.4, rely=0.1)

            tk.Label(form, text="Alamat", bg='white').place(relx=0.1, rely=0.2)
            entry_alamat = tk.Entry(form)
            entry_alamat.insert(0, patient.alamat)
            entry_alamat.place(relx=0.4, rely=0.2)

            tk.Label(form, text="Kota", bg='white').place(relx=0.1, rely=0.3)
            entry_kota = tk.Entry(form)
            entry_kota.insert(0, patient.kota)
            entry_kota.place(relx=0.4, rely=0.3)

            tk.Label(form, text="Tempat Lahir", bg='white').place(relx=0.1, rely=0.4)
            entry_tempat_lahir = tk.Entry(form)
            entry_tempat_lahir.insert(0, patient.tempat_lahir)
            entry_tempat_lahir.place(relx=0.4, rely=0.4)

            tk.Label(form, text="Tanggal Lahir", bg='white').place(relx=0.1, rely=0.5)
            entry_tanggal_lahir = tk.Entry(form)
            entry_tanggal_lahir.insert(0, patient.tanggal_lahir)
            entry_tanggal_lahir.place(relx=0.4, rely=0.5)

            tk.Label(form, text="Umur", bg='white').place(relx=0.1, rely=0.6)
            entry_umur = tk.Entry(form)
            entry_umur.insert(0, patient.umur)
            entry_umur.place(relx=0.4, rely=0.6)

            tk.Label(form, text="Nomor BPJS", bg='white').place(relx=0.1, rely=0.7)
            entry_no_bpjs = tk.Entry(form)
            entry_no_bpjs.insert(0, patient.no_bpjs)
            entry_no_bpjs.place(relx=0.4, rely=0.7)

            tk.Label(form, text="ID Pasien", bg='white').place(relx=0.1, rely=0.8)
            entry_id_pasien = tk.Entry(form)
            entry_id_pasien.insert(0, patient.id_pasien)
            entry_id_pasien.place(relx=0.4, rely=0.8)

            def submitForm():
                patient.nama = entry_nama.get()
                patient.alamat = entry_alamat.get()
                patient.kota = entry_kota.get()
                patient.tempat_lahir = entry_tempat_lahir.get()
                patient.tanggal_lahir = entry_tanggal_lahir.get()
                patient.umur = int(entry_umur.get())
                patient.no_bpjs = int(entry_no_bpjs.get())
                patient.id_pasien = entry_id_pasien.get()
                saveData()
                messagebox.showinfo("Success", "Data pasien telah diubah.")
                form.destroy()

            submit_button = tk.Button(form, text="Submit", command=submitForm)
            submit_button.place(relx=0.5, rely=0.9, anchor="center")

            form.mainloop()

            return

    messagebox.showerror("Error", "Pasien tidak ditemukan.")

def menuData():
    data_window = tk.Toplevel()
    data_window.title("Akses Data Pasien")
    data_window.geometry("600x400")  

    image = Image.open("menu.png")
    image = image.resize((600, 400), Image.LANCZOS)  
    background_image = ImageTk.PhotoImage(image)

    background_label = tk.Label(data_window, image=background_image)
    background_label.place(x=0, y=0, relwidth=1, relheight=1)

    background_label.image = background_image  

    label_title = tk.Label(data_window, text="Akses Data Pasien", font=("Arial", 16, "bold"), bg="white", fg="black")
    label_title.place(relx=0.5, rely=0.05, anchor="center")

    btn_tambah = tk.Button(data_window, text="Tambah Pasien", command=tambahPasien)
    btn_hapus = tk.Button(data_window, text="Hapus Pasien", command=hapusPasien)
    btn_cari = tk.Button(data_window, text="Cari Pasien", command=cariPasien)
    btn_ubah = tk.Button(data_window, text="Ubah Data Pasien", command=ubahPasien)
    btn_kembali = tk.Button(data_window, text="Kembali ke Menu Utama", command=data_window.destroy)

    btn_tambah.grid(row=0, column=0, padx=20, pady=(10, 5), sticky="ew")
    btn_hapus.grid(row=1, column=0, padx=20, pady=(5, 5), sticky="ew")

    btn_cari.grid(row=0, column=1, padx=20, pady=(10, 5), sticky="ew")
    btn_ubah.grid(row=1, column=1, padx=20, pady=(5, 5), sticky="ew")

    btn_kembali.grid(row=2, column=0, columnspan=2, pady=(5, 20), sticky="ew")

    data_window.grid_columnconfigure(0, weight=1)
    data_window.grid_columnconfigure(1, weight=1)
    data_window.grid_rowconfigure(0, weight=1)
    data_window.grid_rowconfigure(1, weight=1)
    data_window.grid_rowconfigure(2, weight=0)

    data_window.mainloop()

def tambahRiwayat():
    no = int(simpledialog.askstring("Input", "Masukkan Nomor:"))
    for riwayat in daftar_riwayat:
        if riwayat.no == no:
            messagebox.showerror("Error", "Nomor riwayat sudah ada, masukkan nomor yang lain.")
            return

    def submitForm():
        tanggal = entry_tanggal.get()
        id_pasien = entry_id_pasien.get()
        diagnosis = entry_diagnosis.get()
        tindakan = entry_tindakan.get()
        kontrol = entry_kontrol.get()
        biaya = entry_biaya.get()

        new_riwayat = Riwayat(no, tanggal, id_pasien, diagnosis, tindakan, kontrol, biaya)
        daftar_riwayat.append(new_riwayat)
        saveRiwayat()
        messagebox.showinfo("Success", "Riwayat berhasil ditambahkan.")
        form.destroy()
    
    form = tk.Toplevel()
    form.title("Formulir Data Riwayat")
    form.geometry("600x400")  

    image = Image.open("menu.png")
    image = image.resize((600, 400), Image.LANCZOS)  
    background_image = ImageTk.PhotoImage(image)

    background_label = tk.Label(form, image=background_image)
    background_label.place(x=0, y=0, relwidth=1, relheight=1)

    background_label.image = background_image  

    padding_options = {'padx': 10, 'pady': 5}

    tk.Label(form, text="Tanggal").grid(row=0, column=0, sticky="e", **padding_options)
    entry_tanggal = tk.Entry(form)
    entry_tanggal.grid(row=0, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="ID Pasien").grid(row=1, column=0, sticky="e", **padding_options)
    entry_id_pasien = tk.Entry(form)
    entry_id_pasien.grid(row=1, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Diagnosis").grid(row=2, column=0, sticky="e", **padding_options)
    entry_diagnosis = tk.Entry(form)
    entry_diagnosis.grid(row=2, column=1, sticky="ew", **padding_options)

    tk.Label(form, text="Tindakan").grid(row=0, column=2, sticky="e", **padding_options)
    entry_tindakan = tk.Entry(form)
    entry_tindakan.grid(row=0, column=3, sticky="ew", **padding_options)

    tk.Label(form, text="Tanggal Kontrol").grid(row=1, column=2, sticky="e", **padding_options)
    entry_kontrol = tk.Entry(form)
    entry_kontrol.grid(row=1, column=3, sticky="ew", **padding_options)

    tk.Label(form, text="Biaya").grid(row=2, column=2, sticky="e", **padding_options)
    entry_biaya = tk.Entry(form)
    entry_biaya.grid(row=2, column=3, sticky="ew", **padding_options)

    submit_button = tk.Button(form, text="Submit", command=submitForm)
    submit_button.grid(row=3, columnspan=4, pady=10)

    tk.Label(form, text="").grid(row=0, column=4, rowspan=4)

    form.columnconfigure(1, weight=1)
    form.columnconfigure(3, weight=1)
    form.columnconfigure(4, weight=1)

    for i in range(4):
        form.rowconfigure(i, weight=1)

    form.mainloop()

def ubahRiwayat():
    no = int(simpledialog.askstring("Input", "Masukkan Nomor Riwayat yang ingin diubah:"))
    for riwayat in daftar_riwayat:
        if riwayat.no == no:
            form = tk.Toplevel()
            form.title("Ubah Data Riwayat")
            form.geometry("600x400") 

            image = Image.open("menu.png") 
            image = image.resize((600, 400), Image.LANCZOS)

            background_image = ImageTk.PhotoImage(image)

            canvas = tk.Canvas(form, width=600, height=400)
            canvas.pack(fill="both", expand=True)

            canvas.create_image(0, 0, anchor="nw", image=background_image)

            padding_options = {'padx': 10, 'pady': 5}

            tk.Label(form, text="Tanggal", bg='white').place(relx=0.1, rely=0.1)
            entry_tanggal = tk.Entry(form)
            entry_tanggal.insert(0, riwayat.tanggal)
            entry_tanggal.place(relx=0.4, rely=0.1)

            tk.Label(form, text="ID Pasien", bg='white').place(relx=0.1, rely=0.2)
            entry_id_pasien = tk.Entry(form)
            entry_id_pasien.insert(0, riwayat.id_pasien)
            entry_id_pasien.place(relx=0.4, rely=0.2)

            tk.Label(form, text="Diagnosis", bg='white').place(relx=0.1, rely=0.3)
            entry_diagnosis = tk.Entry(form)
            entry_diagnosis.insert(0, riwayat.diagnosis)
            entry_diagnosis.place(relx=0.4, rely=0.3)

            tk.Label(form, text="Tindakan", bg='white').place(relx=0.1, rely=0.4)
            entry_tindakan = tk.Entry(form)
            entry_tindakan.insert(0, riwayat.tindakan)
            entry_tindakan.place(relx=0.4, rely=0.4)

            tk.Label(form, text="Kontrol", bg='white').place(relx=0.1, rely=0.5)
            entry_kontrol = tk.Entry(form)
            entry_kontrol.insert(0, riwayat.kontrol)
            entry_kontrol.place(relx=0.4, rely=0.5)

            tk.Label(form, text="Biaya", bg='white').place(relx=0.1, rely=0.6)
            entry_biaya = tk.Entry(form)
            entry_biaya.insert(0, riwayat.biaya)
            entry_biaya.place(relx=0.4, rely=0.6)
            def submitForm():
                riwayat.tanggal = entry_tanggal.get()
                riwayat.id_pasien = entry_id_pasien.get()
                riwayat.diagnosis = entry_diagnosis.get()
                riwayat.tindakan = entry_tindakan.get()
                riwayat.kontrol = int(entry_kontrol.get())
                riwayat.biaya = int(entry_biaya.get())
                saveRiwayat()
                messagebox.showinfo("Success", "Data riwayat telah diubah.")
                form.destroy()

            submit_button = tk.Button(form, text="Submit", command=submitForm)
            submit_button.place(relx=0.5, rely=0.9, anchor="center")

            form.mainloop()

            return

    messagebox.showerror("Error", "Riwayat tidak ditemukan.")

def hapusRiwayat():
    nomor = int(simpledialog.askstring("Input", "Masukkan Nomor riwayat yang akan dihapus:"))
    to_remove = [riwayat for riwayat in daftar_riwayat if riwayat.no == nomor]
    if to_remove:
        for riwayat in to_remove:
            daftar_riwayat.remove(riwayat)
        saveRiwayat()
        messagebox.showinfo("Success", f"{len(to_remove)} riwayat dengan nomor '{nomor}' berhasil dihapus.")
    else:
        messagebox.showerror("Error", f"Tidak ada riwayat dengan nomor '{nomor}' ditemukan.")

def cariRiwayat():
    id_pasien = simpledialog.askstring("Input", "Masukkan ID Pasien yang akan dicari:")
    found = False

    report_window = tk.Toplevel()
    report_window.title(f"Riwayat Pasien dengan ID {id_pasien}")

    report_text = Text(report_window, height=10, width=60)
    report_text.pack(padx=20, pady=20)

    no_counter = 1

    for riwayat in daftar_riwayat:
        if riwayat.id_pasien == id_pasien:
            if not found:
                report_text.insert(tk.END, f"{'No':<5} | {'Riwayat Pasien':<15} | {'Detail':>20}\n")
                report_text.insert(tk.END, "-"*60 + "\n")
                found = True

            report_text.insert(tk.END, f"{no_counter:<5} | {'Tanggal':<15} | {riwayat.tanggal:>20}\n")
            report_text.insert(tk.END, f"{'':<5} | {'Diagnosis':<15} | {riwayat.diagnosis:>20}\n")
            report_text.insert(tk.END, f"{'':<5} | {'Tindakan':<15} | {riwayat.tindakan:>20}\n")
            report_text.insert(tk.END, f"{'':<5} | {'Kontrol':<15} | {riwayat.kontrol:>20}\n")
            report_text.insert(tk.END, f"{'':<5} | {'Biaya':<15} | {riwayat.biaya:>20}\n")
            report_text.insert(tk.END, "-"*60 + "\n")
            
            no_counter += 1

    if not found:
        messagebox.showerror("Error", "Riwayat tidak ditemukan.")

def menuRiwayat():
    data_window = tk.Toplevel()
    data_window.title("Akses Data Riwayat")
    data_window.geometry("600x400")  

    image = Image.open("menu.png")
    image = image.resize((600, 400), Image.LANCZOS)
    background_image = ImageTk.PhotoImage(image)

    background_label = tk.Label(data_window, image=background_image)
    background_label.place(x=0, y=0, relwidth=1, relheight=1)

    background_label.image = background_image  

    label_title = tk.Label(data_window, text="Akses Data Riwayat", font=("Arial", 16, "bold"), bg="white", fg="black")
    label_title.place(relx=0.5, rely=0.05, anchor="center")

    btn_tambah = tk.Button(data_window, text="Tambah Riwayat", command=tambahRiwayat)
    btn_ubah = tk.Button(data_window, text="Ubah Riwayat", command=ubahRiwayat)
    btn_hapus = tk.Button(data_window, text="Hapus Riwayat", command=hapusRiwayat)
    btn_cari = tk.Button(data_window, text="Cari Riwayat", command=cariRiwayat)
    btn_kembali = tk.Button(data_window, text="Kembali ke Menu Utama", command=data_window.destroy)

    btn_tambah.grid(row=0, column=0, padx=20, pady=(10, 5), sticky="ew")
    btn_hapus.grid(row=1, column=0, padx=20, pady=(5, 5), sticky="ew")

    btn_cari.grid(row=0, column=1, padx=20, pady=(10, 5), sticky="ew")
    btn_ubah.grid(row=1, column=1, padx=20, pady=(5, 5), sticky="ew")

    btn_kembali.grid(row=2, column=0, columnspan=2, pady=(5, 20), sticky="ew")

    data_window.grid_columnconfigure(0, weight=1)
    data_window.grid_columnconfigure(1, weight=1)
    data_window.grid_rowconfigure(0, weight=1)
    data_window.grid_rowconfigure(1, weight=1)
    data_window.grid_rowconfigure(2, weight=0)

    data_window.mainloop()

def infoPasien():
    id = simpledialog.askstring("Input", "Masukkan ID Pasien yang akan dicari:")
    info1 = ""
    info2 = ""
    found = False

    for patient in patients:
        if patient.id_pasien == id:
            info1 = (
                f"Nama: {patient.nama}\n"
                f"Alamat: {patient.alamat}\n"
                f"Kota: {patient.kota}\n"
                f"Tempat Lahir: {patient.tempat_lahir}\n"
                f"Tanggal Lahir: {patient.tanggal_lahir}\n"
                f"Umur: {patient.umur}\n"
                f"Nomor BPJS: {patient.no_bpjs}\n"
            )

    for riwayat in daftar_riwayat:
        if riwayat.id_pasien == id:
            info2 += (
                f"Tanggal: {riwayat.tanggal}\n"
                f"Diagnosis: {riwayat.diagnosis}\n"
                f"Tindakan: {riwayat.tindakan}\n"
                f"Kontrol: {riwayat.kontrol}\n"
                f"Biaya: {riwayat.biaya}\n\n"
            )
            found = True
    
    if found:
        report_window_info1 = tk.Toplevel()
        report_window_info1.title("Info Pasien")

        report_text_info1 = Text(report_window_info1, height=10, width=50)
        report_text_info1.pack(padx=20, pady=20)

        report_text_info1.insert(tk.END, "Informasi Pasien:\n")
        report_text_info1.insert(tk.END, "=" * 50 + "\n")
        report_text_info1.insert(tk.END, info1)
        report_text_info1.config(state=tk.DISABLED)

        report_window_info2 = tk.Toplevel()
        report_window_info2.title("Riwayat Pasien")

        report_text_info2 = Text(report_window_info2, height=20, width=50)
        report_text_info2.pack(padx=20, pady=20)

        report_text_info2.insert(tk.END, "Riwayat Pasien:\n")
        report_text_info2.insert(tk.END, "=" * 50 + "\n")
        report_text_info2.insert(tk.END, info2)
        report_text_info2.config(state=tk.DISABLED)

        return
    messagebox.showerror("Error", "ID Pasien tidak ditemukan.")

def parseMonth(monthStr):
    months = {
        "Januari": 1, "Jan": 1,
        "Februari": 2, "Feb": 2,
        "Maret": 3, "Mar": 3,
        "April": 4, "Apr": 4,
        "Mei": 5,
        "Juni": 6, "Jun": 6,
        "Juli": 7, "Jul": 7,
        "Agustus": 8, "Agu": 8,
        "September": 9, "Sep": 9,
        "Oktober": 10, "Okt": 10,
        "November": 11, "Nov": 11,
        "Desember": 12, "Des": 12
    }
    return months.get(monthStr, -1)

def parseTanggal(tanggalStr):
    day, monthStr, year = None, None, None
    parts = tanggalStr.split()
    if len(parts) == 3:
        try:
            day = int(parts[0])
            monthStr = parts[1]
            year = int(parts[2])
        except ValueError:
            pass

    if not day:
        parts = tanggalStr.split('-')
        if len(parts) == 3:
            try:
                day = int(parts[0])
                monthStr = parts[1]
                year = int(parts[2])
            except ValueError:
                pass

    if day is not None and monthStr is not None and year is not None:
        month = parseMonth(monthStr)
        if month != -1:
            if year >= 0 and year < 100:
                if year < 22:
                    year += 2000
                else:
                    year += 2000
            return day, month, year

    return None, None, None

def laporanPendapatan():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            records = []
            for line in reader:
                tanggal = line[1]  
                biaya = int(line[6].replace(",", ""))  

                records.append((tanggal, biaya))

            pendapatan_bulanan = [[0]*12, [0]*12]
            pendapatan_tahunan = [0, 0]

            for tanggal, biaya in records:
                day, month, year = parseTanggal(tanggal)
                if year == 2022 or year == 2023:
                    idx = year - 2022
                    pendapatan_bulanan[idx][month - 1] += biaya
                    pendapatan_tahunan[idx] += biaya

            info2022 = ""
            count = 0

            for i in range(12):
                info2022 += f"Bulan ke - {count+1} : Rp {pendapatan_bulanan[0][i]}\n"
                count += 1
            info2022 += f"Pendapatan Total Tahun 2022 : Rp{str(pendapatan_tahunan[0])}\n"
            info2022 += f"Rata-rata Pendapatan Bulanan Tahun 2022: Rp {int(pendapatan_tahunan[0]) // 12}"

            messagebox.showinfo("Data Pendapatan 2022", info2022)

            info2023 = ""
            count = 0

            for i in range(12):
                info2023 += f"Bulan ke - {count+1} : Rp {pendapatan_bulanan[1][i]}\n"
                count += 1
            info2023 += f"Pendapatan Total Tahun 2023 : Rp{str(pendapatan_tahunan[1])}\n"
            info2023 += f"Rata-rata Pendapatan Bulanan Tahun 2023: Rp {int(pendapatan_tahunan[1]) // 12}"

            messagebox.showinfo("Data Pendapatan 2022", info2023)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporanPenyakitPerTahun():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            yearly_Data = defaultdict(lambda: {'total_pasien': 0, 'diagnosis_counts': defaultdict(int)})

            for line in reader:
                tanggal = line[1]  
                diagnosis = line[3]  
                day, month, year = parseTanggal(tanggal)

                if year is None:
                    continue  

                if year == 22:
                    display_year = 2022
                elif year == 23:
                    display_year = 2023
                else:
                    display_year = year

                yearly_Data[display_year]['total_pasien'] += 1
                yearly_Data[display_year]['diagnosis_counts'][diagnosis] += 1

            result_text = "\nData Diagnosis Per Tahun:\n"
            for year, data in sorted(yearly_Data.items()):
                result_text += f"Tahun: {year}, Total Pasien: {data['total_pasien']}\n"
                for diagnosis, count in data['diagnosis_counts'].items():
                    result_text += f"  Diagnosis: {diagnosis}, Jumlah: {count}\n"

            messagebox.showinfo("Laporan Penyakit", result_text)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporanTotal(yearly_Data, year):
    report_text = ""

    report_text += f"{'Diagnosis':<20} | {'Jumlah':>10}\n"
    report_text += "-" * 35 + "\n"
    for diagnosis, count in yearly_Data[year]['diagnosis_counts'].items():
        report_text += f"{diagnosis:<20} | {count:>10}\n"
    report_text += "-" * 35 + "\n"

    return report_text

def laporanPenyakitTahun2022():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            yearly_Data = defaultdict(lambda: {'total_pasien': 0, 'diagnosis_counts': defaultdict(int)})

            for line in reader:
                tanggal = line[1]  
                diagnosis = line[3]  
                day, month, year = parseTanggal(tanggal)

                if year is None:
                    continue  

                if year == 2022:
                    yearly_Data[year]['total_pasien'] += 1
                    yearly_Data[year]['diagnosis_counts'][diagnosis] += 1

            report_window = tk.Toplevel()
            report_window.title("Laporan Penyakit Tahun 2022")

            report_text = Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, laporanTotal(yearly_Data, 2022))
            report_text.insert(tk.END, f"Total Pasien: {yearly_Data[2022]['total_pasien']}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporanPenyakitTahun2023():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            yearly_Data = defaultdict(lambda: {'total_pasien': 0, 'diagnosis_counts': defaultdict(int)})

            for line in reader:
                tanggal = line[1]  
                diagnosis = line[3]  
                day, month, year = parseTanggal(tanggal)

                if year is None:
                    continue  

                if year == 2023:
                    yearly_Data[year]['total_pasien'] += 1
                    yearly_Data[year]['diagnosis_counts'][diagnosis] += 1

            report_window = tk.Toplevel()
            report_window.title("Laporan Penyakit Tahun 2022")

            report_text = Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, laporanTotal(yearly_Data, 2023))
            report_text.insert(tk.END, f"Total Pasien: {yearly_Data[2023]['total_pasien']}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporanPenyakitPerBulan2022():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            yearly_monthly_Data = defaultdict(lambda: defaultdict(lambda: {'total_pasien': 0, 'diagnosis_counts': defaultdict(int)}))

            for line in reader:
                tanggal = line[1]  
                diagnosis = line[3]  
                day, month, year = parseTanggal(tanggal)

                if year is None or month is None:
                    continue  

                if year >= 0 and year < 100:
                    if year < 22:
                        year += 2000
                    else:
                        year += 2000

                yearly_monthly_Data[year][month]['total_pasien'] += 1
                yearly_monthly_Data[year][month]['diagnosis_counts'][diagnosis] += 1

            report_window = tk.Toplevel()
            report_window.title("Laporan Penyakit Per Bulan Tahun 2022")

            report_text = tk.Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Diagnosis':<20} | {'Jumlah':<10}\n")
            report_text.insert(tk.END, "-"*45 + "\n")

            for month in range(1, 13):
                if yearly_monthly_Data[2022][month]['total_pasien'] > 0:
                    for diagnosis, count in yearly_monthly_Data[2022][month]['diagnosis_counts'].items():
                        bulan = [
                            "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                            "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                        ][month - 1]
                        report_text.insert(tk.END, f"{bulan:<10} | {diagnosis:<20} | {count:<10}\n")

            report_text.insert(tk.END, "\n")

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Total Pasien':<15}\n")
            report_text.insert(tk.END, "-"*25 + "\n")

            for month in range(1, 13):
                if yearly_monthly_Data[2022][month]['total_pasien'] > 0:
                    bulan = [
                        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                    ][month - 1]
                    total_pasien = yearly_monthly_Data[2022][month]['total_pasien']
                    report_text.insert(tk.END, f"{bulan:<10} | {total_pasien:<15}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporanPenyakitPerBulan2023():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            yearly_monthly_Data = defaultdict(lambda: defaultdict(lambda: {'total_pasien': 0, 'diagnosis_counts': defaultdict(int)}))

            for line in reader:
                tanggal = line[1]  
                diagnosis = line[3]  
                day, month, year = parseTanggal(tanggal)

                if year is None or month is None:
                    continue  

                if year >= 0 and year < 100:
                    if year < 23:
                        year += 2000
                    else:
                        year += 2000

                yearly_monthly_Data[year][month]['total_pasien'] += 1
                yearly_monthly_Data[year][month]['diagnosis_counts'][diagnosis] += 1

            report_window = tk.Toplevel()
            report_window.title("Laporan Penyakit Per Bulan Tahun 2023")

            report_text = tk.Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Diagnosis':<20} | {'Jumlah':<10}\n")
            report_text.insert(tk.END, "-"*45 + "\n")

            for month in range(1, 13):
                if yearly_monthly_Data[2023][month]['total_pasien'] > 0:
                    for diagnosis, count in yearly_monthly_Data[2023][month]['diagnosis_counts'].items():
                        bulan = [
                            "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                            "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                        ][month - 1]
                        report_text.insert(tk.END, f"{bulan:<10} | {diagnosis:<20} | {count:<10}\n")

            report_text.insert(tk.END, "\n")

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Total Pasien':<15}\n")
            report_text.insert(tk.END, "-"*25 + "\n")

            for month in range(1, 13):
                if yearly_monthly_Data[2023][month]['total_pasien'] > 0:
                    bulan = [
                        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                    ][month - 1]
                    total_pasien = yearly_monthly_Data[2023][month]['total_pasien']
                    report_text.insert(tk.END, f"{bulan:<10} | {total_pasien:<15}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def menuPenyakit():
    data_window = tk.Toplevel()
    data_window.title("Data Penyakit")
    data_window.geometry("400x300")  

    btn_bulan2022 = tk.Button(data_window, text="Data Penyakit per Bulan 2022", command=laporanPenyakitPerBulan2022)
    btn_bulan2023 = tk.Button(data_window, text="Data Penyakit per Bulan 2023", command=laporanPenyakitPerBulan2023)

    btn_tahun2022 = tk.Button(data_window, text="Data Penyakit Tahun 2022", command=laporanPenyakitTahun2022)
    btn_tahun2023 = tk.Button(data_window, text="Data Penyakit Tahun 2023", command=laporanPenyakitTahun2023)

    btn_kembali = tk.Button(data_window, text="Kembali ke Menu Utama", command=data_window.destroy)

    btn_bulan2022.pack(fill=tk.BOTH, expand=True, pady=5)
    btn_bulan2023.pack(fill=tk.BOTH, expand=True, pady=5)

    btn_tahun2022.pack(fill=tk.BOTH, expand=True, pady=5)
    btn_tahun2023.pack(fill=tk.BOTH, expand=True, pady=5)

    btn_kembali.pack(fill=tk.BOTH, expand=True, pady=5)

    data_window.mainloop()

def laporan2022():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            records = []
            for line in reader:
                tanggal = line[1]
                biaya = int(line[6].replace(",", ""))

                records.append((tanggal, biaya))

            pendapatan_bulanan = [0] * 12
            pendapatan_total = 0

            for tanggal, biaya in records:
                day, month, year = parseTanggal(tanggal)
                if year == 2022:
                    pendapatan_bulanan[month - 1] += biaya
                    pendapatan_total += biaya

            report_window = tk.Toplevel()
            report_window.title("Laporan Pendapatan Tahun 2022")

            report_text = tk.Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Pendapatan (Rp)':<20}\n")
            report_text.insert(tk.END, "-"*30 + "\n")

            for i in range(12):
                bulan = [
                    "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                    "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                ][i]
                report_text.insert(tk.END, f"{bulan:<10} | {pendapatan_bulanan[i]:<20,.0f}\n")

            report_text.insert(tk.END, "-"*30 + "\n")
            report_text.insert(tk.END, f"Pendapatan Total Tahun 2022 : Rp {pendapatan_total:,}\n")
            report_text.insert(tk.END, f"Rata-rata Pendapatan Bulanan Tahun 2022: Rp {pendapatan_total // 12:,}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def laporan2023():
    try:
        with open("Riwayat.csv", newline='', encoding='utf-8') as file:
            reader = csv.reader(file)
            next(reader)  

            records = []
            for line in reader:
                tanggal = line[1]
                biaya = int(line[6].replace(",", ""))

                records.append((tanggal, biaya))

            pendapatan_bulanan = [0] * 12
            pendapatan_total = 0

            for tanggal, biaya in records:
                day, month, year = parseTanggal(tanggal)
                if year == 2023:
                    pendapatan_bulanan[month - 1] += biaya
                    pendapatan_total += biaya

            report_window = tk.Toplevel()
            report_window.title("Laporan Pendapatan Tahun 2023")

            report_text = tk.Text(report_window, height=20, width=60)
            report_text.pack(padx=20, pady=20)

            report_text.insert(tk.END, f"{'Bulan':<10} | {'Pendapatan (Rp)':<20}\n")
            report_text.insert(tk.END, "-"*30 + "\n")

            for i in range(12):
                bulan = [
                    "Januari", "Februari", "Maret", "April", "Mei", "Juni",
                    "Juli", "Agustus", "September", "Oktober", "November", "Desember"
                ][i]
                report_text.insert(tk.END, f"{bulan:<10} | {pendapatan_bulanan[i]:<20,.0f}\n")

            report_text.insert(tk.END, "-"*30 + "\n")
            report_text.insert(tk.END, f"Pendapatan Total Tahun 2023 : Rp {pendapatan_total:,}\n")
            report_text.insert(tk.END, f"Rata-rata Pendapatan Bulanan Tahun 2023: Rp {pendapatan_total // 12:,}\n")

            report_text.config(state=tk.DISABLED)

    except FileNotFoundError:
        messagebox.showerror("Error", "File Riwayat.csv not found.")

def menuPendapatan():
    data_window = tk.Toplevel()
    data_window.title("Data Pendapatan")
    data_window.geometry("400x300")  

    btn_2022 = tk.Button(data_window, text="Data Pendapatan 2022", command=laporan2022)
    btn_2023 = tk.Button(data_window, text="Data Pendapatan 2023", command=laporan2023)
    btn_kembali = tk.Button(data_window, text="Kembali ke Menu Utama", command=data_window.destroy)

    btn_2022.pack(fill=tk.BOTH, expand=True, pady=5)
    btn_2023.pack(fill=tk.BOTH, expand=True, pady=5)
    btn_kembali.pack(fill=tk.BOTH, expand=True, pady=5)

    data_window.mainloop()

def laporanTahunan(yearly_monthly_Data, year):
    report_text = ""
    for month in range(1, 13):  
        if yearly_monthly_Data[year][month]['total_pasien'] > 0:
            report_text += f"Bulan {month}: Total Pasien = {yearly_monthly_Data[year][month]['total_pasien']}\n"
            for diagnosis, count in yearly_monthly_Data[year][month]['diagnosis_counts'].items():
                report_text += f"  Diagnosis: {diagnosis}, Jumlah: {count}\n"
    return report_text

def laporanKontrol():
    id_pasien = simpledialog.askstring("Input", "Masukkan ID Pasien yang akan dicari:")
    found = False
    info = ""

    kontrol_data = []
    kontrol_count = 0

    for riwayat in daftar_riwayat:
        if riwayat.id_pasien == id_pasien:
            kontrol_count += 1
            kontrol_data.append((kontrol_count, riwayat.kontrol, riwayat.tanggal))
            found = True

    if found:
        report_window = tk.Toplevel()
        report_window.title(f"Riwayat Kontrol Pasien dengan ID {id_pasien}")

        report_text = Text(report_window, height=20, width=60)
        report_text.pack(padx=20, pady=20)

        report_text.insert(tk.END, f"{'Data ke':<10} | {'Tanggal Kontrol':<20} | {'Tanggal Riwayat':<20}\n")
        report_text.insert(tk.END, "-"*60 + "\n")

        for kontrol in kontrol_data:
            report_text.insert(tk.END, f"{kontrol[0]:<10} | {kontrol[1]:<20} | {kontrol[2]:<20}\n")

        report_text.config(state=tk.DISABLED)

    else:
        messagebox.showerror("Error", "Riwayat tidak ditemukan.")
        
def main():
    root = tk.Tk()
    root.title("Aplikasi Data Klinik")
    root.geometry("600x400")  

    image = Image.open("menu.png")
    image = image.resize((600, 400), Image.LANCZOS)  
    background_image = ImageTk.PhotoImage(image)

    background_label = tk.Label(root, image=background_image)
    background_label.place(x=0, y=0, relwidth=1, relheight=1)

    background_label.image = background_image  
    background_label.configure(bg='black', bd=0)

    label_title = tk.Label(root, text="Aplikasi Data Klinik", font=("Helvetica", 16, "bold"))
    label_title.grid(row=0, column=0, columnspan=2, pady=10)

    bacaData()
    bacaRiwayat()

    btn_data_pasien = tk.Button(root, text="Akses Data Pasien", command=menuData)
    btn_riwayat_pasien = tk.Button(root, text="Akses Riwayat Pasien", command=menuRiwayat)
    btn_info_pasien = tk.Button(root, text="Akses Informasi Pasien", command=infoPasien)
    btn_pendapatan = tk.Button(root, text="Laporan Pendapatan Klinik", command=menuPendapatan) 
    btn_penyakit = tk.Button(root, text="Laporan Penyakit", command=menuPenyakit)
    btn_data_rumah_sakit = tk.Button(root, text="Laporan Kontrol", command=laporanKontrol)
    btn_keluar = tk.Button(root, text="Keluar", command=root.quit, width=10)  

    btn_data_pasien.grid(row=1, column=0, padx=10, pady=5, sticky="ew")
    btn_riwayat_pasien.grid(row=2, column=0, padx=10, pady=5, sticky="ew")
    btn_info_pasien.grid(row=3, column=0, padx=10, pady=5, sticky="ew")

    btn_pendapatan.grid(row=1, column=1, padx=10, pady=5, sticky="ew")
    btn_penyakit.grid(row=2, column=1, padx=10, pady=5, sticky="ew")
    btn_data_rumah_sakit.grid(row=3, column=1, padx=10, pady=5, sticky="ew")

    btn_keluar.grid(row=4, column=0, columnspan=2, pady=10, sticky="ew")

    root.grid_columnconfigure(0, weight=1)
    root.grid_columnconfigure(1, weight=1)
    root.grid_rowconfigure(0, weight=0)  
    root.grid_rowconfigure(1, weight=1) 
    root.grid_rowconfigure(2, weight=1)  
    root.grid_rowconfigure(3, weight=1)  
    root.grid_rowconfigure(4, weight=0) 

    root.mainloop()
if __name__ == "__main__":
    main()
