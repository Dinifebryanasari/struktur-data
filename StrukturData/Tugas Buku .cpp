#include <iostream>  // Untuk input dan output
#include <stack>     // Untuk menggunakan stack
#include <string>    // Untuk manipulasi string

using namespace std;

// Fungsi untuk menambahkan buku ke tumpukan
void push(stack<string>& books) {
    string book;
    cout << "Masukkan judul buku yang akan ditambahkan: ";
    cin.ignore();  // Membersihkan buffer input
    getline(cin, book);  // Membaca judul buku
    books.push(book);  // Menambahkan buku ke tumpukan
    cout << "Buku \"" << book << "\" telah ditambahkan ke tumpukan." << endl;
}

// Fungsi untuk menghapus buku teratas dari tumpukan
void pop(stack<string>& books) {
    if (books.empty()) {  // Memeriksa apakah tumpukan kosong
        cout << "Tumpukan buku kosong. Tidak ada buku yang bisa dihapus." << endl;
    } else {
        cout << "Buku \"" << books.top() << "\" telah dihapus dari tumpukan." << endl;
        books.pop();  // Menghapus buku teratas dari tumpukan
    }
}

// Fungsi untuk melihat buku teratas di tumpukan tanpa menghapusnya
void peek(const stack<string>& books) {
    if (books.empty()) {  // Memeriksa apakah tumpukan kosong
        cout << "Tumpukan buku kosong." << endl;
    } else {
        cout << "Buku teratas di tumpukan: \"" << books.top() << "\"" << endl;
    }
}

// Fungsi untuk memeriksa apakah tumpukan kosong
void isEmpty(const stack<string>& books) {
    if (books.empty()) {
        cout << "Tumpukan buku kosong." << endl;
    } else {
        cout << "Tumpukan buku tidak kosong." << endl;
    }
}

// Fungsi untuk mengetahui jumlah buku di tumpukan
void size(const stack<string>& books) {
    cout << "Jumlah buku di tumpukan: " << books.size() << endl;
}

int main() {
    stack<string> books;  // Deklarasi tumpukan buku
    string command;
    
    // Loop untuk menjalankan program
    while (true) {
        cout << "\nPilih operasi (1: push, 2: pop, 3: peek, 4: isEmpty, 5: size): ";
        cin >> command;

        // Menjalankan fungsi yang sesuai berdasarkan input pengguna
        if (command == "1" || command == "push") {
            push(books);
        } else if (command == "2" || command == "pop") {
            pop(books);
        } else if (command == "3" || command == "peek") {
            peek(books);
        } else if (command == "4" || command == "isEmpty") {
            isEmpty(books);
        } else if (command == "5" || command == "size") {
            size(books);
        } else {
            cout << "Perintah tidak dikenal. Silakan coba lagi." << endl;
        }
    }
    
    return 0;
}
