#ifndef CREATE_HPP
#define CREATE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <queue> // Header untuk queue
#include <sstream>

using namespace std;

class create {
public:
    struct buku {
        string judul, penulis, genre;
        char rak;
        int status;
    };
    bool tambahbuku(queue<buku>& gudangQueue, const string& filename);
    void simpanKeFile(const string& filename, queue<buku>& gudangQueue);
private:
    bool cekBukuDiFile(const string& filename, const string& judul);
};

bool create::tambahbuku(queue<buku>& gudangQueue, const string& filename) {
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

    cout << "Masukkan jumlah buku: ";
    cin >> bukuBaru.status;

    gudangQueue.push(bukuBaru); // Menggunakan push() untuk menambahkan ke queue
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

void create::simpanKeFile(const string& filename, queue<buku>& gudangQueue) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    while (!gudangQueue.empty()) {
        buku b = gudangQueue.front();
        file << b.judul << ", " << b.penulis << ", " << b.genre
             << ", " << b.rak << ", " << b.status << endl;
        gudangQueue.pop();
    }

    file.close();
    cout << "Data buku berhasil disimpan ke dalam file \"" << filename << "\"." << endl;
}

#endif // CREATE_HPP
