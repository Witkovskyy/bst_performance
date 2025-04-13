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

void postorder(Tree* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->info << " ";
    }
}

int main() {
    Tree* root = nullptr;
    // Amount of nums 
    int n = 10000;
    int number;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::chrono::nanoseconds duration;

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> dist(1,10*n);

    std::vector<std::chrono::nanoseconds> creation_times = {};
    std::vector<int> excluded = {}; 
    std::vector<int> numbers = {};

    for (int i=0;i<n;i++){
        do {
            number = dist(gen);
        } while (std::find(excluded.begin(),excluded.end(),number)!=excluded.end());
        excluded.push_back(number);
        numbers.push_back(number);
    }

    for(int j=0;j<10;j++){

        auto start = std::chrono::high_resolution_clock::now();

        for (int i=0;i<n;i++){
            number = numbers[i];
            root = insert(root,number);
        }
        
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

        creation_times.push_back(duration);
    }

    // std::cout << "Inorder: ";
    // inorder(root);
    
    std::cout << "Czas wykonania: " << duration.count() << " micros" << std::endl;

    return 0;
}
