/*Quản lý sinh viên 1 trường đại học dùng Linked List*/

#include <iostream>
#include <fstream>
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

typedef Node* ListSV;

/*2. Nhập vào Danh sách sinh viên ListSV, và in ra Danh sách sinh viên được sắp xếp tăng dần theo mã sinh viên. 
Hãy viết hàm thêm một sinh viên mới vào danh sách ListSV đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới.*/

ListSV createNode(SinhVien x) {
    Node* p = new Node;
    p->data = x;
    p->link = NULL;
    return p;
}

//Thêm một Node và cuối danh sách
void insertTail(ListSV &head, SinhVien &x) {
    Node* p = createNode(x);
    if (head == NULL) {
        head = p;
    } else {
        Node* q = head;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = p;
    }
}

void read_CSV(){
    ifstream file ("data.csv");
    
    if (!file.is_open()) {
        cout << "Khong the mo file" << endl;
        return;
    }
    SinhVien sv;
    ListSV head = NULL;
    while (!file.eof()) {
        file.getline(sv.maSV, 8, ',');
        file.getline(sv.hoTen, 50, ',');
        file >> sv.gioiTinh;
        file.ignore();
        file >> sv.ngaySinh.ngay;
        file.ignore();
        file >> sv.ngaySinh.thang;
        file.ignore();
        file >> sv.ngaySinh.nam;
        file.ignore();
        file.getline(sv.diaChi, 100, ',');
        file.getline(sv.lop, 12, ',');
        file.getline(sv.khoa, 7);
        insertTail(head, sv);
    }

}

//QuickSort sinh viên theo mã sinh viên

void partition(ListSV &head, ListSV &head1, ListSV &head2) {
    Node* p = head;
    while (p != NULL) {
        if (p->data.maSV[0] == 'A') {
            insertTail(head1, p->data);
        } else {
            insertTail(head2, p->data);
        }
        p = p->link;
    }
}

void quickSort(ListSV &head) {
    if (head == NULL || head->link == NULL) {
        return;
    }
    ListSV head1 = NULL, head2 = NULL;
    partition(head, head1, head2);
    quickSort(head1);
    quickSort(head2);
    if (head1 == NULL) {
        head = head2;
    } else {
        head = head1;
        Node* p = head1;
        while (p->link != NULL) {
            p = p->link;
        }
        p->link = head2;
    }
}

void printList(ListSV head) {
    Node* p = head;
    while (p != NULL) {
        cout << p->data.maSV << " " << p->data.hoTen << " " << p->data.gioiTinh << " " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << " " << p->data.diaChi << " " << p->data.lop << " " << p->data.khoa << endl;
        p = p->link;
    }
}

int main() {
    SinhVien sv;
    ListSV head = NULL;
    read_CSV();
    quickSort(head);
    printList(head);
    return 0;
}

