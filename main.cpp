#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ЧАСТЬ 1. БИНАРНОЕ ДЕРЕВО И ОБХОДЫ

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    // Прямой обход: корень, левое, правое
    void preOrder(Node* node) {
        if (node == nullptr) return;

        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    // Симметричный обход: левое, корень, правое
    void inOrder(Node* node) {
        if (node == nullptr) return;

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    // Обратный обход: левое, правое, корень
    void postOrder(Node* node) {
        if (node == nullptr) return;

        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    // Зеркальное отображение
    void mirror(Node* node) {
        if (node == nullptr) return;

        swap(node->left, node->right);

        mirror(node->left);
        mirror(node->right);
    }

    // Освобождение памяти
    void destroy(Node* node) {
        if (node == nullptr) return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroy(root);
    }

    // Создание тестового дерева
    void buildSample() {
        root = new Node(10);

        root->left = new Node(5);
        root->right = new Node(15);

        root->left->left = new Node(3);
        root->left->right = new Node(7);

        root->right->right = new Node(20);
    }

    void preOrder() {
        preOrder(root);
        cout << endl;
    }

    void inOrder() {
        inOrder(root);
        cout << endl;
    }

    void postOrder() {
        postOrder(root);
        cout << endl;
    }

    // Обход по уровням
    void levelOrder() {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }

        cout << endl;
    }

    void mirror() {
        mirror(root);
    }
};

// ЧАСТЬ 2. БИНАРНОЕ ДЕРЕВО ПОИСКА (BST)

class BST {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Вставка элемента
    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);

        return node;
    }

    // Поиск элемента
    Node* search(Node* node, int key) const {
        if (node == nullptr || node->data == key)
            return node;

        if (key < node->data)
            return search(node->left, key);

        return search(node->right, key);
    }

    // Поиск минимального узла
    Node* findMin(Node* node) const {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    // Удаление элемента
    Node* remove(Node* node, int key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->data) {
            node->left = remove(node->left, key);
        }
        else if (key > node->data) {
            node->right = remove(node->right, key);
        }
        else {
            // Случай 1: нет потомков
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Случай 2: только правый потомок
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // Случай 3: только левый потомок
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Случай 4: два потомка
            Node* minNode = findMin(node->right);

            node->data = minNode->data;

            node->right = remove(node->right, minNode->data);
        }

        return node;
    }

    // Симметричный обход с поиском переставленных узлов
    void findSwappedNodes(
        Node* node,
        Node*& previous,
        Node*& first,
        Node*& second
    ) {
        if (node == nullptr) return;

        findSwappedNodes(node->left, previous, first, second);

        if (previous != nullptr && previous->data > node->data) {
            if (first == nullptr)
                first = previous;

            second = node;
        }

        previous = node;

        findSwappedNodes(node->right, previous, first, second);
    }

    // Поиск узла для демонстрации восстановления
    Node* findNode(Node* node, int key) {
        if (node == nullptr || node->data == key)
            return node;

        if (key < node->data)
            return findNode(node->left, key);

        return findNode(node->right, key);
    }

    // Освобождение памяти
    void destroy(Node* node) {
        if (node == nullptr) return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

    // Вывод дерева в симметричном порядке
    void inOrder(Node* node) const {
        if (node == nullptr) return;

        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    // Высота дерева
    int height(Node* node) const {
        if (node == nullptr) return 0;

        return 1 + max(height(node->left), height(node->right));
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    // Запрет копирования дерева
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) const {
        return search(root, key) != nullptr;
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void inOrder() const {
        inOrder(root);
        cout << endl;
    }

    int getHeight() const {
        return height(root);
    }

    int getMin() const {
        Node* node = findMin(root);

        if (node == nullptr)
            throw runtime_error("Дерево пустое");

        return node->data;
    }

    int getMax() const {
        if (root == nullptr)
            throw runtime_error("Дерево пустое");

        Node* node = root;

        while (node->right != nullptr)
            node = node->right;

        return node->data;
    }

    // Восстановление BST после перестановки двух значений
    bool recoverSwappedNodes() {
        Node* previous = nullptr;
        Node* first = nullptr;
        Node* second = nullptr;

        findSwappedNodes(root, previous, first, second);

        if (first == nullptr || second == nullptr)
            return false;

        swap(first->data, second->data);

        return true;
    }

    // Искусственная перестановка двух узлов для проверки
    bool swapNodeValuesForTest(int firstKey, int secondKey) {
        Node* first = findNode(root, firstKey);
        Node* second = findNode(root, secondKey);

        if (first == nullptr || second == nullptr)
            return false;

        swap(first->data, second->data);

        return true;
    }
};

// ЧАСТЬ 3. ПРИМЕНЕНИЕ BST

int main() {
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(nullptr)));

    // ЧАСТЬ 1

    cout << "========== ЧАСТЬ 1 ==========\n";

    BinaryTree tree;
    tree.buildSample();

    cout << "\nПрямой обход (pre-order): ";
    tree.preOrder();

    cout << "Симметричный обход (in-order): ";
    tree.inOrder();

    cout << "Обратный обход (post-order): ";
    tree.postOrder();

    cout << "Уровневый обход (level-order): ";
    tree.levelOrder();

    cout << "\nЗеркальное отображение дерева:\n";

    tree.mirror();

    cout << "Прямой обход: ";
    tree.preOrder();

    cout << "Симметричный обход: ";
    tree.inOrder();

    cout << "Обратный обход: ";
    tree.postOrder();

    cout << "Уровневый обход: ";
    tree.levelOrder();

    // ЧАСТЬ 2

    cout << "\n========== ЧАСТЬ 2 ==========\n";

    BST testTree;

    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int value : values)
        testTree.insert(value);

    cout << "\nИсходное BST: ";
    testTree.inOrder();

    cout << "Поиск 40: "
         << (testTree.search(40) ? "найден" : "не найден") << endl;

    cout << "Поиск 100: "
         << (testTree.search(100) ? "найден" : "не найден") << endl;

    cout << "\nПерестановка значений 20 и 60 для проверки восстановления.\n";

    testTree.swapNodeValuesForTest(20, 60);

    cout << "Дерево после перестановки: ";
    testTree.inOrder();

    if (testTree.recoverSwappedNodes()) {
        cout << "Дерево восстановлено.\n";
    } else {
        cout << "Переставленные узлы не обнаружены.\n";
    }

    cout << "После восстановления: ";
    testTree.inOrder();

    cout << "\nУдаление элемента 30:\n";

    testTree.remove(30);

    testTree.inOrder();

    // ЧАСТЬ 3

    cout << "\n========== ЧАСТЬ 3 ==========\n";

    BST randomTree;

    vector<int> generated;

    // Генерация 20 уникальных случайных чисел
    while (generated.size() < 20) {
        int value = rand() % 100 + 1;

        bool exists = false;

        for (int x : generated) {
            if (x == value) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            generated.push_back(value);
            randomTree.insert(value);
        }
    }

    cout << "\nСгенерированные числа:\n";

    for (int x : generated)
        cout << x << " ";

    cout << "\n\nОтсортированная последовательность BST:\n";
    randomTree.inOrder();

    cout << "\nМинимальный элемент: "
         << randomTree.getMin() << endl;

    cout << "Максимальный элемент: "
         << randomTree.getMax() << endl;

    cout << "Высота дерева: "
         << randomTree.getHeight() << endl;

    // Удаление элемента, введённого пользователем
    int key;

    cout << "\nВведите число для удаления: ";
    cin >> key;

    if (randomTree.search(key)) {
        randomTree.remove(key);

        cout << "Элемент удалён.\n";
    } else {
        cout << "Такого элемента нет в дереве.\n";
    }

    cout << "BST после удаления:\n";
    randomTree.inOrder();

    return 0;
}
