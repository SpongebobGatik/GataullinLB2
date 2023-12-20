#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Определение структуры узла дерева
typedef struct Node {
    int data;
    struct Node* left, * right;
} Node;

// Функция для создания нового узла
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Функция для печати правого соседа каждого узла
void printRightNeighbor(Node* root) {
    if (root == NULL) return;

    // Создаем очередь для уровневого обхода
    Node* queue[100];
    int front = 0, rear = 0;

    // Добавляем корень дерева в очередь
    queue[rear++] = root;
    queue[rear++] = NULL; // Маркер конца уровня

    while (front < rear) {
        Node* current = queue[front++];

        if (current == NULL) {
            if (front < rear) {
                queue[rear++] = NULL; // Добавляем маркер конца уровня
            }
        }
        else {
            // Печатаем данные текущего узла и его правого соседа
            printf("%d – ", current->data);
            if (queue[front] != NULL) {
                printf("%d", queue[front]->data);
            }
            else {
                printf("null");
            }
            printf(", ");

            // Добавляем дочерние узлы в очередь
            if (current->left != NULL) queue[rear++] = current->left;
            if (current->right != NULL) queue[rear++] = current->right;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Создаем узлы дерева согласно примеру
    Node* root = newNode(22);
    root->left = newNode(16);
    root->right = newNode(51);
    root->left->left = newNode(7);
    root->left->right = newNode(19);
    root->right->left = newNode(43);
    root->right->right = newNode(57);

    // Печатаем правого соседа каждого узла
    printRightNeighbor(root);

    return 0;
}