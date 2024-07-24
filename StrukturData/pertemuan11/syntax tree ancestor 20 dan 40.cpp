#include <iostream>
using namespace std;

// Definisi struktur node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Fungsi untuk menambahkan node baru ke tree
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }

    return root;
}

// Fungsi untuk mencari common ancestor dari dua node
Node* findCommonAncestor(Node* root, int n1, int n2) {
    if (root == nullptr) return nullptr;

    // Jika salah satu nilai adalah root, maka root adalah ancestor bersama
    if (root->data == n1 || root->data == n2) return root;

    // cari ancestor di sub-tree kiri dan kanan
    Node* left = findCommonAncestor(root->left, n1, n2);
    Node* right = findCommonAncestor(root->right, n1, n2);

    // Jika n1 dan n2 ditemukan di sub-tree kiri dan kanan, maka root adalah ancestor bersama
    if (left != nullptr && right != nullptr) return root;

    // Jika tidak ditemukan di kedua sub-tree
    return (left != nullptr) ? left : right;
}

// Fungsi utama
int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    int n1 = 20, n2 = 40;
    Node* ancestor = findCommonAncestor(root, n1, n2);

    if (ancestor != nullptr) {
        cout << "Common ancestor of " << n1 << " and " << n2 << " is: " << ancestor->data << endl;
    } else {
        cout << "No common ancestor found." << endl;
    }

    return 0;
}
