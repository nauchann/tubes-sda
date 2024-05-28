#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <algorithm>
#include "create.hpp" // Pastikan create.hpp ada dan tidak memiliki siklus pengiriman

using namespace std;

class read
{
public:
    static void tampilkanMenu();
    static void tampilkanBukuDariFile(const string &filename);
    static void sortingBukuDariFile(const string &filename);
    static void cariBuku(const string &filename, const string &keyword);
    static void filterBukuByGenre(const string &filename, const string &genre);
    static void tampilkanGenre(const string &filename);
    static string toLower(const string &str); // Made static
};

void read::tampilkanMenu()
{
    cout << "=== MENU ===\n";
    cout << "1. Tambah buku\n";
    cout << "2. Tampilkan Daftar Buku\n";
    cout << "3. Cari Buku\n";
    cout << "4. Update Status Buku\n";
    cout << "5. Delete buku\n";
    cout << "6. Filter Buku Berdasarkan Genre\n";
    cout << "7. Keluar\n";
    cout << "Pilihan: ";
}

void read::tampilkanBukuDariFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    string judul, penulis, genre, rak, status;

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

        cout << "Judul\t\t: " << judul << endl;
        cout << "Penulis\t\t: " << penulis << endl;
        cout << "Genre\t\t: " << genre << endl;
        cout << "Rak\t\t: " << rak << endl;
        cout << "Status(Qty)\t: " << status << endl;
        cout << endl;
    }

    file.close();
}

void read::sortingBukuDariFile(const string &filename)
{
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    for (int i = 1; i < lines.size(); ++i)
    {
        string key = lines[i];
        int j = i - 1;
        string keyJudul = key.substr(0, key.find(','));
        // Konversi judul menjadi lowercase
        transform(keyJudul.begin(), keyJudul.end(), keyJudul.begin(), ::tolower);
        while (j >= 0)
        {
            string lineJudul = lines[j].substr(0, lines[j].find(','));
            // Konversi judul yang dibandingkan menjadi lowercase
            transform(lineJudul.begin(), lineJudul.end(), lineJudul.begin(), ::tolower);
            if (lineJudul.compare(keyJudul) > 0)
            {
                lines[j + 1] = lines[j];
                --j;
            }
            else
            {
                break;
            }
        }
        lines[j + 1] = key;
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
}

void read::cariBuku(const string &filename, const string &keyword)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Hasil pencarian untuk \"" << keyword << "\":" << endl;
    string judul, penulis, genre, rak, status;
    bool ditemukan = false;

    string lowerkeyword = toLower(keyword);

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

        string lowerjudul = toLower(judul);
        string lowerpenulis = toLower(penulis);

        if (lowerjudul.find(lowerkeyword) != string::npos || lowerpenulis.find(lowerkeyword) != string::npos)
        {
            cout << "Judul\t\t: " << judul << endl;
            cout << "Penulis\t\t: " << penulis << endl;
            cout << "Genre\t\t: " << genre << endl;
            cout << "Rak\t\t: " << rak << endl;
            cout << "Status(Qty)\t: " << status << endl;
            cout << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
    {
        cout << "Tidak ada buku yang ditemukan dengan kata kunci \"" << keyword << "\"." << endl;
    }

    file.close();
}

void read::tampilkanGenre(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    set<string> genres;
    string judul, penulis, genre, rak, status;

    while (getline(file, judul, ','))
    {
        getline(file, penulis, ',');
        getline(file, genre, ',');
        getline(file, rak, ',');
        getline(file, status);

        genre.erase(0, genre.find_first_not_of(" \t\n\r\f\v"));

        genres.insert(genre);
    }

    file.close();

    cout << "\nGenre yang tersedia:" << endl;
    for (const auto &g : genres)
    {
        cout << g << endl;
    }
    cout << endl;
}

void read::filterBukuByGenre(const string &filename, const string &genre)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Hasil filter untuk genre \"" << genre << "\":" << endl;
    string judul, penulis, genreBuku, rak, status;
    bool ditemukan = false;

    while (getline(file, judul, ','))
    {
        getline(file, penulis, ',');
        getline(file, genreBuku, ',');
        getline(file, rak, ',');
        getline(file, status);

        judul.erase(0, judul.find_first_not_of(" \t\n\r\f\v"));
        penulis.erase(0, penulis.find_first_not_of(" \t\n\r\f\v"));
        genreBuku.erase(0, genreBuku.find_first_not_of(" \t\n\r\f\v"));
        rak.erase(0, rak.find_first_not_of(" \t\n\r\f\v"));
        status.erase(0, status.find_first_not_of(" \t\n\r\f\v"));

        if (toLower(genreBuku) == toLower(genre))
        {
            cout << "Judul\t\t: " << judul << endl;
            cout << "Penulis\t\t: " << penulis << endl;
            cout << "Genre\t\t: " << genreBuku << endl; // Corrected to show genreBuku
            cout << "Rak\t\t: " << rak << endl;
            cout << "Status(Qty)\t: " << status << endl;
            cout << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
    {
        cout << "Tidak ada buku yang ditemukan dengan genre \"" << genre << "\"." << endl;
    }

    file.close();
}

string read::toLower(const std::string &str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c)
              { return tolower(c); });
    return lowerStr;
}

#endif // READ_HPP
