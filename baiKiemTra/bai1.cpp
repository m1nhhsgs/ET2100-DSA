#include <iostream>
#include <cstring>
using namespace std;

struct Ngay {
    int ngay;
    int thang;
    int nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct List {
    Node* first;
    Node* last;
};

//Tao list rong
void initList(List &list) {
    list.first = list.last = NULL;
}

//Tao node
Node* createNode(SinhVien sv) {
    Node* node = new Node;
    node->data = sv;
    node->link = NULL;
    return node;
}

//Chen node vao vi tri co thu tu
void insertSorted(List &list, SinhVien sv) {
    Node* node = createNode(sv);
    if (list.first == NULL || strcmp(list.first->data.maSV, sv.maSV) > 0) {
        node->link = list.first; 
        list.first = node;
        if (list.last == NULL) list.last = node;
    } else {
        Node* p = list.first;
        while (p->link != NULL && strcmp(p->link->data.maSV, sv.maSV) < 0) {
            p = p->link;
        }
        node->link = p->link;
        p->link = node;
        if (node->link == NULL) list.last = node;
    }
}

void inputSinhVien(SinhVien &sv) {
    cout << "Nhap ma SV: "; cin >> sv.maSV;
    cout << "Nhap ho ten: "; cin.ignore(); cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): "; cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh (ngay thang nam): "; cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Nhap dia chi: "; cin.ignore(); cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: "; cin >> sv.lop;
    cout << "Nhap khoa: "; cin >> sv.khoa;
}

void printList(const List &list) {
    Node* p = list.first;
    while (p != NULL) {
        cout << p->data.maSV << " - " << p->data.hoTen << " - " << p->data.gioiTinh << " - "
             << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << " - "
             << p->data.diaChi << " - " << p->data.lop << " - " << p->data.khoa << endl;
        p = p->link;
    }
}

void findSameBirthDate(const List &list, Ngay date) {
    Node* p = list.first;
    bool found = false;
    while (p != NULL) {
        if (p->data.ngaySinh.ngay == date.ngay && p->data.ngaySinh.thang == date.thang && p->data.ngaySinh.nam == date.nam) {
            cout << p->data.maSV << " - " << p->data.hoTen << endl;
            found = true;
        }
        p = p->link;
    }
    if (!found) {
        cout << "khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

void removeSameBirthDate(List &list, Ngay date) {
    Node* p = list.first;
    Node* prev = NULL;
    while (p != NULL) {
        if (p->data.ngaySinh.ngay == date.ngay && p->data.ngaySinh.thang == date.thang && p->data.ngaySinh.nam == date.nam) {
            if (prev == NULL) {
                list.first = p->link;
            } else {
                prev->link = p->link;
            }
            Node* temp = p;
            p = p->link;
            delete temp;
        } else {
            prev = p;
            p = p->link;
        }
    }
}

int main() {
    List ListSV;
    initList(ListSV);
    SinhVien sv;
    cout << "Nhap so sinh vien: ";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        inputSinhVien(sv);
        insertSorted(ListSV, sv);
    }
    cout << "Danh sach sinh vien: " << endl;
    printList(ListSV);

    Ngay date;
    cout << "Nhap ngay sinh de tim sinh vien (ngay thang nam): ";
    cin >> date.ngay >> date.thang >> date.nam;
    cout << "Sinh vien cung ngay sinh: " << endl;
    findSameBirthDate(ListSV, date);

    cout << "Loai bo sinh vien cung ngay sinh: " << endl;
    removeSameBirthDate(ListSV, date);
    printList(ListSV);

    return 0;
}