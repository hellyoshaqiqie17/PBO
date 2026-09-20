"""
Tugas 1: Simulasi Program Pembayaran Rumah Makan (Versi Python)
Implementasi Class dan Method Pemrograman Berorientasi Objek (OOP)
Nama    : Hellyos Ageng Haqiqie
NIM     : 163251001
Jurusan : Robotics & AI Engineering
"""

class Menu:
    """Class untuk merepresentasikan entitas menu makanan/minuman."""
    def __init__(self, id_menu: int, nama_menu: str, harga_menu: float):
        self._id = id_menu
        self._nama = nama_menu
        self._harga = harga_menu

    def get_id(self) -> int:
        return self._id

    def get_nama(self) -> str:
        return self._nama

    def get_harga(self) -> float:
        return self._harga


class ItemPesanan:
    """Class untuk merepresentasikan item pesanan yang dipilih."""
    def __init__(self, menu: Menu, jumlah: int):
        self._menu = menu
        self._jumlah = jumlah

    def get_menu(self) -> Menu:
        return self._menu

    def get_jumlah(self) -> int:
        return self._jumlah

    def get_subtotal(self) -> float:
        return self._menu.get_harga() * self._jumlah


class KasirRumahMakan:
    """Class utama kasir rumah makan yang mengelola katalog dan transaksi."""
    def __init__(self):
        # Inisialisasi katalog menu makanan dan minuman
        self._daftar_menu = [
            Menu(1, "Nasi Goreng Spesial", 22000),
            Menu(2, "Ayam Bakar Madu", 28000),
            Menu(3, "Soto Ayam Lamongan", 20000),
            Menu(4, "Bebek Goreng Crispy", 35000),
            Menu(5, "Mie Goreng Seafood", 25000),
            Menu(6, "Es Teh Manis", 5000),
            Menu(7, "Es Jeruk Peras", 7000)
        ]
        self._pesanan: list[ItemPesanan] = []

    def tampilkan_menu(self):
        """Method untuk menampilkan daftar menu beserta harga."""
        print("\n" + "=" * 54)
        print("               DAFTAR MENU RUMAH MAKAN               ")
        print("=" * 54)
        print(f"{'No':<6}{'Nama Makanan/Minuman':<26}{'Harga Satuan':>18}")
        print("-" * 54)
        for item in self._daftar_menu:
            print(f"{item.get_id():<6}{item.get_nama():<26}{'Rp ' + f'{item.get_harga():,.0f}':>18}")
        print("=" * 54)

    def cari_menu_by_id(self, id_menu: int) -> Menu | None:
        """Helper method untuk mencari menu berdasarkan ID."""
        for m in self._daftar_menu:
            if m.get_id() == id_menu:
                return m
        return None

    def tambah_pesanan(self, id_menu: int, jumlah: int) -> bool:
        """Method untuk menambahkan item pesanan ke keranjang."""
        if jumlah <= 0:
            print(">> Error: Jumlah pesanan harus lebih dari 0!")
            return False

        menu_dipilih = self.cari_menu_by_id(id_menu)
        if menu_dipilih:
            self._pesanan.append(ItemPesanan(menu_dipilih, jumlah))
            print(f">> Berhasil menambahkan {jumlah}x {menu_dipilih.get_nama()} ke pesanan.")
            return True
        else:
            print(">> Error: Nomor menu tidak valid!")
            return False

    def hitung_total(self) -> float:
        """Method menghitung total keseluruhan tagihan."""
        return sum(item.get_subtotal() for item in self._pesanan)

    def tampilkan_pesanan(self):
        """Method menampilkan ringkasan makanan yang telah dipesan."""
        if not self._pesanan:
            print(">> Belum ada makanan yang dipesan.")
            return

        print("\n" + "=" * 54)
        print("                   RINGKASAN PESANAN                  ")
        print("=" * 54)
        print(f"{'Item':<24}{'Qty':<8}{'Harga':>10}{'Subtotal':>12}")
        print("-" * 54)
        for p in self._pesanan:
            print(f"{p.get_menu().get_nama():<24}{p.get_jumlah():<8}{'Rp ' + f'{p.get_menu().get_harga():,.0f}':>10}{'Rp ' + f'{p.get_subtotal():,.0f}':>12}")
        print("-" * 54)
        print(f"{'TOTAL HARUS DIBAYAR:':<32}{'Rp ' + f'{self.hitung_total():,.0f}':>22}")
        print("=" * 54)

    def proses_pembayaran(self, uang_bayar: float):
        """Method memproses pembayaran, menghitung kembalian, dan cetak struk."""
        total = self.hitung_total()
        kembalian = uang_bayar - total

        print("\n" + "=" * 54)
        print("                   STRUK PEMBAYARAN                   ")
        print("=" * 54)
        print(f"{'Total Tagihan':<30}: Rp {total:,.0f}")
        print(f"{'Uang Pembayaran Pelanggan':<30}: Rp {uang_bayar:,.0f}")
        print(f"{'Uang Kembalian':<30}: Rp {kembalian:,.0f}")
        print("=" * 54)
        print("          Terima Kasih Atas Kunjungan Anda!          ")
        print("=" * 54 + "\n")

    def ada_pesanan(self) -> bool:
        return len(self._pesanan) > 0


def main():
    kasir = KasirRumahMakan()

    print("======================================================")
    print("     SIMULASI APLIKASI KASIR PEMBAYARAN RUMAH MAKAN   ")
    print("======================================================")

    # 1. Tampilan Awal: Menu Makanan Beserta Harga
    kasir.tampilkan_menu()

    # 2. Input data pada kasir berupa makanan dan jumlah
    while True:
        while True:
            try:
                pilihan_menu = int(input("\nMasukkan nomor menu yang dipesan : "))
                if kasir.cari_menu_by_id(pilihan_menu) is not None:
                    break
                print(">> Nomor menu tidak ditemukan dalam katalog! Masukkan nomor yang valid.")
            except ValueError:
                print(">> Input tidak valid! Harap masukkan angka.")

        while True:
            try:
                jumlah = int(input("Masukkan jumlah (porsi/item)    : "))
                if jumlah > 0:
                    break
                print(">> Jumlah harus berupa angka bulat positif!")
            except ValueError:
                print(">> Input tidak valid! Harap masukkan angka bulat.")

        kasir.tambah_pesanan(pilihan_menu, jumlah)

        lanjut = input("Apakah ingin memesan menu lain? (y/n): ").strip().lower()
        if lanjut != 'y':
            break

    if not kasir.ada_pesanan():
        print("\nTidak ada pesanan yang diproses. Program selesai.")
        return

    # 3. Output: Ringkasan makanan yang dipesan & total bayar
    kasir.tampilkan_pesanan()

    # 4. Input uang pembayaran oleh pelanggan
    total_bayar = kasir.hitung_total()
    while True:
        try:
            uang_bayar = float(input("\nMasukkan uang pembayaran dari pelanggan: Rp "))
            if uang_bayar >= total_bayar:
                break
            else:
                kekurangan = total_bayar - uang_bayar
                print(f">> Uang pembayaran kurang! Dibutuhkan minimal Rp {total_bayar:,.0f} (Kekurangan: Rp {kekurangan:,.0f})")
        except ValueError:
            print(">> Input salah! Harap masukkan nominal uang yang valid.")

    # 5. Output: Jumlah uang kembalian & struk pembayaran
    kasir.proses_pembayaran(uang_bayar)


if __name__ == "__main__":
    main()
