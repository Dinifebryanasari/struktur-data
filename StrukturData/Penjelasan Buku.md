Berikut adalah penjelasan lengkap yang telah dirapikan dan siap untuk diunggah ke GitHub melalui VSCode:

---

# Program Stack Buku dengan C++

Program ini adalah implementasi sederhana dari tumpukan (stack) buku menggunakan C++. Program ini menyediakan beberapa operasi dasar seperti menambahkan buku, menghapus buku teratas, melihat buku teratas, memeriksa apakah tumpukan kosong, dan mengetahui jumlah buku di tumpukan.

## Header Files

```cpp
#include <iostream>     // Header ini diperlukan untuk menggunakan objek input dan output standar seperti cin dan cout.
#include <stack>        // Header ini digunakan untuk menggunakan kelas stack dari pustaka standar C++.
#include <string>       // Header ini digunakan untuk manipulasi string di C++.
```

- **`#include <iostream>`**: Digunakan untuk operasi input dan output standar. Memungkinkan penggunaan `cin` untuk input dan `cout` untuk output.
- **`#include <stack>`**: Memungkinkan penggunaan kelas `stack` dari pustaka standar C++. `stack` adalah struktur data LIFO (Last In First Out).
- **`#include <string>`**: Menyediakan kelas `string` untuk manipulasi teks.

## Namespace

```cpp
using namespace std;    // Menggunakan namespace standar C++ agar tidak perlu menulis std:: sebelum setiap penggunaan objek dari standar library.
```

- **`using namespace std;`**: Mempermudah penggunaan elemen dari pustaka standar C++ tanpa perlu menambahkan `std::` di depan setiap elemen.

## Fungsi `push`

```cpp
void push(stack<string>& books) {
    cin.ignore();               // membersihkan buffer input
    string book;
    getline(cin, book);         // membaca satu baris input yang berisi judul buku
    books.push(book);           // menambahkan buku ke tumpukan
}
```

- **`void push(stack<string>& books)`**: Fungsi untuk menambahkan buku ke tumpukan.
  - **`cin.ignore()`**: Membersihkan buffer input untuk memastikan tidak ada karakter tersisa yang bisa mengganggu input berikutnya.
  - **`getline(cin, book)`**: Membaca satu baris input dari pengguna yang berisi judul buku dan menyimpannya dalam variabel `book`.
  - **`books.push(book)`**: Menambahkan judul buku ke tumpukan `books`.

## Fungsi `pop`

```cpp
void pop(stack<string>& books) {
    if (!books.empty()) {       // memeriksa apakah tumpukan kosong
        cout << "Removing: " << books.top() << endl; // mengakses buku teratas tanpa menghapusnya
        books.pop();            // menghapus buku teratas dari tumpukan
    } else {
        cout << "The stack is empty." << endl;
    }
}
```

- **`void pop(stack<string>& books)`**: Fungsi untuk menghapus buku teratas dari tumpukan.
  - **`if (!books.empty())`**: Memeriksa apakah tumpukan tidak kosong.
  - **`cout << "Removing: " << books.top() << endl;`**: Menampilkan buku teratas yang akan dihapus.
  - **`books.pop()`**: Menghapus buku teratas dari tumpukan.
  - **`else` block**: Menampilkan pesan bahwa tumpukan kosong jika tidak ada buku di tumpukan.

## Fungsi `peek`

```cpp
void peek(const stack<string>& books) {
    if (!books.empty()) {       // memeriksa apakah tumpukan kosong
        cout << "Top book: " << books.top() << endl; // mengakses buku teratas tanpa menghapusnya
    } else {
        cout << "The stack is empty." << endl;
    }
}
```

- **`void peek(const stack<string>& books)`**: Fungsi untuk melihat buku teratas di tumpukan tanpa menghapusnya.
  - **`if (!books.empty())`**: Memeriksa apakah tumpukan tidak kosong.
  - **`cout << "Top book: " << books.top() << endl;`**: Menampilkan buku teratas.
  - **`else` block**: Menampilkan pesan bahwa tumpukan kosong jika tidak ada buku di tumpukan.

## Fungsi `isEmpty`

```cpp
void isEmpty(const stack<string>& books) {
    if (books.empty()) {        // memeriksa apakah tumpukan kosong
        cout << "The stack is empty." << endl;
    } else {
        cout << "The stack is not empty." << endl;
    }
}
```

- **`void isEmpty(const stack<string>& books)`**: Fungsi untuk memeriksa apakah tumpukan kosong.
  - **`if (books.empty())`**: Memeriksa apakah tumpukan kosong dan menampilkan pesan yang sesuai.
  - **`else` block**: Menampilkan pesan bahwa tumpukan tidak kosong jika terdapat buku di tumpukan.

## Fungsi `size`

```cpp
void size(const stack<string>& books) {
    cout << "Stack size: " << books.size() << endl; // mengembalikan jumlah elemen di tumpukan
}
```

- **`void size(const stack<string>& books)`**: Fungsi untuk mengetahui jumlah buku di tumpukan.
  - **`cout << "Stack size: " << books.size() << endl;`**: Menampilkan jumlah buku di tumpukan.

## Fungsi `main`

```cpp
int main() {
    stack<string> books;        // Menginisialisasi sebuah tumpukan buku
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push a book\n";
        cout << "2. Pop a book\n";
        cout << "3. Peek at the top book\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Get stack size\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: push(books); break;
            case 2: pop(books); break;
            case 3: peek(books); break;
            case 4: isEmpty(books); break;
            case 5: size(books); break;
            case 6: cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
    } while (choice != 6);

    return 0;
}
```

- **`int main()`**: Fungsi utama yang menjalankan program.
  - **`stack<string> books;`**: Menginisialisasi sebuah tumpukan untuk menyimpan buku.
  - **`int choice;`**: Variabel untuk menyimpan pilihan pengguna.
  - **`do-while` loop**: Menyediakan menu interaktif yang terus berjalan hingga pengguna memilih untuk keluar.
    - **`cout << ...`**: Menampilkan menu pilihan kepada pengguna.
    - **`cin >> choice;`**: Menerima input pilihan dari pengguna.
    - **`switch (choice)`**: Memanggil fungsi yang sesuai berdasarkan pilihan pengguna:
      - **case 1**: Memanggil fungsi `push` untuk menambahkan buku.
      - **case 2**: Memanggil fungsi `pop` untuk menghapus buku teratas.
      - **case 3**: Memanggil fungsi `peek` untuk melihat buku teratas.
      - **case 4**: Memanggil fungsi `isEmpty` untuk memeriksa apakah tumpukan kosong.
      - **case 5**: Memanggil fungsi `size` untuk mengetahui jumlah buku di tumpukan.
      - **case 6**: Menampilkan pesan keluar dan mengakhiri loop.
      - **default**: Menampilkan pesan jika pilihan tidak valid.
  - **`while (choice != 6);`**: Kondisi untuk terus menjalankan loop selama pilihan bukan 6.