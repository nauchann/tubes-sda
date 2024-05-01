// create.hpp
#ifndef CREATE_HPP
#define CREATE_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class create {
public:
    struct buku {
        string judul, penulis, penerbit;
        char rak;
        int status;
    };
    void tambahbuku(vector<vector<buku>>& gudang);
};

void create::tambahbuku(vector<vector<buku>>& gudang) {
    buku bukuBaru;
    cout << "Masukkan judul buku: ";
    cin.ignore(); // Membersihkan buffer sebelum getline
    getline(cin, bukuBaru.judul);

    cout << "Masukkan nama penulis buku: ";
    getline(cin, bukuBaru.penulis);

    cout << "Masukkan nama penerbit buku: ";
    getline(cin, bukuBaru.penerbit);

    cout << "Masukkan kode rak buku: ";
    cin >> bukuBaru.rak;

    cout << "Masukkan jumlah buku: ";
    cin >> bukuBaru.status;
    
    gudang.push_back({bukuBaru});
    cout << "Buku berhasil ditambahkan!\n";
}

#endif // CREATE_HPP
