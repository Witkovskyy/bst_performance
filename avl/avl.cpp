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

void inorder(Tree* root, std::vector<int>& result) {
    if (root) {
        inorder(root->left, result);
        result.push_back(root->info);
        inorder(root->right, result);
    }
}

int height(Tree* root) {
    if (!root) return 0;
    int left_h = height(root->left);
    int right_h = height(root->right);
    return 1 + std::max(left_h, right_h);
}

Tree* build_balanced_tree(std::vector<int>& sorted, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Tree* node = new Tree{sorted[mid], nullptr, nullptr};
    node->left = build_balanced_tree(sorted, start, mid - 1);
    node->right = build_balanced_tree(sorted, mid + 1, end);
    return node;
}

void delete_tree(Tree* root) {
    if (root) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

int main() {

    std::ifstream checkfile("avl.txt");
    bool isempty = checkfile.peek() == std::ifstream::traits_type::eof();
    checkfile.close();

    std::ofstream file("avl.txt", std::ios::app);
    if (file.is_open() && isempty) {
        file << "Liczba elementow, Wysokosc BST, Wysokosc AVL\n";
    }
    file.close();

    for (int iterator=1; iterator<=15; iterator++) {

        Tree* root = nullptr;
        Tree* avl_root = nullptr;

        int n = 1000 * iterator;
        int number;

        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(1, n*10);

        std::vector<int> excluded = {};
        std::vector<int> numbers = {};

        for (int i=0; i<n; i++) {
            do {
                number = dist(gen);
            } while (std::find(excluded.begin(), excluded.end(), number) != excluded.end());
            excluded.push_back(number);
            numbers.push_back(number);
        }

        for (int i=0; i<n; i++) {
            root = insert(root, numbers[i]);
        }

        int bst_height = height(root);

        std::vector<int> inorder_result = {};
        inorder(root, inorder_result);

        avl_root = build_balanced_tree(inorder_result, 0, inorder_result.size()-1);

        int avl_height = height(avl_root);

        std::ofstream file("avl.txt", std::ios::app);
        if (file.is_open()) {
            file << n << "," << bst_height << "," << avl_height << std::endl;
        }
        file.close();

        delete_tree(root);
        delete_tree(avl_root);

    }

    return 0;
}
