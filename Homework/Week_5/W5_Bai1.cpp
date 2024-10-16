#include <iostream>

using namespace std;

enum Color {
    red = 0,
    white,
    blue = 2
};

//Dung QuickSort de sap xep
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void sortColors(int* arr, int low, int high) {
    // QuickSort
    if (low < high) {
        int pi = partition(arr, low, high);
        sortColors(arr, low, pi - 1);
        sortColors(arr, pi + 1, high);
    }
    
}

int main(){
    int n;
    cout << "Nhap n: ";
    cin >> n;

    int *arr = new int[n];
    
    int choice;
    for (int i = 0; i < n; i++) {
        cout << "Chon dau vao thu " << i + 1 << ": 0. red, 1. white, 2. blue: ";
        cin >> choice;
        switch(choice){
            case 0:
                arr[i] = red;
                break;
            case 1:
                arr[i] = white;
                break;
            case 2:
                arr[i] = blue;
                break;
            default:
                cout << "Nhap sai, chon lai" << endl;
                i--;
                break;
        }
    }
    cout << "Mang truoc khi sort: ";
    for (int i = 0; i < n; i++){
        if (arr[i] == red){
            cout << "red ";
        } else if (arr[i] == white){
            cout << "white ";
        } else {
            cout << "blue ";
        }
    }
    sortColors(arr, 0, n - 1);

    cout << "\nMang sau khi sort: ";
    for (int i = 0; i < n; i++){
        if (arr[i] == red){
            cout << "red ";
        } else if (arr[i] == white){
            cout << "white ";
        } else {
            cout << "blue ";
        }
    }

    delete[] arr;
    return 0;

}