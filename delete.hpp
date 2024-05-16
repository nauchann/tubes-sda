#ifndef DELETE_HPP
#define DELETE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void hapusBuku(const string& filename, const string& judul) {
    ifstream fileInput(filename);
    if (!fileInput) {
        cerr << "Gagal membuka file " << filename << " untuk menghapus buku.\n";
        return;
    }

    vector<string> lines;
    string line;

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
        if (l.find(judul) != string::npos) {
            found = true;
            continue; 
        }
        fileOutput << l << "\n";
    }

    if (!found) {
        cerr << "Buku dengan judul '" << judul << "' tidak ditemukan dalam file.\n";
        return;
    }

    cout << "Buku dengan judul '" << judul << "' berhasil dihapus dari file.\n";
    fileOutput.close();
}

#endif // DELETE_HPP
