/* Cài đặt giải thuật để nhập và in ra hai đa thức theo định dạng như sau:
f(x) = x^10 + 1;
g(x) = x^15 + x^7 + x^2 + 1; 
In ra tổng của 2 đa thức h(x) = f(x) + g(x) (*)
Ưu tiên cài đặt CTDL và giải thuật để sử dụng bộ nhớ tối ưu nhất  */
#include <iostream>

using namespace std;

struct Node{
    int coef;
    int power;
    Node* next;
};

typedef Node* Polynomial;

//Cac node ma co coef = 0 hoac cac node co cung power, tong cac coef = 0 thi se khong hien thi, bi xoa khoi bo nho

void inputPolynomial(Polynomial &p){
    int n;
    cout << "Nhap so luong node: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        int coef, power;
        cout << "Nhap he so: ";
        cin >> coef;
        cout << "Nhap so mu: ";
        cin >> power;
        if(coef != 0){
            Node* temp = new Node;
            temp->coef = coef;
            temp->power = power;
            temp->next = NULL;
            if(p == NULL){
                p = temp;
            }
            else{
                Node* last = p;
                while(last->next != NULL){
                    last = last->next;
                }
                last->next = temp;
            }
        }
    }
}

//Ham in da thuc, neu he so am thi in ra dau tru, neu he so la 1 thi khong in ra he so, neu he so la 0 thi khong in ra node do
void printPolynomial(Polynomial p){
    Node* temp = p;
    while(temp != NULL){
        cout << temp->coef << "x^" << temp->power;
        if(temp->next != NULL){
            cout << " + ";
        }
        temp = temp->next;
    }
    cout << endl;
}

//Ham tinh tong cua 2 da thuc, cong cac he so cung so mu
Polynomial sumPolynomial(Polynomial f, Polynomial g){
    Polynomial h = NULL;
    Node* temp1 = f;
    Node* temp2 = g;
    while(temp1 != NULL && temp2 != NULL){
        if(temp1->power == temp2->power){
            Node* temp = new Node;
            temp->coef = temp1->coef + temp2->coef;
            temp->power = temp1->power;
            temp->next = NULL;
            if(h == NULL){
                h = temp;
            }
            else{
                Node* last = h;
                while(last->next != NULL){
                    last = last->next;
                }
                last->next = temp;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1->power > temp2->power){
            Node* temp = new Node;
            temp->coef = temp1->coef;
            temp->power = temp1->power;
            temp->next = NULL;
            if(h == NULL){
                h = temp;
            }
            else{
                Node* last = h;
                while(last->next != NULL){
                    last = last->next;
                }
                last->next = temp;
            }
            temp1 = temp1->next;
        }
        else{
            Node* temp = new Node;
            temp->coef = temp2->coef;
            temp->power = temp2->power;
            temp->next = NULL;
            if(h == NULL){
                h = temp;
            }
            else{
                Node* last = h;
                while(last->next != NULL){
                    last = last->next;
                }
                last->next = temp;
            }
            temp2 = temp2->next;
        }
    }
    while(temp1 != NULL){
        Node* temp = new Node;
        temp->coef = temp1->coef;
        temp->power = temp1->power;
        temp->next = NULL;
        if(h == NULL){
            h = temp;
        }
        else{
            Node* last = h;
            while(last->next != NULL){
                last = last->next;
            }
            last->next = temp;
        }
        temp1 = temp1->next;
    }
    while(temp2 != NULL){
        Node* temp = new Node;
        temp->coef = temp2->coef;
        temp->power = temp2->power;
        temp->next = NULL;
        if(h == NULL){
            h = temp;
        }
        else{
            Node* last = h;
            while(last->next != NULL){
                last = last->next;
            }
            last->next = temp;
        }
        temp2 = temp2->next;
    }
    return h;
}


int main(){
    Polynomial f = NULL;
    Polynomial g = NULL;
    Polynomial h = NULL;
    cout << "Nhap da thuc f(x): " << endl;
    inputPolynomial(f);
    cout << "Nhap da thuc g(x): " << endl;
    inputPolynomial(g);
    cout << "Da thuc f(x): ";
    printPolynomial(f);
    cout << "Da thuc g(x): ";
    printPolynomial(g);
    h = sumPolynomial(f, g);
    cout << "Da thuc h(x) = f(x) + g(x): ";
    printPolynomial(h);
    return 0;
}