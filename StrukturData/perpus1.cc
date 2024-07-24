#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <string>

using namespace std;

// Konfigurasi database
const char* hostname = "127.0.0.1";  // Alamat IP server database
const char* user = "root";          // Nama pengguna database
const char* pass = "123";           // Kata sandi database
const char* dbname = "perpustakaan";// Nama database
unsigned int port = 31235;          // Port yang digunakan untuk koneksi
const char* unixsocket = NULL;      // Socket Unix (NULL jika tidak digunakan)
unsigned long clientflag = 0;       // Flag client (biasanya 0)

// Fungsi untuk menghubungkan ke database
MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (!conn) {
        cerr << "mysql_init gagal" << endl;
        return nullptr;
    }

    // Menghubungkan ke database
    conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
    if (!conn) {
        cerr << "Koneksi gagal: " << mysql_error(conn) << endl;
    }
    return conn;
}

// Fungsi untuk autentikasi pengguna
bool authenticate_user(const string& username, const string& password, string& role) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "SELECT role FROM users WHERE username = '" << username << "' AND password = '" << password << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "SELECT gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            role = row[0];  // Menyimpan peran pengguna (admin/user)
            mysql_free_result(res);
            mysql_close(conn);
            return true;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
    return false;
}

// Fungsi untuk menambahkan buku ke database
void create_book(const string& title, const string& author, const string& year) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO buku (title, author, year) VALUES ('" + title + "', '" + author + "', '" + year + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil ditambahkan." << endl;
        }
        mysql_close(conn);
    }
}

// Fungsi untuk menampilkan semua buku
void get_books() {
    MYSQL* conn = connect_db();
    if (conn) {
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
        while ((row = mysql_fetch_row(res))) {
            // Menampilkan informasi buku
            cout << "ID: " << row[0] << ", Judul Buku: " << row[1] << ", Penulis: " << row[2] << ", Tahun: " << row[3] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

// Fungsi untuk memperbarui informasi buku
void update_book(int book_id, const string& title, const string& author, const string& year) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE buku SET title = '" << title << "', author = '" << author << "', year = '" << year << "' WHERE id = " << book_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE gagal: " << mysql_error(conn) << endl;
        } else {
            cout << "Buku berhasil diperbarui." << endl;
        }
        mysql_close(conn);
    }
}

// Fungsi untuk menghapus buku dari database
void delete_book(int book_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
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
            string title, author, year;
            cout << "Masukkan judul buku: ";
            cin.ignore();
            getline(cin, title);
            cout << "Masukkan penulis buku: ";
            getline(cin, author);
            cout << "Masukkan tahun terbit buku: ";
            getline(cin, year);
            create_book(title, author, year);
        } else if (choice == 2) {
            get_books();
        } else if (choice == 3) {
            int book_id;
            string title, author, year;
            cout << "Masukkan ID buku yang ingin diperbarui: ";
            cin >> book_id;
            cin.ignore();
            cout << "Masukkan judul baru: ";
            getline(cin, title);
            cout << "Masukkan penulis baru: ";
            getline(cin, author);
            cout << "Masukkan tahun terbit baru: ";
            getline(cin, year);
            update_book(book_id, title, author, year);
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

// Fungsi login untuk autentikasi pengguna
void login() {
    string username, password, role;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if (authenticate_user(username, password, role)) {
        if (role == "admin") {
            admin_menu();
        } else if (role == "user") {
            user_menu();
        } else {
            cout << "Peran tidak valid." << endl;
        }
    } else {
        cout << "Username atau password salah." << endl;
    }
}l

// Fungsi utama untuk menjalankan program
int main() {
    login(); // Memulai program dengan login
    return 0;
}
