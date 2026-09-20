# Pemrograman Berorientasi Objek (PBO) - C++ & Python

Repository tugas mata kuliah Pemrograman Berorientasi Objek (PBO) mengenai implementasi konsep *Class* dan *Method* menggunakan dua versi bahasa pemrograman: **C++** dan **Python**.

**Identitas Mahasiswa:**
- **Nama:** Hellyos Ageng Haqiqie
- **NIM:** 163251001
- **Jurusan:** Robotics & AI Engineering

---

## Ringkasan Tugas

### Tugas 1: Simulasi Pembayaran Kasir Rumah Makan
Program aplikasi kasir rumah makan yang menampilkan menu makanan beserta harga, menerima input pesanan makanan dan jumlah secara berulang, menampilkan ringkasan pesanan & total pembayaran, menerima input uang pembayaran, memvalidasi pembayaran, dan mencetak struk transaksi dengan uang kembalian.
- **Versi C++:** [`tugas1_kasir.cpp`](./tugas1_kasir.cpp)
- **Versi Python:** [`tugas1_kasir.py`](./tugas1_kasir.py)

### Tugas 2: Sistem Record Data Mahasiswa & Flowchart
Program manajemen data akademik mahasiswa berbasis OOP dengan method untuk:
1. Mengisikan data mahasiswa baru (NIM, Nama, Jurusan, Nilai Tugas, UTS, UAS) dengan verifikasi keunikan NIM.
2. Melihat seluruh daftar nilai mahasiswa terhitung (bobot 30% Tugas, 30% UTS, 40% UAS beserta Grade A-E) maupun melihat detail perorangan berdasarkan NIM.
3. Merubah nilai mahasiswa berdasarkan pencarian NIM.
- **Versi C++:** [`tugas2_mahasiswa.cpp`](./tugas2_mahasiswa.cpp)
- **Versi Python:** [`tugas2_mahasiswa.py`](./tugas2_mahasiswa.py)
- **Diagram Alir (Flowchart TikZ):** [`flowchart_tugas2.tex`](./flowchart_tugas2.tex)

### Laporan Lengkap
- Dokumen laporan teknis lengkap format LaTeX: [`laporan_tugas.tex`](./laporan_tugas.tex)

---

### 1. Versi C++
```bash
# Kompilasi & Jalankan Tugas 1 (Kasir)
g++ -std=c++17 tugas1_kasir.cpp -o tugas1_kasir
./tugas1_kasir

# Kompilasi & Jalankan Tugas 2 (Record Mahasiswa)
g++ -std=c++17 tugas2_mahasiswa.cpp -o tugas2_mahasiswa
./tugas2_mahasiswa
```

### 2. Versi Python
```bash
# Jalankan Tugas 1 (Kasir)
python tugas1_kasir.py

# Jalankan Tugas 2 (Record Mahasiswa)
python tugas2_mahasiswa.py
```
