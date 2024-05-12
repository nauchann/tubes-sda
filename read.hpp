#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "create.hpp"

using namespace std;

class read {
public:
    static void tampilkanMenu();
    static void tampilkanBukuDariFile(const string& filename);
    static void sortingBukuDariFile(const string& filename);
};

void read::tampilkanMenu() {
    cout << "=== MENU ===\n";
    cout << "1. Tambah buku\n";
    cout << "2. Tampilkan Daftar Buku\n";
    cout << "3. Keluar\n";
    cout << "Pilihan: ";
}

void read::tampilkanBukuDariFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Isi dari file \"" << filename << "\":" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
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
        while (j >= 0 && lines[j].substr(7) > key.substr(7)) {
            lines[j + 1] = lines[j];
            --j;
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

#endif //READ_HPP