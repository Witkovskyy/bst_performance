#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

struct Tree {
    int info;
    Tree* left;
    Tree* right;
};

Tree* insert(Tree* root, int x) {
    if (!root) {
        Tree* newNode = new Tree;
        newNode->info = x;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (x < root->info) {
        root->left = insert(root->left, x);
    } else if (x > root->info) {
        root->right = insert(root->right, x);
    }
    return root;
}

Tree* search(Tree* root, int x) {
    Tree* ptr = root;
    while (ptr) {
        if (x < ptr->info) {
            ptr = ptr->left;
        } else if (x > ptr->info) {
            ptr = ptr->right;
        } else {
            return ptr;
        }
    }
    return nullptr;
}

void inorder(Tree* root) {
    if (root) {
        inorder(root->left);
        std::cout << root->info << " ";
        inorder(root->right);
    }
}

void preorder(Tree* root) {
    if (root) {
        std::cout << root->info << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Tree* root, int debug_a) {
    if (root) {
        postorder(root->left, debug_a);
        postorder(root->right, debug_a);
        debug_a += 1;
        // std::cout << root->info << " ";
    }
}
void delete_tree(Tree* root) {
    if (root) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

int main() {

    // std::ofstream file("bst.txt", std::ios::app);
    std::ifstream checkfile("bst.txt");
    bool isempty = checkfile.peek() == std::ifstream::traits_type::eof();
    checkfile.close();

    std::ofstream file("bst.txt", std::ios::app);
    if(file.is_open() && isempty)
    {
        file << "Czas tworzenia,Czas porządku wstecznego,Suma czasu wyszukiwania" << std::endl;
    }

    file.close();


    for (int iterator=1;iterator<16;iterator++){

        
        Tree* root = nullptr;
        // Amount of nums 
        int n = 10000*iterator;
        int number;
        int* tofind = new int[n];
        int creation_avg;
        int postorder_avg;
        int debug_a = 0;
        

        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        std::chrono::nanoseconds duration;
        std::chrono::nanoseconds sum_of_searches;

        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(1,n*10);

        std::vector<int> excluded = {}; 
        std::vector<int> numbers = {};

        std::vector<std::chrono::nanoseconds> creation_times = {};
        std::vector<std::chrono::nanoseconds> postorder_times = {};
        std::chrono::nanoseconds creation_sum(0);
        std::chrono::nanoseconds postorder_sum(0);

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
                root = insert(root,number);
            }
            
            end = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

            creation_times.push_back(duration);
        }

        for (int i=0;i<n;i++){

            start = std::chrono::high_resolution_clock::now();
            search(root, tofind[i]);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            sum_of_searches += duration;

        }

        for(int j=0;j<10;j++){

            start = std::chrono::high_resolution_clock::now();

            postorder(root, debug_a);

            end = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            // delete_tree(root);
            postorder_times.push_back(duration);
        }

        // std::cout << "Inorder: ";
        // inorder(root);
        
        // std::cout << "Czas wykonania: " << duration.count() << " nanoseconds" << std::endl;
        // std::cout << sum_of_searches.count() << " nanoseconds ";
        // std::cout << creation_times[0].count();
        // std::cout << postorder_times[0].count();
        // for(int i=0;i<postorder_times.size();i++)
        // {
        //     std::cout << postorder_times[i].count() << std::endl;
        // }

        for(int k=0;k<10;k++){
            creation_sum+=creation_times[k];
        }
        creation_avg = creation_sum.count()/10;

        for(int k=0;k<10;k++){
            postorder_sum+=postorder_times[k];
        }
        postorder_avg = postorder_sum.count()/10;

        std::ofstream file("bst.txt", std::ios::app);

        if (file.is_open()) {
            file << creation_avg << "," << postorder_avg << "," << sum_of_searches.count() << std::endl;
        }

        file.close();

    }

    return 0;
}
