#ifndef DELETE_HPP
#define DELETE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "read.hpp" // Pastikan read.hpp di-include untuk menggunakan fungsi toLower

using namespace std;

class del {
public:
    static void hapusBuku(const string& filename, const string& judul);
};

void del::hapusBuku(const string& filename, const string& judul) {
    ifstream fileInput(filename);
    if (!fileInput) {
        cerr << "Gagal membuka file " << filename << " untuk menghapus buku.\n";
        return;
    }

    vector<string> lines;
    string line;
    string lowerJudul = read::toLower(judul); // Menggunakan fungsi toLower dari kelas read

    while (getline(fileInput, line)) {
        lines.push_back(line);
    }

    fileInput.close();

    ofstream fileOutput(filename);
    if (!fileOutput) {
        cerr << "Gagal membuka file " << filename << " untuk menghapus buku.\n";
        return;
    }

    bool found = false;
    for (const auto& l : lines) {
        size_t pos = l.find(',');
        if (pos != string::npos) {
            string judulBuku = l.substr(0, pos);
            if (read::toLower(judulBuku) == lowerJudul) {
                found = true;
                continue; 
            }
        }
        fileOutput << l << "\n";
    }

    if (!found) {
        cerr << "Buku dengan judul '" << judul << "' tidak ditemukan dalam file.\n";
    } else {
        cout << "Buku dengan judul '" << judul << "' berhasil dihapus dari file.\n";
    }

    fileOutput.close();
}

#endif // DELETE_HPP
