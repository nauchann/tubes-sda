#include <iostream>
#include <limits>
#include "create.hpp" // Include header untuk create.hpp
#include "read.hpp"   // Include header untuk read.hpp
#include "update.hpp" // Include header untuk update.hpp
#include "delete.hpp" // Include header untuk delete.hpp

using namespace std;

void pressAnyKey() {
    cout << "Press any key to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
}
int main() {
    string filename = "gudang.txt"; // Nama file gudang
    create c;
    read r;
    update u;
    del d;

    int pilihan;
    do {
        r.tampilkanMenu(); // Tampilkan menu
        cin >> pilihan;
            
        switch(pilihan) {
            case 1:
                {
                    // Tambah buku baru
                    vector<create::buku> gudang;
                    if (c.tambahbuku(gudang, filename)) {
                        c.simpanKeFile(filename, gudang);
                    }
                    pressAnyKey();
                    break;
                }
            case 2:
                {
                    r.sortingBukuDariFile(filename);
                    r.tampilkanBukuDariFile(filename);
                    pressAnyKey();
                    break;
                }
            case 3:
                {   
                    string keyword;
                    cout << "Masukkan kata kunci (judul buku / penulis) untuk mencari buku: ";
                    cin.ignore(); // Membersihkan input buffer
                    getline(cin, keyword);
                    r.cariBuku(filename, keyword);
                    pressAnyKey();
                    break;
                }
            case 4:
                {
                    u.updateStatus(filename);
                    pressAnyKey();
                    break;
                }
            case 5:
                {
                    string judul;
                    cout << "Masukkan judul buku yang ingin dihapus: ";
                    cin.ignore();
                    getline(cin, judul);
                    d.hapusBuku(filename, judul); 
                    pressAnyKey();
                    break;
                }
            case 6:
                {
                    r.tampilkanGenre(filename);
                    string genre;
                    cout << "Masukkan nama genre yang ingin dilihat: ";
                    cin.ignore(); // Membersihkan input buffer
                    getline(cin, genre);
                    r.filterBukuByGenre(filename, genre);
                    pressAnyKey();
                    break;
                }    
            case 7:
                cout << "Terima kasih! Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
                pressAnyKey();
        }
    } while (pilihan != 7);
    
    return 0;
}
