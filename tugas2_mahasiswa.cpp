#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Class yang merepresentasikan entitas Mahasiswa
class Mahasiswa {
private:
    string nim;
    string nama;
    string jurusan;
    double nilaiTugas;
    double nilaiUTS;
    double nilaiUAS;

public:
    // Constructor default
    Mahasiswa() : nim(""), nama(""), jurusan(""), nilaiTugas(0), nilaiUTS(0), nilaiUAS(0) {}

    // Constructor berparameter untuk mengisikan data awal mahasiswa
    Mahasiswa(string idNim, string namaMhs, string jur, double tugas, double uts, double uas) {
        nim = idNim;
        nama = namaMhs;
        jurusan = jur;
        nilaiTugas = tugas;
        nilaiUTS = uts;
        nilaiUAS = uas;
    }

    // Method Getter
    string getNim() const { return nim; }
    string getNama() const { return nama; }
    string getJurusan() const { return jurusan; }
    double getNilaiTugas() const { return nilaiTugas; }
    double getNilaiUTS() const { return nilaiUTS; }
    double getNilaiUAS() const { return nilaiUAS; }

    // Method untuk merubah nilai mahasiswa
    void ubahNilai(double tugasBaru, double utsBaru, double uasBaru) {
        nilaiTugas = tugasBaru;
        nilaiUTS = utsBaru;
        nilaiUAS = uasBaru;
    }

    // Method untuk menghitung Nilai Akhir (Bobot: Tugas 30%, UTS 30%, UAS 40%)
    double hitungNilaiAkhir() const {
        return (0.30 * nilaiTugas) + (0.30 * nilaiUTS) + (0.40 * nilaiUAS);
    }

    // Method untuk menentukan Grade Huruf
    string getGrade() const {
        double na = hitungNilaiAkhir();
        if (na >= 85) return "A";
        else if (na >= 75) return "B";
        else if (na >= 65) return "C";
        else if (na >= 50) return "D";
        else return "E";
    }

    // Method untuk menampilkan detail data dan nilai mahasiswa
    void tampilkanData() const {
        cout << left << setw(14) << nim
             << setw(22) << nama
             << setw(18) << jurusan
             << right << setw(8) << fixed << setprecision(1) << nilaiTugas
             << setw(8) << nilaiUTS
             << setw(8) << nilaiUAS
             << setw(10) << hitungNilaiAkhir()
             << setw(7)  << getGrade() << "\n";
    }
};

// Class pengelola sekumpulan Record Mahasiswa
class RekamMedikMahasiswa { // atau RecordDataMahasiswa
private:
    vector<Mahasiswa> dataMahasiswa;

    // Helper method untuk mencari index mahasiswa berdasarkan NIM
    int cariIndexByNim(const string& nim) const {
        for (size_t i = 0; i < dataMahasiswa.size(); ++i) {
            if (dataMahasiswa[i].getNim() == nim) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    // Method 1: Mengisikan data mahasiswa baru
    bool inputDataMahasiswa(const Mahasiswa& mhs) {
        if (cariIndexByNim(mhs.getNim()) != -1) {
            cout << ">> Error: Mahasiswa dengan NIM " << mhs.getNim() << " sudah terdaftar!\n";
            return false;
        }
        dataMahasiswa.push_back(mhs);
        cout << ">> Sukses: Data mahasiswa " << mhs.getNama() << " (" << mhs.getNim() << ") berhasil disimpan.\n";
        return true;
    }

    // Method 2: Melihat nilai mahasiswa (seluruhnya maupun perorangan)
    void lihatNilaiSemua() const {
        if (dataMahasiswa.empty()) {
            cout << ">> Belum ada data mahasiswa yang tersimpan.\n";
            return;
        }

        cout << "\n==========================================================================================\n";
        cout << "                                  DAFTAR NILAI MAHASISWA                                  \n";
        cout << "==========================================================================================\n";
        cout << left << setw(14) << "NIM"
             << setw(22) << "Nama"
             << setw(18) << "Jurusan"
             << right << setw(8) << "Tugas"
             << setw(8) << "UTS"
             << setw(8) << "UAS"
             << setw(10) << "Akhir"
             << setw(7)  << "Grade" << "\n";
        cout << "------------------------------------------------------------------------------------------\n";

        for (const auto& mhs : dataMahasiswa) {
            mhs.tampilkanData();
        }
        cout << "==========================================================================================\n";
    }

    // Method melihat nilai spesifik mahasiswa berdasarkan NIM
    void lihatNilaiByNim(const string& nim) const {
        int idx = cariIndexByNim(nim);
        if (idx == -1) {
            cout << ">> Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
            return;
        }

        const Mahasiswa& m = dataMahasiswa[idx];
        cout << "\n======================================================\n";
        cout << "              RECORD DETAIL NILAI MAHASISWA           \n";
        cout << "======================================================\n";
        cout << left << setw(18) << "NIM" << ": " << m.getNim() << "\n";
        cout << left << setw(18) << "Nama" << ": " << m.getNama() << "\n";
        cout << left << setw(18) << "Jurusan" << ": " << m.getJurusan() << "\n";
        cout << "------------------------------------------------------\n";
        cout << left << setw(18) << "Nilai Tugas (30%)" << ": " << fixed << setprecision(1) << m.getNilaiTugas() << "\n";
        cout << left << setw(18) << "Nilai UTS (30%)"   << ": " << fixed << setprecision(1) << m.getNilaiUTS() << "\n";
        cout << left << setw(18) << "Nilai UAS (40%)"   << ": " << fixed << setprecision(1) << m.getNilaiUAS() << "\n";
        cout << "------------------------------------------------------\n";
        cout << left << setw(18) << "Nilai Akhir"       << ": " << fixed << setprecision(2) << m.hitungNilaiAkhir() << "\n";
        cout << left << setw(18) << "Grade"             << ": " << m.getGrade() << "\n";
        cout << "======================================================\n";
    }

    // Method 3: Merubah nilai mahasiswa berdasarkan NIM
    bool rubahNilaiMahasiswa(const string& nim, double tugasBaru, double utsBaru, double uasBaru) {
        int idx = cariIndexByNim(nim);
        if (idx == -1) {
            cout << ">> Error: Mahasiswa dengan NIM " << nim << " tidak ditemukan! Perubahan dibatalkan.\n";
            return false;
        }

        dataMahasiswa[idx].ubahNilai(tugasBaru, utsBaru, uasBaru);
        cout << ">> Sukses: Nilai mahasiswa " << dataMahasiswa[idx].getNama() 
             << " (" << nim << ") berhasil diperbarui!\n";
        return true;
    }

    // Cek apakah data kosong
    bool isKosong() const {
        return dataMahasiswa.empty();
    }
};

// Helper function untuk input nilai dengan validasi 0 - 100
double inputNilaiValid(const string& label) {
    double nilai;
    while (true) {
        cout << label;
        if (cin >> nilai) {
            if (nilai >= 0.0 && nilai <= 100.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return nilai;
            } else {
                cout << ">> Nilai harus berada dalam rentang 0 sampai 100!\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else {
            cout << ">> Input salah! Masukkan angka yang valid.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    RekamMedikMahasiswa recordMhs;
    int pilihan;

    do {
        cout << "\n======================================================\n";
        cout << "       SISTEM RECORD DATA MAHASISWA (OOP C++)         \n";
        cout << "======================================================\n";
        cout << " 1. Mengisikan Data Mahasiswa (Input Data Baru)       \n";
        cout << " 2. Melihat Nilai (Semua Mahasiswa)                   \n";
        cout << " 3. Melihat Nilai (Berdasarkan NIM Mahasiswa)         \n";
        cout << " 4. Merubah Nilai Mahasiswa                           \n";
        cout << " 5. Keluar                                            \n";
        cout << "======================================================\n";
        cout << "Pilih menu [1-5]: ";

        if (!(cin >> pilihan)) {
            cout << "Input tidak valid! Masukkan angka 1-5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan newline

        switch (pilihan) {
            case 1: {
                cout << "\n--- INPUT DATA MAHASISWA BARU ---\n";
                string nim, nama, jurusan;
                cout << "Masukkan NIM     : ";
                getline(cin, nim);
                cout << "Masukkan Nama    : ";
                getline(cin, nama);
                cout << "Masukkan Jurusan : ";
                getline(cin, jurusan);

                double tugas = inputNilaiValid("Masukkan Nilai Tugas (0-100): ");
                double uts   = inputNilaiValid("Masukkan Nilai UTS (0-100)  : ");
                double uas   = inputNilaiValid("Masukkan Nilai UAS (0-100)  : ");

                Mahasiswa mhsBaru(nim, nama, jurusan, tugas, uts, uas);
                recordMhs.inputDataMahasiswa(mhsBaru);
                break;
            }
            case 2: {
                recordMhs.lihatNilaiSemua();
                break;
            }
            case 3: {
                if (recordMhs.isKosong()) {
                    cout << ">> Data mahasiswa masih kosong.\n";
                } else {
                    string nim;
                    cout << "Masukkan NIM mahasiswa yang ingin dilihat: ";
                    getline(cin, nim);
                    recordMhs.lihatNilaiByNim(nim);
                }
                break;
            }
            case 4: {
                if (recordMhs.isKosong()) {
                    cout << ">> Data mahasiswa masih kosong. Tidak ada data untuk dirubah.\n";
                } else {
                    string nim;
                    cout << "\n--- MERUBAH NILAI MAHASISWA ---\n";
                    cout << "Masukkan NIM mahasiswa yang akan diubah nilainya: ";
                    getline(cin, nim);

                    cout << "\nMasukkan data nilai baru:\n";
                    double tugasBaru = inputNilaiValid("Nilai Tugas Baru (0-100): ");
                    double utsBaru   = inputNilaiValid("Nilai UTS Baru (0-100)  : ");
                    double uasBaru   = inputNilaiValid("Nilai UAS Baru (0-100)  : ");

                    recordMhs.rubahNilaiMahasiswa(nim, tugasBaru, utsBaru, uasBaru);
                }
                break;
            }
            case 5: {
                cout << "\nTerima kasih telah menggunakan sistem record data mahasiswa.\n";
                break;
            }
            default: {
                cout << ">> Pilihan menu tidak valid! Silakan pilih antara 1-5.\n";
                break;
            }
        }
    } while (pilihan != 5);

    return 0;
}
