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

ListSV createNode(SinhVien x) {
    Node* p = new Node;
    p->data = x;
    p->link = NULL;
    return p;
}

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

void readCSV(ListSV &head) {
    ifstream fileIn("D:/Project/ET2100-DSA/baiKiemTra/Bai1/data.csv", ios::in);
    if (fileIn.fail()) {
        cout << "File khong ton tai";
        return;
    }
    while (!fileIn.eof()) {
        SinhVien sv;
        fileIn.getline(sv.maSV, 8, ',');
        fileIn.getline(sv.hoTen, 50, ',');
        fileIn >> sv.gioiTinh;
        fileIn.ignore();
        char ngaySinh[11];
        fileIn.getline(ngaySinh, 11, ',');
        sscanf(ngaySinh, "%d/%d/%d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);

        fileIn.getline(sv.diaChi, 100, ',');
        fileIn.getline(sv.lop, 12, ',');
        fileIn.getline(sv.khoa, 7, '\n');
        insertTail(head, sv);
    }
    fileIn.close();
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

Node* partition(ListSV low, ListSV high) {
    SinhVien pivot = high->data;
    ListSV i = low;

    for (ListSV j = low; j != high; j = j->link) {
        if (strcmp(j->data.maSV, pivot.maSV) < 0) {
            swap(i->data, j->data);
            i = i->link;
        }
    }
    swap(i->data, high->data);
    return i;
}

void quickSort(ListSV low, ListSV high) {
    if (low != NULL && high != NULL && low != high && low != high->link) {
        ListSV pi = partition(low, high);
        quickSort(low, pi);
        quickSort(pi->link, high);
    }
}

void addStudent(ListSV &head, SinhVien &sv) {
    cout << "Nhap ma sinh vien (dinh dang 6 ky tu ): ";
    cin.ignore();
    cin.getline(sv.maSV, 8);
    cout << "Nhap ho ten: ";
    cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh: ";
    cin >> sv.gioiTinh;
    cin.ignore(); // Clear the newline character from the input buffer
    cout << "Nhap ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore(); // Clear the newline character from the input buffer
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: ";
    cin.getline(sv.lop, 12);
    cout << "Nhap khoa: ";
    cin.getline(sv.khoa, 7);
    insertTail(head, sv);
}

void printList(ListSV head) {
    for (Node* p = head; p != NULL; p = p->link) {
        cout << p->data.maSV << ". " << p->data.hoTen << ", " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
    }
}

Node* getTail(ListSV head) {
    while (head != NULL && head->link != NULL) {
        head = head->link;
    }
    return head;
}

int main() {
    ListSV head = NULL;
    SinhVien sv;
    readCSV(head);
    quickSort(head, getTail(head));
    printList(head);
    cout << "Co muon nhap them khong ? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'N' || choice == 'n') {
        return 0;
    }
    else if (choice != 'Y' && choice != 'y') {
        cout << "Lua chon khong hop le";
        return 1;
    }
    addStudent(head, sv);
    quickSort(head, getTail(head));
    printList(head);
    return 0;
}