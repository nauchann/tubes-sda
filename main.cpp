#include <iostream>
#include "create.hpp" // Include header untuk create.hpp
#include "read.hpp"   // Include header untuk read.hpp
#include "update.hpp" // Include header untuk update.hpp

using namespace std;

int main() {
    string filename = "gudang.txt"; // Nama file gudang

    int pilihan;
    do {
        read::tampilkanMenu(); // Tampilkan menu
        cin >> pilihan;
            
            switch(pilihan) {
            case 1:
                {
                // Tambah buku baru
                    queue<create::buku> gudangQueue;
                    create c;
                    if (c.tambahbuku(gudangQueue, filename)) {
                        c.simpanKeFile(filename, gudangQueue);
                    }
                    break;
                }
            case 2:
                read::sortingBukuDariFile(filename);
                // Tampilkan daftar buku dari file
                read::tampilkanBukuDariFile(filename);
                break;
            case 3:
                {   
                string keyword;
                cout << "Masukkan kata kunci untuk mencari buku: ";
                cin.ignore(); // Membersihkan input buffer
                getline(cin, keyword);
                read::cariBuku(filename, keyword);
                break;
                }
            case 4:
                {
                read::updateStatus(filename);
                break;
                }
            case 5:
                // Keluar
                cout << "Terima kasih! Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}
