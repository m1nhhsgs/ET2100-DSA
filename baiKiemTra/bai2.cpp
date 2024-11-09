/*Bài toán Josephus được mô tả như sau: Có N người đánh số từ 1 đến N ngồi xếp thành vòng tròn. Người bắt đầu là người số 1 giữ một quả bóng và truyền cho người thứ 2, người thứ 2 truyền bóng cho người thứ 3 theo 1 chiều nhất định và lần lượt đến khi truyền đến người thứ M, người thứ M sẽ bị loại ra khỏi vòng tròn. Vòng tròn sẽ bị thu hẹp dần, cuộc chơi vẫn tiếp tục với người ngồi kế tiếp người thứ M vừa bị loại bỏ, sẽ là người giữ quả bóng cho lượt chơi tiếp theo và được coi là người số 1 của lượt tiếp theo. Người cuối cùng còn sót lại là người chiến thắng.

Ví dụ như sau:

- Nếu N = 5, M = 0, các người chơi bị loại bỏ là 1, 2, ,3 ,4 người 5 là người chiến thắng

- Nếu N = 5, M = 1, thì thứ tự người chơi bị loại bỏ là 2, 4, 1, 5 người 3 là người chiến thắng

Yêu cầu:

1. Thiết kế giải thuật để tìm ra người chiến thắng cuối cùng, viết chương trình cài đặt giải thuật bằng việc sử dụng cấu trúc dữ liệu kiểu danh sách liên kết để duyệt luật chơi và tìm được vị trí người chiến thắng với các trường hợp của M = 1,2,3 và N bất kỳ
2. Nếu M = 1, xác định độ phức tạp thuật toán tương ứng với giải thuật đã đề xuất, tính thời gian chạy chương trình với giá trị N > 100000*/

#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

class CircularLinkedList {
public:
    CircularLinkedList() : head(nullptr) {}

    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void remove(Node* node) {
        if (head == node) {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = head->next;
            head = head->next;
        } else {
            Node* temp = head;
            while (temp->next != node) {
                temp = temp->next;
            }
            temp->next = node->next;
        }
        delete node;
    }

    Node* getHead() {
        return head;
    }

private:
    Node* head;
};

int josephus_problem(int N, int M) {
    CircularLinkedList cll;
    for (int i = 1; i <= N; ++i) {
        cll.append(i);
    }

    Node* current = cll.getHead();

    while (current->next != current) {
        for (int i = 1; i < M; ++i) {
            current = current->next;
        }
        std::cout << "Loai bo: " << current->next->data << std::endl;
        cll.remove(current->next);
        current = current->next;
    }

    return current->data;
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::cout << josephus_problem(N, M) << std::endl;

    return 0;
}




