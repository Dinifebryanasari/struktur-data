#include <iostream>
#include <mysql/mysql.h>
#include <sstream>

using namespace std;

// Konfigurasi koneksi database
const char* hostname = "127.0.0.1"; // Alamat IP database server
const char* user = "root";          // Nama pengguna database
const char* pass = "123";           // Password pengguna database
const char* dbname = "perpustakaan"; // Nama database yang digunakan
unsigned int port = 31235;           // Port koneksi database
const char* unixsocket = NULL;      // Unix socket (jika diperlukan)
unsigned long clientflag = 0;       // Flag untuk opsi koneksi client

// Fungsi untuk menghubungkan ke database
MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (!conn) {
        cerr << "mysql_init gagal" << endl;
        return nullptr;
    }

    conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
    if (!conn) {
        cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
    }
    return conn;
}

// Fungsi untuk menambahkan buku baru ke dalam database
void create_book(const string& judul, const string& penulis, const string& tahun) {
    MYSQL* conn = connect_db();
    if (conn) {
        // Query SQL untuk menyisipkan data buku baru
        string query = "INSERT INTO buku (judul, penulis, tahun) VALUES ('" + judul + "', '" + penulis + "', '" + tahun + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

// Fungsi untuk menampilkan semua buku dari database
void get_books() {
    MYSQL* conn = connect_db();
    if (conn) {
        // Query SQL untuk mengambil semua data buku
        if (mysql_query(conn, "SELECT * FROM buku")) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        // Tampilkan setiap baris data buku
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Judul: " << row[1] << ", Penulis: " << row[2] << ", Tahun: " << row[3] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

// Fungsi untuk memperbarui data buku berdasarkan ID
void update_book(int book_id, const string& judul, const string& penulis, const string& tahun) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        // Query SQL untuk memperbarui data buku berdasarkan ID
        query << "UPDATE buku SET judul = '" << judul << "', penulis = '" << penulis << "', tahun = '" << tahun << "' WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

// Fungsi untuk menghapus buku berdasarkan ID
void delete_book(int book_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        // Query SQL untuk menghapus buku berdasarkan ID
        query << "DELETE FROM buku WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil dihapus." << endl;
        }
        mysql_close(conn);
    }
}

// Menu untuk admin
void admin_menu() {
    int choice;
    while (true) {
        cout << "\nMenu Admin:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Semua Buku\n";
        cout << "3. Perbarui Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            string judul, penulis, tahun;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, judul);
            cout << "Masukkan penulis buku: ";
            getline(cin, penulis);
            cout << "Masukkan tahun terbit buku: ";
            getline(cin, tahun);
            create_book(judul, penulis, tahun);
        } else if (choice == 2) {
            get_books();
        } else if (choice == 3) {
            int book_id;
            string judul, penulis, tahun;
            cout << "Masukkan ID buku yang ingin diperbarui: ";
            cin >> book_id;
            cin.ignore();
            cout << "Masukkan judul baru: ";
            getline(cin, judul);
            cout << "Masukkan penulis baru: ";
            getline(cin, penulis);
            cout << "Masukkan tahun terbit baru: ";
            getline(cin, tahun);
            update_book(book_id, judul, penulis, tahun);
        } else if (choice == 4) {
            int book_id;
            cout << "Masukkan ID buku yang ingin dihapus: ";
            cin >> book_id;
            delete_book(book_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Menu untuk user
void user_menu() {
    int choice;
    while (true) {
        cout << "\nMenu User:\n";
        cout << "1. Tampilkan Semua Buku\n";
        cout << "2. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> choice;

        if (choice == 1) {
            get_books();
        } else if (choice == 2) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Fungsi utama
int main() {
    int role;
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "Masukkan pilihan: ";
    cin >> role;

    if (role == 1) {
        admin_menu(); // Masuk ke menu admin
    } else if (role == 2) {
        user_menu(); // Masuk ke menu user
    } else {
        cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}
