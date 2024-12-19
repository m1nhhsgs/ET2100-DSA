/*Mục lục của một cuốn sách được lưu trữ dưới dạng một cây trong đó mỗi node có thể là chapter, section, subsection, subsubsection.  
Khai báo cấu trúc cây để biểu diễn cuốn sách. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện:  
- Xác định số chương của cuốn sách 
- Tìm chương dài nhất của cuốn sách 
- Thực hiện tìm một mục và xoá mục đó khỏi sách. Lưu ý cập nhật lại số trang của từng mục.  
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum NodeType {
    CHAPTER,
    SECTION,
    SUBSECTION,
    SUBSUBSECTION
};

struct Node {
    string title;
    NodeType type;
    int pageCount;
    Node* parent;
    vector<Node*> children;

    Node(string t, NodeType tp, int pages) : 
        title(t), type(tp), pageCount(pages), parent(nullptr) {}

    void addChild(Node* child) {
        child->parent = this;
        children.push_back(child);
    }

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class BookTree {
private:
    Node* root;
    
    int getTotalChapters(Node* node) const {
        if (!node) return 0;
        int count = (node->type == CHAPTER) ? 1 : 0;
        for (Node* child : node->children) {
            count += getTotalChapters(child);
        }
        return count;
    }

    Node* findLongestChapter(Node* node, Node* &longest) const {
        if (!node) return nullptr;
        
        if (node->type == CHAPTER) {
            if (!longest || node->pageCount > longest->pageCount) {
                longest = node;
            }
        }
        
        for (Node* child : node->children) {
            findLongestChapter(child, longest);
        }
        return longest;
    }

    Node* findSection(Node* node, const string& title) const {
        if (!node) return nullptr;
        if (node->title == title) return node;
        
        for (Node* child : node->children) {
            Node* found = findSection(child, title);
            if (found) return found;
        }
        return nullptr;
    }

    void updatePageNumbers(Node* node, int diff) {
        if (!node) return;
        node->pageCount += diff;
        if (node->parent) {
            updatePageNumbers(node->parent, diff);
        }
    }

public:
    BookTree() : root(nullptr) {}
    ~BookTree() { delete root; }

    void setRoot(Node* node) { root = node; }
    Node* getRoot() const { return root; }
    
    int getChapterCount() const {
        return getTotalChapters(root);
    }

    Node* getLongestChapter() const {
        Node* longest = nullptr;
        return findLongestChapter(root, longest);
    }

    bool deleteSection(const string& title) {
        Node* toDelete = findSection(root, title);
        if (!toDelete) return false;

        Node* parent = toDelete->parent;
        if (!parent) {
            if (toDelete == root) {
                root = nullptr;
                delete toDelete;
                return true;
            }
            return false;
        }

        // Remove from parent's children
        auto it = find(parent->children.begin(), parent->children.end(), toDelete);
        if (it != parent->children.end()) {
            parent->children.erase(it);
        }

        // Update page counts
        updatePageNumbers(parent, -toDelete->pageCount);
        
        delete toDelete;
        return true;
    }
};

int main() {
    // Create a sample book structure
    BookTree book;
    
    Node* chapter1 = new Node("Chapter 1", CHAPTER, 30);
    Node* section11 = new Node("Section 1.1", SECTION, 10);
    Node* section12 = new Node("Section 1.2", SECTION, 20);
    
    Node* chapter2 = new Node("Chapter 2", CHAPTER, 50);
    Node* section21 = new Node("Section 2.1", SECTION, 25);
    Node* section22 = new Node("Section 2.2", SECTION, 25);
    
    // Build the tree
    chapter1->addChild(section11);
    chapter1->addChild(section12);
    chapter2->addChild(section21);
    chapter2->addChild(section22);
    
    Node* root = new Node("Book Title", CHAPTER, 80);
    root->addChild(chapter1);
    root->addChild(chapter2);
    
    book.setRoot(root);
    
    // Test functionalities
    cout << "Total chapters: " << book.getChapterCount() << endl;
    
    Node* longest = book.getLongestChapter();
    if (longest) {
        cout << "Longest chapter: " << longest->title << " (" << longest->pageCount << " pages)" << endl;
    }
    
    // Delete a section
    if (book.deleteSection("Section 1.1")) {
        cout << "Section 1.1 deleted successfully" << endl;
    }
    
    return 0;
}
