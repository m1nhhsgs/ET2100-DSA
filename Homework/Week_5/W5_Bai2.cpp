/*Thiết kế giải thuật và cài đặt để tạo ra một mảng số nửa nguyên tố nhỏ hơn một số N cho trước và thực hiện hai yêu cầu sau
- Tìm ra tất cả các cặp số Blum có tổng cũng là một số nửa nguyên tố nhỏ hơn N
- Kiểm tra xem một số nửa nguyên tố M có tồn tại trong dãy số nửa nguyên tố được tạo ra hay không.*/


/*Định nghĩa số Blum: In mathematics, a natural number n is a Blum integer if n = p × q is a semiprime for which p and q are distinct prime numbers congruent to 3 mod 4.
[1] That is, p and q must be of the form 4t + 3, for some integer t. 
Integers of this form are referred to as Blum primes.
[2] This means that the factors of a Blum integer are Gaussian primes with no imaginary part. 
The first few Blum integers are:
21, 33, 57, 69, 77, 93, 129, 133, 141, 161, 177, 201, 209, 213, 217, 237, 249, 253, 301, 309, 321, 329, 341, 381, 393, 413, 417, 437, 453, 469, 473, 489, 497, ... (sequence A016105 in the OEIS)
The integers were named for computer scientist Manuel Blum.[3]*/

// Bài này sẽ làm với số Semiprime thay vì Blum integer
#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int n){
    if (n < 2){
        return false;
    }
    if (n == 2){
        return true;
    }
    for (int i = 2; i * i <= n; i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

bool isSemiprime(int n){
    vector<int> v;
    for (int i = 2; i <= n; i++){
        if (isPrime(i)){
            v.push_back(i);
        }
    }

    for (int i = 0; i <= v.size(); i++){
        for (int j = i; j <= v.size(); j++){
            if (v[i] * v[j] == n){
                return true;
            }
        }
    }
    return false;
}
    

vector<int> findSemiprimeinRange(int N){
    vector<int> v;
    for (int i = 2 ; i <= N; i++){
        if (isSemiprime(i)){
            v.push_back(i);
        }
    }
    return v;
}

//Tìm ra tất cả các cặp số Blum có tổng cũng là một số Blum nhỏ hơn N
vector<vector<int>> findSemiprimePairs(int N){
    vector<int> v1 = findSemiprimeinRange(N);
    vector<vector<int>> v2;

    for (int i = 0; i < v1.size(); i++){
        for (int j = i; j < v1.size(); j++){
            if (v1[i] + v1[j] < N && isSemiprime(v1[i] + v1[j])){
                v2.push_back({v1[i], v1[j]});
            }
        }
    }
    return v2;    
}


bool isSemiprimeExist(int M, int N){
    vector<int> v = findSemiprimeinRange(N);
    for (int i = 0; i < v.size(); i++){
        if (v[i] == M){
            return true;
        }
    }
    return false;
}

int main(){
    int N;
    cout << "Nhap N: ";
    cin >> N;
    vector<int> v1 = findSemiprimeinRange(N);
    cout << "\nTat ca cac so semiprime nho hon " << N << " la: " << endl;
    for (int i = 0; i < v1.size(); i++){
        cout << v1[i] << " ";
    }
    vector<vector<int>> v = findSemiprimePairs(N);
    if (v.size() == 0){
        cout << "Khong co cap nao thoa man\n" << endl;
    }
    else{
        cout << "Tat ca cac cap Semiprime co tong cung la semiprime nho hon " << N << " la: " << endl;
        for (int i = 0; i < v.size(); i++){
            cout << "(" << v[i][0] << ", " << v[i][1] << ")" << endl;
        }
    }
    
    int M;
    while (true){
        cout << "Nhap M: ";
        cin >> M;
        if (isSemiprimeExist(M, N)){
            cout << M << " nam trong tap" << endl;
        }
        else{
            cout << M << " khong nam trong tap" << endl;
        }
    }
    return 0;
}

