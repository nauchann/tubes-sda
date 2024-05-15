#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "create.hpp"
#include "read.hpp"
#include "update.hpp"

using namespace std;

class read {
public:
    static void tampilkanMenu();
    static void tampilkanBukuDariFile(const string& filename);
    static void sortingBukuDariFile(const string& filename);
    static void cariBuku(const string& filename, const string& keyword);
    static void updateStatus(const string& filename);
};

void read::tampilkanMenu() {
    cout << "=== MENU ===\n";
    cout << "1. Tambah buku\n";
    cout << "2. Tampilkan Daftar Buku\n";
    cout << "3. Cari Buku\n";
    cout << "4. Update Status Buku\n";
    cout << "5. Keluar\n";
    cout << "Pilihan: ";
}

void read::tampilkanBukuDariFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Isi dari file \"" << filename << "\":" << endl;
    string judul, penulis, genre, rak, status;

    while (getline(file, judul, ',')) {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        // Menghapus spasi tambahan setelah koma
        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        cout << "Judul: " << judul << endl;
        cout << "Penulis: " << penulis << endl;
        cout << "Genre: " << genre << endl;
        cout << "Rak: " << rak << endl;
        cout << "Status: " << status << endl;
        cout << endl;
    }

    file.close();
}

void read::sortingBukuDariFile(const string& filename) {
    // Baca data dari file ke dalam vektor
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Lakukan pengurutan berdasarkan abjad judul buku menggunakan insertion sort
    for (int i = 1; i < lines.size(); ++i) {
        string key = lines[i];
        int j = i - 1;
        string keyJudul = key.substr(0, key.find(',')); // Ambil bagian judul dari key
        while (j >= 0) {
            string lineJudul = lines[j].substr(0, lines[j].find(',')); // Ambil bagian judul dari lines[j]
            if (lineJudul.compare(keyJudul) > 0) {
                lines[j + 1] = lines[j];
                --j;
            } else {
                break;
            }
        }
        lines[j + 1] = key;
    }

    // Tulis kembali data yang sudah diurutkan ke dalam file
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    for (const string& line : lines) {
        outfile << line << endl;
    }
    outfile.close();

    cout << "Data buku berhasil diurutkan dan disimpan ke dalam file \"" << filename << "\"." << endl;
    
}

void read::cariBuku(const string& filename, const string& keyword) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Hasil pencarian untuk \"" << keyword << "\":" << endl;
    string judul, penulis, genre, rak, status;
    bool ditemukan = false;

    while (getline(file, judul, ',')) {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        // Menghapus spasi tambahan setelah koma
        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        if (judul.find(keyword) != string::npos || penulis.find(keyword) != string::npos) {
            cout << "Judul: " << judul << endl;
            cout << "Penulis: " << penulis << endl;
            cout << "Genre: " << genre << endl;
            cout << "Rak: " << rak << endl;
            cout << "Status: " << status << endl;
            cout << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada buku yang ditemukan dengan kata kunci \"" << keyword << "\"." << endl;
    }

    file.close();
}

void read::updateStatus(const string& filename) {
    string keyword, newStatus;
    cout << "Masukkan kata kunci untuk mencari buku yang akan diperbarui statusnya: ";
    cin.ignore();
    getline(cin, keyword);

    string status;
    bool ditemukan = update::findAndShowBook(filename, keyword, status);
    if (ditemukan) {
        cout << "Masukkan status baru untuk buku: ";
        getline(cin, newStatus);
        update::updateStatusBuku(filename, keyword, newStatus);
    } else {
        cout << "Buku tidak ditemukan, status tidak dapat diperbarui." << endl;
    }
}

#endif //READ_HPP