#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_SIZE 100

typedef struct NodeHashTable {
	char* key;
	char* element;
	struct NodeHashTable* next;
	struct NodeHashTable* prev;
} NodeHashTable;

typedef struct HashTable {
	NodeHashTable** nodes;
	int count;
} HashTable;

// Функция для инициализации хеш-таблицы
HashTable* initHashTable() {
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	ht->nodes = (NodeHashTable**)malloc(MAX_SIZE * sizeof(NodeHashTable*));
	ht->count = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		ht->nodes[i] = NULL;
	}
	return ht;
}

// Функция для вычисления хеша
int calculateHashT(const char* element) {
	int hash = 0;
	for (int i = 0; element[i] != '\0'; i++) {
		hash = 31 * hash + element[i];
	}
	return abs(hash) % MAX_SIZE;
}

// Функция для добавления элемента в хеш-таблицу
void HSET(HashTable* ht, const char* key, const char* value) {
	int hash = calculateHashT(key);
	// Создаем новый узел для хранения ключа и значения
	NodeHashTable* newNode = (NodeHashTable*)malloc(sizeof(NodeHashTable));
	newNode->key = _strdup(key);
	newNode->element = _strdup(value);
	newNode->next = NULL; // Устанавливаем указатель на следующий узел как NULL
	newNode->prev = NULL; // Устанавливаем указатель на предыдущий узел как NULL
	// Обработка коллизий и проверка на дубликаты ключей
	NodeHashTable* current = ht->nodes[hash]; // Получаем узел по хеш-ключу
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) { // Если ключ уже существует
			// Освобождаем память нового узла
			free(newNode->key);
			free(newNode->element);
			free(newNode);
			printf("Ключ уже существует.\n");
			return;
		}
		if (current->next == NULL) { // Если достигли конца цепочки
			break;
		}
		current = current->next; // Переходим к следующему узлу
	}
	// Добавление нового узла
	if (current == NULL) { // Если цепочка пуста
		ht->nodes[hash] = newNode; // Устанавливаем новый узел как начало цепочки
	}
	else {
		current->next = newNode; // Добавляем новый узел в конец цепочки
		newNode->prev = current; // Устанавливаем предыдущий узел для нового узла
	}
	ht->count++;
}

// Функция для получения элемента из хеш-таблицы
char* HGET(HashTable* ht, const char* key) {
	int hash = calculateHashT(key);
	NodeHashTable* current = ht->nodes[hash]; // Получаем узел по хеш-ключу
	while (current != NULL) { // Перебираем узлы в цепочке
		if (strcmp(current->key, key) == 0) { // Если ключ совпадает
			return current->element;
		}
		current = current->next; // Переходим к следующему узлу
	}
	return NULL;
}

// Функция для удаления элемента из хеш-таблицы
void HDEL(HashTable* ht, const char* key) {
	int hash = calculateHashT(key);
	NodeHashTable* current = ht->nodes[hash]; // Получаем узел по хеш-ключу
	NodeHashTable* nodeToRemove = NULL;
	while (current != NULL) { // Перебираем узлы в цепочке
		if (strcmp(current->key, key) == 0) { // Если ключ совпадает
			nodeToRemove = current; // Устанавливаем узел для удаления
			break;
		}
		current = current->next; // Переходим к следующему узлу
	}

	if (nodeToRemove != NULL) {
		if (nodeToRemove->prev != NULL) { // Если у узла есть предыдущий узел
			nodeToRemove->prev->next = nodeToRemove->next; // Удаляем узел из цепочки
		}
		else {
			ht->nodes[hash] = nodeToRemove->next; // Устанавливаем следующий узел как начало цепочки
		}
		if (nodeToRemove->next != NULL) { // Если у узла есть следующий узел
			nodeToRemove->next->prev = nodeToRemove->prev; // Устанавливаем предыдущий узел для следующего узла
		}
		// Освобождаем память удаляемого узла
		free(nodeToRemove->key);
		free(nodeToRemove->element);
		free(nodeToRemove);
		ht->count--;
	}
	else {
		printf("Ключ не найден.\n");
	}
}

// Функция для вывода хеш-таблицы
void printHashTable(HashTable* ht) {
    printf("Хеш-таблица:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        NodeHashTable* current = ht->nodes[i];
        if (current != NULL) {
            printf("Индекс %d: ", i);
            while (current != NULL) {
                printf("(%s, %s) ", current->key, current->element);
                current = current->next;
            }
            printf("\n");
        }
    }
}

// Функция для освобождения памяти хеш-таблицы
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < MAX_SIZE; i++) {
        NodeHashTable* current = ht->nodes[i];
        while (current != NULL) {
            NodeHashTable* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->element);
            free(temp);
        }
    }
    free(ht->nodes);
    free(ht);
}

int main() {
	setlocale(LC_ALL, "Rus");
    // Инициализация хеш-таблицы
    HashTable* ht = initHashTable();

    // Добавление элементов в хеш-таблицу
    HSET(ht, "AXkLn", "элемент1");
    HSET(ht, "kqyzI", "элемент2");
	HSET(ht, "ключ3", "элемент3");

    // Вывод хеш-таблицы
    printHashTable(ht);

    // Получение элемента из хеш-таблицы
    char* element = HGET(ht, "kqyzI");
    if (element != NULL) {
        printf("Элемент с ключом 'ключ2': %s\n", element);
    }
    else {
        printf("Элемент с ключом 'ключ2' не найден.\n");
    }

    // Удаление элемента из хеш-таблицы
    HDEL(ht, "kqyzI");
    printHashTable(ht);

    // Освобождение памяти хеш-таблицы
    freeHashTable(ht);

    return 0;
}
