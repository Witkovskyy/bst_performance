#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

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

Node* searchList(Node* head, int value) {
    while (head != nullptr) {
        if (head->info == value) {
            return head;
            }
        head = head->next;
        }
    return nullptr;
    }

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->info << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {

    std::ifstream checkfile("linked_list.txt");
    bool isempty = checkfile.peek() == std::ifstream::traits_type::eof();
    checkfile.close();

    std::ofstream file("linked_list.txt", std::ios::app);
    if(file.is_open() && isempty)
    {
        file << "Czas tworzenia,Czas porządku wstecznego,Suma czasu wyszukiwania" << std::endl;
    }

    file.close();

    for(int iterator=1;iterator<16;iterator++)
    {
        Node* found = nullptr;
        Node* list = nullptr;
        int n = 300*iterator;
        int* tofind = new int[n];
        int number;
        int creation_avg;



        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(1,n*10);

        std::vector<int> excluded = {}; 
        std::vector<int> numbers = {};

        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        std::chrono::nanoseconds duration;

        std::vector<std::chrono::nanoseconds> creation_times = {};
        std::chrono::nanoseconds sum_of_searches(0);
        std::chrono::nanoseconds creation_sum(0);
        
        for (int i=0;i<n;i++){
            do {
                number = dist(gen);
            } while (std::find(excluded.begin(),excluded.end(),number)!=excluded.end());
            excluded.push_back(number);
            numbers.push_back(number);
            tofind[i] = number;
        }

        for(int j=0;j<10;j++){

            start = std::chrono::high_resolution_clock::now();

            for (int i=0;i<n;i++){
                number = numbers[i];
                insertSorted(list,number);
            }
            
            end = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

            creation_times.push_back(duration);
        }
        
        for (int i=0;i<n;i++){
            number = tofind[i];
            start = std::chrono::high_resolution_clock::now();

            found = searchList(list, number);

            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

            sum_of_searches += duration;
        }
        

    for(int k=0;k<10;k++){
        creation_sum+=creation_times[k];
    }
    creation_avg = creation_sum.count()/10;

    // printList(list);
    // std::cout << creation_avg << std::endl;
    std::cout << sum_of_searches.count() << std::endl;
    }
    

    return 0;
}