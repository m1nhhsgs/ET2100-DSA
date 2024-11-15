#include <iostream>
#include <string>
using namespace std;


struct Wood {
    string type;
    int size;
    int age;
    Wood* next;

    Wood(const string& type, int size, int age) 
        : type(type), size(size), age(age), next(nullptr) {}
};


class WoodStack {
private:
    string type;
    Wood* top;

public:
    
    WoodStack(const string& type) : type(type), top(nullptr) {}

    
    ~WoodStack() {
        while (top != nullptr) {
            pop();
        }
    }

    
    void push(int size, int age) {
        Wood* newWood = new Wood(type, size, age);
        newWood->next = top;
        top = newWood;
    }

    
    Wood* pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return nullptr;
        }
        Wood* removedWood = top;
        top = top->next;
        return removedWood;
    }

    
    int countSameAge(int age) const {
        int count = 0;
        Wood* current = top;
        while (current != nullptr) {
            if (current->age == age) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    
    void displayStack() const {
        cout << "Loai go " << type << ":" << endl;
        Wood* current = top;
        while (current != nullptr) {
            cout << "  Do dai: " << current->size << ", Tuoi: " << current->age << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    
    WoodStack GoKeo("Go_Keo");
    WoodStack GoNghien("Go_Nghien");

    
    GoKeo.push(7, 10);
    GoKeo.push(4, 15);
    GoNghien.push(5, 8);
    GoKeo.push(3, 10);


    cout << "Go trong kho:" << endl;
    GoKeo.displayStack();
    GoNghien.displayStack();

    
    cout << "So go co so tuoi la 10 la: " << GoKeo.countSameAge(10) << endl;

    
    Wood* removedWood = GoKeo.pop();
    if (removedWood) {
        cout << "So loai go: Type: " << removedWood->type 
             << ", Size: " << removedWood->size 
             << ", Age: " << removedWood->age << endl;
        delete removedWood;
    }

    
    cout << "\nSo go sau khi lay go la:" << endl;
    GoKeo.displayStack();
    GoNghien.displayStack();

    return 0;
}
