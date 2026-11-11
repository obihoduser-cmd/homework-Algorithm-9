# homework-Algorithm-9
Институт Информационных Технологий и Кибербезопасности
Дисциплина: Алгоритмы и Структура Данных
Тема: Бинарное дерево. Обходы. BST
Выполнил: Ибрагимов Магомед Абдуллаевич
Группа: ПИЖ-б-о-25-2

Цель работы:
1. Реализовать структуру данных «бинарное дерево» и изучить
различные способы его обхода (прямой, симметричный,
обратный, уровневый)
2. Реализовать бинарное дерево поиска (BST) с операциями вставки,
удаления и поиска
3. Освоить применение рекурсии для работы с деревьями
4. Проанализировать сложность операций в BST
5. Научиться визуализировать структуру дерева

<img width="647" height="152" alt="image" src="https://github.com/user-attachments/assets/b2ba9bbc-beea-48c8-a741-86bd5e1422d9" />
<img width="609" height="102" alt="image" src="https://github.com/user-attachments/assets/28cff26d-aaed-4402-96de-ab0e18c6fffe" />
<img width="660" height="89" alt="image" src="https://github.com/user-attachments/assets/592e890e-61d2-4e60-b32b-ab75a5c08916" />
<img width="633" height="79" alt="image" src="https://github.com/user-attachments/assets/424b7b4b-555e-496e-b547-2a7c658991f2" />
<img width="618" height="250" alt="image" src="https://github.com/user-attachments/assets/1c7575b2-14fc-412c-a3fc-c2da4222b135" />
Рисунки 1, 2, 3, 4, 5 - Условие задания



```
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ==========================================
// ЧАСТЬ 1. БИНАРНОЕ ДЕРЕВО И ОБХОДЫ
// ==========================================

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

// ==========================================
// ЧАСТЬ 2. БИНАРНОЕ ДЕРЕВО ПОИСКА (BST)
// ==========================================

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

// ==========================================
// ЧАСТЬ 3. ПРИМЕНЕНИЕ BST
// ==========================================

int main() {
    setlocale(LC_ALL, "");
    srand(static_cast<unsigned int>(time(nullptr)));

    // --------------------------------------
    // ЧАСТЬ 1
    // --------------------------------------

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

    // --------------------------------------
    // ЧАСТЬ 2
    // --------------------------------------

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

    // --------------------------------------
    // ЧАСТЬ 3
    // --------------------------------------

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
```

<img width="645" height="748" alt="image" src="https://github.com/user-attachments/assets/ffa61fe7-99ab-4278-a1b2-3fa65d57b638" />
Рисунок 6 - Вывод

Контрольные вопросы:
1. Что такое бинарное дерево? Из каких элементов оно состоит?

Бинарное дерево — это структура данных, в которой каждый узел может иметь не более двух потомков: левого и правого. Оно состоит из корневого узла, внутренних узлов, листьев (узлов без потомков) и связей между ними.

2. В чём отличие бинарного дерева от бинарного дерева поиска (BST)?

В обычном бинарном дереве нет обязательного порядка расположения элементов. В бинарном дереве поиска для каждого узла значения в левом поддереве меньше его значения, а в правом — больше (при условии уникальных ключей).

3. Какие существуют виды обхода бинарного дерева? В чём их особенности?
- Pre-order (прямой): корень → левое поддерево → правое поддерево.
- In-order (симметричный): левое поддерево → корень → правое поддерево.
- Post-order (обратный): левое поддерево → правое поддерево → корень.
- Level-order (по уровням): узлы посещаются сверху вниз, слева направо. Обычно используется очередь.
4. Какой обход даёт отсортированную последовательность для BST?

Симметричный обход (In-order). Он посещает элементы в порядке возрастания.

5. Какова сложность операций поиска, вставки и удаления в BST? От чего она зависит?

В среднем сложность поиска, вставки и удаления составляет \(O(\log n)\), если дерево достаточно сбалансировано. В худшем случае — \(O(n)\), если дерево сильно вытянуто. Сложность зависит от высоты дерева.

6. Что происходит с BST, если вставлять элементы в отсортированном порядке?

Дерево становится вырожденным: каждый новый элемент добавляется преимущественно в одну сторону. Оно напоминает связный список, поэтому основные операции могут выполняться за \(O(n)\).

7. Какие три случая нужно рассмотреть при удалении узла из BST?
1. Узел — лист, у него нет потомков. Его можно просто удалить.
2. У узла один потомок. Потомок занимает место удаляемого узла.
3. У узла два потомка. Его заменяют значением минимального элемента правого поддерева или максимального элемента левого поддерева, после чего удаляют заменяющий узел.
8. Как найти наименьший элемент в BST? Наибольший?
- Наименьший элемент находится в самом левом узле дерева.
- Наибольший элемент находится в самом правом узле дерева.
Нужно двигаться от корня в соответствующую сторону, пока следующий потомок не станет отсутствовать.

9. Как вычислить высоту бинарного дерева рекурсивно?

Высота определяется как максимальная высота левого и правого поддеревьев плюс один:
\[
H = 1 + \max(H_{left}, H_{right})
\]

Для пустого дерева высота равна 0.

10. Что такое наименьший общий предок (LCA) двух узлов в дереве?

LCA (Lowest Common Ancestor) — это самый глубокий узел дерева, который является предком обоих заданных узлов. Сам узел может считаться своим предком.

11. Как проверить, является ли бинарное дерево BST?

Нужно рекурсивно проверить, что каждый узел находится в допустимом диапазоне значений: для левого поддерева значения меньше текущего, для правого — больше. При переходе к потомкам границы диапазона обновляются.

12. Что такое сбалансированное дерево? Почему это важно для производительности?

Сбалансированное дерево — это дерево, в котором высоты левого и правого поддеревьев узлов отличаются незначительно. Баланс важен, потому что позволяет сохранять высоту дерева порядка \(O(\log n)\), обеспечивая эффективный поиск, вставку и удаление.

13. Как преобразовать несбалансированное BST в сбалансированное?

Сначала выполняют симметричный обход BST и сохраняют значения в отсортированный массив. Затем рекурсивно выбирают средний элемент массива как корень, а левую и правую половины используют для построения поддеревьев.

14. Как восстановить дерево по массиву обхода (in-order + pre-order)?

Первый элемент Pre-order является корнем дерева. Его находят в массиве In-order: элементы слева от него относятся к левому поддереву, справа — к правому. Затем процесс рекурсивно повторяют для каждого поддерева.

15. Как реализовать итеративный (не рекурсивный) обход бинарного дерева?

Итеративный обход выполняется с помощью дополнительных структур данных:
- Pre-order: используется стек. Сначала обрабатывается корень, затем добавляются правый и левый потомки.
- In-order: используется стек для сохранения пути к узлам. Сначала переходят максимально влево, затем обрабатывают узел и переходят вправо.
- Post-order: можно использовать два стека или один стек с дополнительным признаком посещения узла.
- Level-order: используется очередь, в которую последовательно добавляются потомки обработанных узлов.

