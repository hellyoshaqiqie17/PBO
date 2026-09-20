#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Class untuk merepresentasikan entitas Menu Makanan
class Menu {
private:
    int id;
    string nama;
    double harga;

public:
    Menu(int idMenu, string namaMenu, double hargaMenu) {
        id = idMenu;
        nama = namaMenu;
        harga = hargaMenu;
    }

    int getId() const {
        return id;
    }

    string getNama() const {
        return nama;
    }

    double getHarga() const {
        return harga;
    }
};

// Class untuk merepresentasikan Item yang Dipesan
class ItemPesanan {
private:
    Menu menu;
    int jumlah;

public:
    ItemPesanan(Menu m, int jml) : menu(m), jumlah(jml) {}

    Menu getMenu() const {
        return menu;
    }

    int getJumlah() const {
        return jumlah;
    }

    double getSubtotal() const {
        return menu.getHarga() * jumlah;
    }
};

// Class utama Kasir Rumah Makan (Mengelola Transaksi)
class KasirRumahMakan {
private:
    vector<Menu> daftarMenu;
    vector<ItemPesanan> pesanan;

public:
    // Constructor: inisialisasi daftar menu rumah makan
    KasirRumahMakan() {
        daftarMenu.push_back(Menu(1, "Nasi Goreng Spesial", 22000));
        daftarMenu.push_back(Menu(2, "Ayam Bakar Madu", 28000));
        daftarMenu.push_back(Menu(3, "Soto Ayam Lamongan", 20000));
        daftarMenu.push_back(Menu(4, "Bebek Goreng Crispy", 35000));
        daftarMenu.push_back(Menu(5, "Mie Goreng Seafood", 25000));
        daftarMenu.push_back(Menu(6, "Es Teh Manis", 5000));
        daftarMenu.push_back(Menu(7, "Es Jeruk Peras", 7000));
    }

    // Method untuk menampilkan daftar menu beserta harga
    void tampilkanMenu() const {
        cout << "\n======================================================\n";
        cout << "               DAFTAR MENU RUMAH MAKAN               \n";
        cout << "======================================================\n";
        cout << left << setw(6)  << "No" 
             << setw(26) << "Nama Makanan/Minuman" 
             << right << setw(18) << "Harga Satuan" << "\n";
        cout << "------------------------------------------------------\n";
        
        for (const auto& item : daftarMenu) {
            cout << left << setw(6)  << item.getId() 
                 << setw(26) << item.getNama() 
                 << right << setw(15) << "Rp " << fixed << setprecision(0) << item.getHarga() << "\n";
        }
        cout << "======================================================\n";
    }

    // Method mencari menu berdasarkan ID
    bool cariMenuById(int id, Menu& hasil) const {
        for (const auto& m : daftarMenu) {
            if (m.getId() == id) {
                hasil = m;
                return true;
            }
        }
        return false;
    }

    // Method menambahkan pesanan
    bool tambahPesanan(int idMenu, int jumlah) {
        if (jumlah <= 0) {
            cout << ">> Error: Jumlah pesanan harus lebih dari 0!\n";
            return false;
        }

        Menu menuDipilih(0, "", 0);
        if (cariMenuById(idMenu, menuDipilih)) {
            pesanan.push_back(ItemPesanan(menuDipilih, jumlah));
            cout << ">> Berhasil menambahkan " << jumlah << "x " << menuDipilih.getNama() << " ke pesanan.\n";
            return true;
        } else {
            cout << ">> Error: Nomor menu tidak valid!\n";
            return false;
        }
    }

    // Method menghitung total pembayaran
    double hitungTotal() const {
        double total = 0;
        for (const auto& item : pesanan) {
            total += item.getSubtotal();
        }
        return total;
    }

    // Method menampilkan ringkasan pesanan
    void tampilkanPesanan() const {
        if (pesanan.empty()) {
            cout << ">> Belum ada makanan yang dipesan.\n";
            return;
        }

        cout << "\n======================================================\n";
        cout << "                   RINGKASAN PESANAN                  \n";
        cout << "======================================================\n";
        cout << left << setw(24) << "Item"
             << setw(8)  << "Qty"
             << right << setw(12) << "Harga"
             << right << setw(14) << "Subtotal" << "\n";
        cout << "------------------------------------------------------\n";

        for (const auto& p : pesanan) {
            cout << left << setw(24) << p.getMenu().getNama()
                 << setw(8)  << p.getJumlah()
                 << right << setw(9) << "Rp " << fixed << setprecision(0) << p.getMenu().getHarga()
                 << right << setw(11) << "Rp " << fixed << setprecision(0) << p.getSubtotal() << "\n";
        }
        cout << "------------------------------------------------------\n";
        cout << left << setw(32) << "TOTAL HARUS DIBAYAR:" 
             << right << setw(18) << "Rp " << fixed << setprecision(0) << hitungTotal() << "\n";
        cout << "======================================================\n";
    }

    // Method untuk memproses pembayaran dan menghitung uang kembalian
    void prosesPembayaran(double uangBayar) {
        double total = hitungTotal();
        double kembalian = uangBayar - total;

        cout << "\n======================================================\n";
        cout << "                   STRUK PEMBAYARAN                   \n";
        cout << "======================================================\n";
        cout << left << setw(30) << "Total Tagihan" 
             << ": Rp " << fixed << setprecision(0) << total << "\n";
        cout << left << setw(30) << "Uang Pembayaran Pelanggan" 
             << ": Rp " << fixed << setprecision(0) << uangBayar << "\n";
        cout << left << setw(30) << "Uang Kembalian" 
             << ": Rp " << fixed << setprecision(0) << kembalian << "\n";
        cout << "======================================================\n";
        cout << "          Terima Kasih Atas Kunjungan Anda!          \n";
        cout << "======================================================\n\n";
    }

    // Method untuk mengecek apakah ada pesanan
    bool adaPesanan() const {
        return !pesanan.empty();
    }

    // Method mereset transaksi
    void resetTransaksi() {
        pesanan.clear();
    }
};

int main() {
    KasirRumahMakan kasir;
    char lanjutPesan = 'y';

    cout << "======================================================\n";
    cout << "     SIMULASI APLIKASI KASIR PEMBAYARAN RUMAH MAKAN   \n";
    cout << "======================================================\n";

    // 1. Tampilan Awal Menu Makanan beserta Harga
    kasir.tampilkanMenu();

    // 2. Input data pada kasir berupa makanan dan jumlah
    do {
        int pilihanMenu, jumlah;
        cout << "\nMasukkan nomor menu yang dipesan : ";
        while (!(cin >> pilihanMenu)) {
            cout << "Input tidak valid! Masukkan angka menu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Masukkan jumlah (porsi/item)    : ";
        while (!(cin >> jumlah) || jumlah <= 0) {
            cout << "Jumlah harus berupa angka bulat positif! Masukkan lagi: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        kasir.tambahPesanan(pilihanMenu, jumlah);

        cout << "Apakah ingin memesan menu lain? (y/n): ";
        cin >> lanjutPesan;
    } while (lanjutPesan == 'y' || lanjutPesan == 'Y');

    if (!kasir.adaPesanan()) {
        cout << "\nTidak ada pesanan yang diproses. Program selesai.\n";
        return 0;
    }

    // 3. Output berupa tampilan makanan yang telah dipesan dan total harus dibayar
    kasir.tampilkanPesanan();

    // 4. Input data/uang pembayaran oleh pelanggan
    double totalBayar = kasir.hitungTotal();
    double uangBayar = 0;

    cout << "\n--- PROSES PEMBAYARAN ---\n";
    while (true) {
        cout << "Masukkan uang pembayaran dari pelanggan: Rp ";
        if (cin >> uangBayar) {
            if (uangBayar >= totalBayar) {
                break;
            } else {
                cout << ">> Uang pembayaran kurang! Dibutuhkan minimal Rp " 
                     << fixed << setprecision(0) << totalBayar 
                     << " (Kekurangan: Rp " << (totalBayar - uangBayar) << ")\n";
            }
        } else {
            cout << "Input salah! Harap masukkan nominal uang yang valid.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // 5. Output jumlah uang kembalian kepada pelanggan & struk
    kasir.prosesPembayaran(uangBayar);

    return 0;
}
