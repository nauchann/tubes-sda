#ifndef UPDATE_HPP
#define UPDATE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "read.hpp" // Pastikan read.hpp di-include untuk menggunakan fungsi toLower

using namespace std;

class update
{
public:
    static bool findAndShowBook(const string &filename, const string &keyword, string &status);
    static void updateStatusBuku(const string &filename, const string &keyword, const string &newStatus);
    static void updateStatus(const string &filename);
};

bool update::findAndShowBook(const string &filename, const string &keyword, string &status)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return false;
    }

    string judul, penulis, genre, rak;
    bool ditemukan = false;
    string lowerKeyword = read::toLower(keyword); // Menggunakan fungsi toLower dari kelas read

    while (getline(file, judul, ','))
    {
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

        if (read::toLower(judul).find(lowerKeyword) != string::npos || read::toLower(penulis).find(lowerKeyword) != string::npos)
        {
            cout << "Judul\t\t: " << judul << endl;
            cout << "Penulis\t\t: " << penulis << endl;
            cout << "Genre\t\t: " << genre << endl;
            cout << "Rak\t\t: " << rak << endl;
            cout << "Status(Qty)\t: " << status << endl;
            cout << endl;
            ditemukan = true;
            break;
        }
    }

    file.close();
    return ditemukan;
}

void update::updateStatusBuku(const string &filename, const string &keyword, const string &newStatus)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    vector<string> lines;
    string judul, penulis, genre, rak, status;
    bool ditemukan = false;
    string lowerKeyword = read::toLower(keyword); // Menggunakan fungsi toLower dari kelas read

    while (getline(file, judul, ','))
    {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        if (read::toLower(judul).find(lowerKeyword) != string::npos || read::toLower(penulis).find(lowerKeyword) != string::npos)
        {
            status = newStatus;
            ditemukan = true;
        }

        lines.push_back(judul + ", " + penulis + ", " + genre + ", " + rak + ", " + status);
    }
    file.close();

    if (!ditemukan)
    {
        cout << "Tidak ada buku yang ditemukan dengan kata kunci \"" << keyword << "\"." << endl;
        return;
    }

    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    for (const string &line : lines)
    {
        outfile << line << endl;
    }
    outfile.close();

    cout << "Status buku berhasil diperbarui." << endl;
}

void update::updateStatus(const string &filename)
{
    string keyword, newStatus;
    cout << "Masukkan kata kunci untuk mencari buku yang akan diperbarui statusnya: ";
    cin.ignore();
    getline(cin, keyword);

    string status;
    bool ditemukan = update::findAndShowBook(filename, keyword, status);
    if (ditemukan)
    {
        cout << "Masukkan status baru untuk buku: ";
        getline(cin, newStatus);
        update::updateStatusBuku(filename, keyword, newStatus);
    }
    else
    {
        cout << "Buku tidak ditemukan, status tidak dapat diperbarui." << endl;
    }
}

#endif // UPDATE_HPP
