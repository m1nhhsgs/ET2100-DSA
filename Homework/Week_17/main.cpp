/*Cài đặt cây AVL với các hàm theo yêu cầu sau:
- Khai báo cấu trúc cây AVL
- Cài đặt hàm thực hiện các phép xoay đơn, xoay kép để cân bằng cây 
- Cài đặt hàm bổ sung thêm một node mới trên cây AVL 
- Sử dụng mảng cho trên lớp để làm bộ kiểm tra đầu vào, in ra cây AVL theo từng bước bổ sung thêm phân tử theo các phép duyệt cây */

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

public:
    AVLTree() : root(nullptr) {}

    void insertKey(int key) {
        root = insert(root, key);
        cout << "\nAfter inserting " << key << ":\n";
        cout << "Inorder: ";   printInorder();
        cout << "\nPreorder: "; printPreorder();
        cout << "\nPostorder: "; printPostorder();
        cout << "\n";
    }

    void printInorder() { inorder(root); }
    void printPreorder() { preorder(root); }
    void printPostorder() { postorder(root); }
};

int main() {
    AVLTree tree;
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < n; i++) {
        tree.insertKey(arr[i]);
    }

    return 0;
}