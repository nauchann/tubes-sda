#ifndef CREATE_HPP
#define CREATE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
#include <sstream>

using namespace std;

class create {
public:
    struct buku {
        string judul, penulis, genre;
        char rak;
        int status;
    };
    bool tambahbuku(vector<buku>& gudang, const string& filename);
    void simpanKeFile(const string& filename, const vector<buku>& gudang);
private:
    bool cekBukuDiFile(const string& filename, const string& judul);
};

bool create::tambahbuku(vector<buku>& gudang, const string& filename) {
    buku bukuBaru;
    cin.ignore(); // Membersihkan buffer sebelum meminta input pengguna
    cout << "Masukkan judul buku: ";
    getline(cin, bukuBaru.judul);

    // Cek apakah buku sudah ada dalam file
    if (cekBukuDiFile(filename, bukuBaru.judul)) {
        cout << "Buku sudah ada dalam gudang. Tidak bisa ditambahkan lagi.\n";
        return false;
    }

    cout << "Masukkan nama penulis buku: ";
    getline(cin, bukuBaru.penulis);

    cout << "Masukkan nama genre buku: ";
    getline(cin, bukuBaru.genre);

    cout << "Masukkan kode rak buku: ";
    cin >> bukuBaru.rak;
    cin.ignore(); // Membersihkan buffer setelah cin

    cout << "Masukkan jumlah buku: ";
    cin >> bukuBaru.status;
    cin.ignore(); // Membersihkan buffer setelah cin

    gudang.push_back(bukuBaru); // Menggunakan push_back() untuk menambahkan ke vector
    cout << "Buku berhasil ditambahkan!\n";
    return true;
}

bool create::cekBukuDiFile(const string& filename, const string& judul) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return false;
    }

    string line, existingJudul;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, existingJudul, ',');
        existingJudul.erase(0, existingJudul.find_first_not_of(" \t\n\r\f\v"));
        if (existingJudul == judul) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void create::simpanKeFile(const string& filename, const vector<buku>& gudang) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    for (const auto& b : gudang) {
        file << b.judul << ", " << b.penulis << ", " << b.genre
             << ", " << b.rak << ", " << b.status << endl;
    }

    file.close();
    cout << "Data buku berhasil disimpan ke dalam file \"" << filename << "\"." << endl;
}

#endif // CREATE_HPP

