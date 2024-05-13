#include <iostream>
#include "create.hpp" // Include header untuk create.hpp
#include "read.hpp"   // Include header untuk read.hpp

using namespace std;

int main() {
    string filename = "gudang.txt"; // Nama file gudang

    int pilihan;
    do {
        read::tampilkanMenu(); // Tampilkan menu
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                {
                // Tambah buku baru
                queue<create::buku> gudangQueue;
                create c;
                c.tambahbuku(gudangQueue);
                c.simpanKeFile(filename, gudangQueue);
                break;
                }
            case 2:
                read::sortingBukuDariFile(filename);
                // Tampilkan daftar buku dari file
                read::tampilkanBukuDariFile(filename);
                break;
            case 3:
                // Keluar
                cout << "Terima kasih! Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
        }
    } while (pilihan != 3);

    return 0;
}
