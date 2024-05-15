#ifndef UPDATE_HPP
#define UPDATE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class update {
public:
    static bool findAndShowBook(const string& filename, const string& keyword, string& status);
    static void updateStatusBuku(const string& filename, const string& keyword, const string& newStatus);
};

bool update::findAndShowBook(const string& filename, const string& keyword, string& status) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return false;
    }

    string judul, penulis, genre, rak;
    bool ditemukan = false;

    while (getline(file, judul, ',')) {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        if (judul.find(keyword) != string::npos || penulis.find(keyword) != string::npos) {
            cout << "Judul: " << judul << endl
                 << "Penulis: " << penulis << endl
                 << "Genre: " << genre << endl
                 << "Rak: " << rak << endl
                 << "Status: " << status << endl << endl;
            ditemukan = true;
            break;
        }
    }

    file.close();
    return ditemukan;
}

void update::updateStatusBuku(const string& filename, const string& keyword, const string& newStatus) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    vector<string> lines;
    string judul, penulis, genre, rak, status;
    bool ditemukan = false;

    while (getline(file, judul, ',')) {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        if (judul.find(keyword) != string::npos || penulis.find(keyword) != string::npos) {
            status = newStatus;
            ditemukan = true;
        }

        lines.push_back(judul + ", " + penulis + ", " + genre + ", " + rak + ", " + status);
    }
    file.close();

    if (!ditemukan) {
        cout << "Tidak ada buku yang ditemukan dengan kata kunci \"" << keyword << "\"." << endl;
        return;
    }

    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    for (const string& line : lines) {
        outfile << line << endl;
    }
    outfile.close();

    cout << "Status buku berhasil diperbarui." << endl;
}

#endif //UPDATE_HPP
