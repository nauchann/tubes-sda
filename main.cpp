#include <iostream>
#include "create.hpp" // Include header untuk create.hpp
#include "read.hpp"   // Include header untuk read.hpp
#include "update.hpp" // Include header untuk update.hpp
#include "delete.hpp" // Include header untuk delete.hpp

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
                    vector<create::buku> gudang;
                    create c;
                    if (c.tambahbuku(gudang, filename)) {
                        c.simpanKeFile(filename, gudang);
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
                update::updateStatus(filename);
                break;
                }
               case 5:
                {
                    string judul;
                    cout << "Masukkan judul buku yang ingin dihapus: ";
                    cin.ignore();
                    getline(cin, judul);
                    hapusBuku(filename, judul); 
                    break;
                }
            case 6:
                cout << "Terima kasih! Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
        }
    } while (pilihan != 6);
    
    return 0;
}
