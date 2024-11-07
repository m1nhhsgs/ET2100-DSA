/* Cài đặt giải thuật để nhập và in ra hai đa thức theo định dạng như sau:
f(x) = x^10 + 1;
g(x) = x^15 + x^7 + x^2 + 1; 
In ra tổng của 2 đa thức h(x) = f(x) + g(x) (*)
Ưu tiên cài đặt CTDL và giải thuật để sử dụng bộ nhớ tối ưu nhất  */
#include <iostream>

using namespace std;

struct Node{
    int data;
    int power;
    Node* next;
};

typedef Node* Polynomial;
Node* createNode(int x, int y){
    Node* p = new Node;
    p->data = x;
    p->power = y;
    p->next = NULL;
    return p;
}

void insertTail(Node* &head, int x, int y){
    Node* p = createNode(x, y);
    if (head == NULL){
        head = p;
        return;
    }
    Node* q = head;
    while (q->next != NULL){
        q = q->next;
    }
    q->next = p;
}

void printPolynomial(Polynomial head){
    Polynomial p = head;
    while (p != NULL){
        if (p->data )
    }
}


int main(){

}