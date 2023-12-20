#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Определение структуры для узла дерева
typedef struct TreeNode {
    int value; // Значение в узле
    struct TreeNode* left; // Указатель на левое поддерево
    struct TreeNode* right; // Указатель на правое поддерево
} TreeNode;

// Функция для поиска узла с минимальным значением в дереве
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) node = node->left; // Перемещение в самый левый узел
    return node; // Возврат узла с минимальным значением
}

// Функция для удаления узла из дерева
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == NULL) return root; // Если дерево пустое, возвращаем NULL
    // Поиск узла для удаления
    if (key < root->value)
        root->left = deleteNode(root->left, key); // Переход к левому поддереву
    else if (key > root->value)
        root->right = deleteNode(root->right, key); // Переход к правому поддереву
    else {
        // Найден узел для удаления
        if (root->left == NULL) {
            TreeNode* temp = root->right; // Узел имеет только правое поддерево
            free(root); // Освобождение памяти удаляемого узла
            return temp; // Возврат правого поддерева
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left; // Узел имеет только левое поддерево
            free(root); // Освобождение памяти удаляемого узла
            return temp; // Возврат левого поддерева
        }

        // Узел имеет оба поддерева
        TreeNode* temp = findMin(root->right); // Поиск минимального значения в правом поддереве
        root->value = temp->value; // Замена значения удаляемого узла
        root->right = deleteNode(root->right, temp->value); // Удаление узла с минимальным значением
    }
    return root; // Возврат корня дерева
}

// Функция для обхода дерева "inorder"
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left); // Обход левого поддерева
        printf("%d ", root->value); // Вывод значения узла
        inorderTraversal(root->right); // Обход правого поддерева
    }
}

// Функция для создания нового узла
TreeNode* newNode(int item) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode)); // Выделение памяти для нового узла
    temp->value = item; // Присвоение значения узлу
    temp->left = temp->right = NULL; // Инициализация указателей на поддеревья как NULL
    return temp; // Возврат нового узла
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Создание дерева с корнем и поддеревьями
    TreeNode* root = newNode(50);
    root->left = newNode(30);
    root->right = newNode(70);
    root->left->left = newNode(20);
    root->left->right = newNode(40);
    root->right->left = newNode(60);
    root->right->right = newNode(80);

    printf("Исходное дерево: ");
    inorderTraversal(root); // Вывод исходного дерева
    printf("\n");

    root = deleteNode(root, 50); // Удаление узла с ключом 50

    printf("Дерево после удаления узла: ");
    inorderTraversal(root); // Вывод дерева после удаления узла
    printf("\n");

    return 0;
}