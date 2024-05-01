#include "create.hpp"
#include "read.hpp"

using namespace std;

int main() {
    vector<vector<create::buku>> gudang;

    int pilihan;
    do {
        read::tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                create tambah;
                tambah.tambahbuku(gudang);
                break;
            case 2:
                read::tampilkanGudang(gudang);
                break;
            case 3:
                cout << "Terima kasih telah menggunakan program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 3);

    return 0;
}
