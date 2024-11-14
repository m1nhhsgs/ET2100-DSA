/*Một câu tiếng việt cấu thành từ nhiều từ khác nhau. Mỗi từ được lưu thành một node trong một danh sách liên kết đơn  

Khai báo cấu trúc danh sách liên kết. Các thông tin chứa ở mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện 
1. Xác định từ xuất hiện nhiều nhất trong câu  
2. Nếu xuất hiện từ láy (cấu thành từ hai từ giống nhau ví dụ: xanh xanh), thực hiện loại bỏ một từ 
3. Thực hiện đếm số từ vựng xuất hiện trong câu.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    string data;
    Node *next;
};

Node *createNode(string data)
{
    Node *temp = new Node;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void addTail(Node *&head, Node *&tail, string data)
{
    Node *temp = createNode(data);
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;
    tail = temp;
}


void printList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int countWord(Node *head)
{
    int count = 0;
    Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

string mostTimesWord(Node *head)
{
    vector<string> words;
    Node *temp = head;
    while (temp != NULL)
    {
        words.push_back(temp->data);
        temp = temp->next;
    }
    sort(words.begin(), words.end());
    int max_count = 1, res = 0, count = 1;
    for (int i = 1; i < words.size(); i++)
    {
        if (words[i] == words[i - 1])
            count++;
        else
        {
            if (count > max_count)
            {
                max_count = count;
                res = i - 1;
            }
            count = 1;
        }
    }
    if (count > max_count)
    {
        max_count = count;
        res = words.size() - 1;
    }
    return words[res];
}

void removeSameWord(Node *&head)
{
    Node *temp = head;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->data == temp->next->data)
        {
            Node *del = temp->next;
            temp->next = temp->next->next;
            delete del;
        }
        else
            temp = temp->next;
    }
}

int main()
{
    Node *head = NULL, *tail = NULL;
    string sentence;
    cout << "Nhap cau: ";
    getline(cin, sentence);
    string word = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        if (sentence[i] == ' ')
        {
            addTail(head, tail, word);
            word = "";
        }
        else
            word += sentence[i];
    }
    addTail(head, tail, word);
    cout << "Cau: ";
    printList(head);
    cout << "Tu lap lai nhieu nhat: " << mostTimesWord(head) << endl;
    removeSameWord(head);
    cout << "Cau sau khi xoa lap lai: ";
    printList(head);
    cout << "So tu xuat hien: " << countWord(head) << endl;
    return 0;
}