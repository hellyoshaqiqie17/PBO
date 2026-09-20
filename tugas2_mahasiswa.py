"""
Tugas 2: Sistem Record Data Mahasiswa (Versi Python)
Implementasi Class dan Method Pemrograman Berorientasi Objek (OOP)
Nama    : Hellyos Ageng Haqiqie
NIM     : 163251001
Jurusan : Robotics & AI Engineering
"""

class Mahasiswa:
    """Class yang merepresentasikan entitas Mahasiswa."""
    def __init__(self, nim: str, nama: str, jurusan: str, tugas: float = 0.0, uts: float = 0.0, uas: float = 0.0):
        self._nim = nim
        self._nama = nama
        self._jurusan = jurusan
        self._nilai_tugas = tugas
        self._nilai_uts = uts
        self._nilai_uas = uas

    # Getter methods
    def get_nim(self) -> str:
        return self._nim

    def get_nama(self) -> str:
        return self._nama

    def get_jurusan(self) -> str:
        return self._jurusan

    def get_nilai_tugas(self) -> float:
        return self._nilai_tugas

    def get_nilai_uts(self) -> float:
        return self._nilai_uts

    def get_nilai_uas(self) -> float:
        return self._nilai_uas

    def ubah_nilai(self, tugas_baru: float, uts_baru: float, uas_baru: float):
        """Method untuk memperbarui data nilai mahasiswa."""
        self._nilai_tugas = tugas_baru
        self._nilai_uts = uts_baru
        self._nilai_uas = uas_baru

    def hitung_nilai_akhir(self) -> float:
        """Method menghitung Nilai Akhir (Bobot: Tugas 30%, UTS 30%, UAS 40%)."""
        return (0.30 * self._nilai_tugas) + (0.30 * self._nilai_uts) + (0.40 * self._nilai_uas)

    def get_grade(self) -> str:
        """Method menentukan Grade Huruf berdasarkan Nilai Akhir."""
        na = self.hitung_nilai_akhir()
        if na >= 85:
            return "A"
        elif na >= 75:
            return "B"
        elif na >= 65:
            return "C"
        elif na >= 50:
            return "D"
        else:
            return "E"

    def tampilkan_data(self):
        """Method mencetak baris data mahasiswa untuk tabel rekap."""
        print(f"{self._nim:<14}{self._nama:<22}{self._jurusan:<26}"
              f"{self._nilai_tugas:>8.1f}{self._nilai_uts:>8.1f}{self._nilai_uas:>8.1f}"
              f"{self.hitung_nilai_akhir():>10.2f}{self.get_grade():>7}")


class RecordDataMahasiswa:
    """Class pengelola sekumpulan Record Mahasiswa."""
    def __init__(self):
        self._data_mahasiswa: list[Mahasiswa] = []

    def cari_index_by_nim(self, nim: str) -> int:
        """Helper method pencarian indeks mahasiswa berdasarkan NIM."""
        for i, mhs in enumerate(self._data_mahasiswa):
            if mhs.get_nim() == nim:
                return i
        return -1

    def input_data_mahasiswa(self, mhs: Mahasiswa) -> bool:
        """Method 1: Mengisikan data mahasiswa baru dengan validasi keunikan NIM."""
        if self.cari_index_by_nim(mhs.get_nim()) != -1:
            print(f">> Error: Mahasiswa dengan NIM {mhs.get_nim()} sudah terdaftar!")
            return False

        self._data_mahasiswa.append(mhs)
        print(f">> Sukses: Data mahasiswa {mhs.get_nama()} ({mhs.get_nim()}) berhasil disimpan.")
        return True

    def lihat_nilai_semua(self):
        """Method 2: Menampilkan rekap seluruh tabel nilai mahasiswa."""
        if not self._data_mahasiswa:
            print(">> Belum ada data mahasiswa yang tersimpan.")
            return

        print("\n" + "=" * 95)
        print("                              DAFTAR NILAI MAHASISWA                              ")
        print("=" * 95)
        print(f"{'NIM':<14}{'Nama':<22}{'Jurusan':<26}{'Tugas':>8}{'UTS':>8}{'UAS':>8}{'Akhir':>10}{'Grade':>7}")
        print("-" * 95)
        for mhs in self._data_mahasiswa:
            mhs.tampilkan_data()
        print("=" * 95)

    def lihat_nilai_by_nim(self, nim: str):
        """Method melihat rincian nilai mahasiswa tertentu berdasarkan NIM."""
        idx = self.cari_index_by_nim(nim)
        if idx == -1:
            print(f">> Mahasiswa dengan NIM {nim} tidak ditemukan.")
            return

        m = self._data_mahasiswa[idx]
        print("\n" + "=" * 54)
        print("              RECORD DETAIL NILAI MAHASISWA           ")
        print("=" * 54)
        print(f"{'NIM':<18}: {m.get_nim()}")
        print(f"{'Nama':<18}: {m.get_nama()}")
        print(f"{'Jurusan':<18}: {m.get_jurusan()}")
        print("-" * 54)
        print(f"{'Nilai Tugas (30%)':<18}: {m.get_nilai_tugas():.1f}")
        print(f"{'Nilai UTS (30%)':<18}: {m.get_nilai_uts():.1f}")
        print(f"{'Nilai UAS (40%)':<18}: {m.get_nilai_uas():.1f}")
        print("-" * 54)
        print(f"{'Nilai Akhir':<18}: {m.hitung_nilai_akhir():.2f}")
        print(f"{'Grade':<18}: {m.get_grade()}")
        print("=" * 54)

    def rubah_nilai_mahasiswa(self, nim: str, tugas_baru: float, uts_baru: float, uas_baru: float) -> bool:
        """Method 3: Merubah nilai mahasiswa berdasarkan kunci NIM."""
        idx = self.cari_index_by_nim(nim)
        if idx == -1:
            print(f">> Error: Mahasiswa dengan NIM {nim} tidak ditemukan! Perubahan dibatalkan.")
            return False

        self._data_mahasiswa[idx].ubah_nilai(tugas_baru, uts_baru, uas_baru)
        print(f">> Sukses: Nilai mahasiswa {self._data_mahasiswa[idx].get_nama()} ({nim}) berhasil diperbarui!")
        return True

    def is_kosong(self) -> bool:
        return len(self._data_mahasiswa) == 0


def input_nilai_valid(prompt: str) -> float:
    """Fungsi pembantu untuk memvalidasi input nilai numerik (0-100)."""
    while True:
        try:
            val = float(input(prompt))
            if 0.0 <= val <= 100.0:
                return val
            print(">> Nilai harus berada dalam rentang 0 sampai 100!")
        except ValueError:
            print(">> Input salah! Harap masukkan angka yang valid.")


def main():
    record_mhs = RecordDataMahasiswa()

    while True:
        print("\n======================================================")
        print("       SISTEM RECORD DATA MAHASISWA (OOP Python)      ")
        print("======================================================")
        print(" 1. Mengisikan Data Mahasiswa (Input Data Baru)       ")
        print(" 2. Melihat Nilai (Semua Mahasiswa)                   ")
        print(" 3. Melihat Nilai (Berdasarkan NIM Mahasiswa)         ")
        print(" 4. Merubah Nilai Mahasiswa                           ")
        print(" 5. Keluar                                            ")
        print("======================================================")

        try:
            pilihan = int(input("Pilih menu [1-5]: "))
        except ValueError:
            print("Input tidak valid! Harap masukkan angka 1-5.")
            continue

        if pilihan == 1:
            print("\n--- INPUT DATA MAHASISWA BARU ---")
            nim = input("Masukkan NIM     : ").strip()
            nama = input("Masukkan Nama    : ").strip()
            jurusan = input("Masukkan Jurusan : ").strip()

            tugas = input_nilai_valid("Masukkan Nilai Tugas (0-100): ")
            uts = input_nilai_valid("Masukkan Nilai UTS (0-100)  : ")
            uas = input_nilai_valid("Masukkan Nilai UAS (0-100)  : ")

            mhs_baru = Mahasiswa(nim, nama, jurusan, tugas, uts, uas)
            record_mhs.input_data_mahasiswa(mhs_baru)

        elif pilihan == 2:
            record_mhs.lihat_nilai_semua()

        elif pilihan == 3:
            if record_mhs.is_kosong():
                print(">> Data mahasiswa masih kosong.")
            else:
                nim = input("Masukkan NIM mahasiswa yang ingin dilihat: ").strip()
                record_mhs.lihat_nilai_by_nim(nim)

        elif pilihan == 4:
            if record_mhs.is_kosong():
                print(">> Data mahasiswa masih kosong. Tidak ada data yang dapat diubah.")
            else:
                print("\n--- MERUBAH NILAI MAHASISWA ---")
                nim = input("Masukkan NIM mahasiswa yang akan diubah nilainya: ").strip()
                if record_mhs.cari_index_by_nim(nim) == -1:
                    print(f">> Mahasiswa dengan NIM {nim} tidak ditemukan.")
                else:
                    print("\nMasukkan data nilai baru:")
                    tugas_baru = input_nilai_valid("Nilai Tugas Baru (0-100): ")
                    uts_baru = input_nilai_valid("Nilai UTS Baru (0-100)  : ")
                    uas_baru = input_nilai_valid("Nilai UAS Baru (0-100)  : ")
                    record_mhs.rubah_nilai_mahasiswa(nim, tugas_baru, uts_baru, uas_baru)

        elif pilihan == 5:
            print("\nProgram selesai. Terima kasih!")
            break

        else:
            print(">> Pilihan menu tidak valid! Silakan pilih antara 1-5.")


if __name__ == "__main__":
    main()
