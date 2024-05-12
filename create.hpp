#ifndef CREATE_HPP
#define CREATE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <queue> // Header untuk queue

using namespace std;

class create {
public:
    struct buku {
        string judul, penulis, penerbit;
        char rak;
        int status;
    };
    void tambahbuku(queue<buku>& gudangQueue);
    void simpanKeFile(const string& filename, queue<buku>& gudangQueue);
};

void create::tambahbuku(queue<buku>& gudangQueue) {
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

    gudangQueue.push(bukuBaru); // Menggunakan push() untuk menambahkan ke queue
    cout << "Buku berhasil ditambahkan!\n";
}

void create::simpanKeFile(const string& filename, queue<buku>& gudangQueue) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    while (!gudangQueue.empty()) {
        buku b = gudangQueue.front();
        file << "Judul: " << b.judul << ", Penulis: " << b.penulis << ", Penerbit: " << b.penerbit
             << ", Rak: " << b.rak << ", Status: " << b.status << endl;
        gudangQueue.pop();
    }

    file.close();
    cout << "Data buku berhasil disimpan ke dalam file \"" << filename << "\"." << endl;
}

#endif // CREATE_HPP
