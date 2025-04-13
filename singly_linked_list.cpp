#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

struct Node {
    int info;
    Node* next;
};

Node* createNode(int a) {
    Node* newNode = new Node;
    newNode->info = a;
    newNode->next = nullptr;
    return newNode;
}

void insertSorted(Node*& head, int a) {
    Node* newNode = createNode(a);

    if (head == nullptr || head->info > a) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* tmp = head;
    while (tmp->next != nullptr && tmp->next->info < a) {
        tmp = tmp->next;
    }

    newNode->next = tmp->next;
    tmp->next = newNode;
}

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->info << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> dist(1,1000);

    std::vector<int> excluded = {}; 

    Node* list = nullptr;
    int n = 100;
    for (int i=0;i<100;i++){
        int number;
        do {
            number = dist(gen);
        } while (std::find(excluded.begin(),excluded.end(),number)!=excluded.end());
        excluded.push_back(number);
        insertSorted(list,number);

        
    }

    printList(list);

    return 0;
}