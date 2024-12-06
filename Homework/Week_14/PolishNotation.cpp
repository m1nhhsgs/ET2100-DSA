#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;
    
    Node(string value) {
        data = value;
        left = right = nullptr;
    }
};

// Checks if token is an operator
bool isOperator(string token) {
    return (token == "+" || token == "-" || token == "*" || 
            token == "/" || token == "^");
}

int getOperatorPrecedence(const string& op) {
    if (op == "^") return 3;
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// Builds tree from Polish Notation tokens
Node* buildTree(string tokens[], int& index, int size) {
    if (index >= size)
        return nullptr;
        
    Node* root = new Node(tokens[index]);
    
    if (isOperator(tokens[index])) {
        index++;
        root->left = buildTree(tokens, index, size);
        index++;
        root->right = buildTree(tokens, index, size);
    }
    
    return root;
}

// Preorder traversal (Root-Left-Right)
void preOrder(Node* root) {
    if (root == nullptr)
        return;
        
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Inorder traversal (Left-Root-Right)
void inOrder(Node* root) {
    if (root == nullptr)
        return;
        
    if (isOperator(root->data)) cout << "(";
    inOrder(root->left);
    cout << root->data;
    inOrder(root->right);
    if (isOperator(root->data)) cout << ")";
}

// Postorder traversal (Left-Right-Root)
void postOrder(Node* root) {
    if (root == nullptr)
        return;
        
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

int getHeight(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

void printLevel(Node* root, int level, int space) {
    if (root == nullptr) return;
    if (level == 1) {
        cout << setw(space) << root->data;
    }
    else if (level > 1) {
        printLevel(root->left, level - 1, space);
        printLevel(root->right, level - 1, space);
    }
}

void printTree(Node* root) {
    int h = getHeight(root);
    int space = 5;
    
    for (int i = 1; i <= h; i++) {
        cout << string(space * (h - i), ' ');
        printLevel(root, i, space * (1 << (i-1)));
        cout << endl;
        
        if (i < h) {
            cout << string(space * (h - i), ' ');
            for (int j = 1; j <= (1 << (i-1)); j++) {
                if (j % 2 == 1) cout << string(space-1, ' ') << "/" << string(space-1, ' ');
                else cout << "\\" << string(space-1, ' ');
            }
            cout << endl;
        }
    }
}

int main() {
    // Polish Notation for: a + 5 * b / c - c ^ 8 + d * e ^ 2
    string expr[] = {"+", "+", "-", "+", "a", "*", "5", "/", "b", "c", 
                    "^", "c", "8", "*", "d", "^", "e", "2"};
    int size = sizeof(expr)/sizeof(expr[0]);
    int index = 0;
    
    Node* root = buildTree(expr, index, size);
    
    cout << "Preorder traversal: ";
    preOrder(root);
    cout << "\n\nInorder traversal: ";
    inOrder(root);
    cout << "\n\nPostorder traversal: ";
    postOrder(root);
    cout << endl;
   
    return 0;
}
