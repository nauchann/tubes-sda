// read.hpp
#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <vector>
#include <string>
#include "create.hpp"

using namespace std;

class read {
public:
    static void tampilkanMenu();
    static void tampilkanGudang(const vector<vector<create::buku>>& gudang);
};

void read::tampilkanMenu() {
    cout << "=== MENU ===\n";
    cout << "1. Tambah Buku\n";
    cout << "2. Tampilkan Daftar Buku\n";
    cout << "3. Keluar\n";
    cout << "Pilihan: ";
}

void read::tampilkanGudang(const vector<vector<create::buku>>& gudang) {
    cout << "Daftar Buku:\n";
    int nomorRak = 1;
    for (const auto& rak : gudang) {
        cout << "Rak " << nomorRak << ":\n";
        for (const auto& buku : rak) {
            cout << "Judul: " << buku.judul << ", Penulis: " << buku.penulis
                << ", Penerbit: " << buku.penerbit << ", Rak: " << buku.rak
                << ", Jumlah: " << buku.status << endl;
        }
        nomorRak++;
    }
}

#endif // READ_HPP
