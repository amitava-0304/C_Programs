#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 101  // prime number, reduces collisions

typedef struct Node {
    int key;
    int count;
    struct Node *next;
} Node;

// simple hash function that works for negative numbers too
unsigned int hash(int key) {
    unsigned int ukey = (unsigned int)key; // handles negatives via wraparound
    return ukey % TABLE_SIZE;
}

void insertOrIncrement(Node *table[], int key) {
    unsigned int idx = hash(key);
    Node *curr = table[idx];

    // check if key already exists in this bucket
    while (curr != NULL) {
        if (curr->key == key) {
            curr->count++;
            return;
        }
        curr = curr->next;
    }

    // not found -> create new node at head of bucket
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->count = 1;
    newNode->next = table[idx];
    table[idx] = newNode;
}

void freeTable(Node *table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *curr = table[i];
        while (curr != NULL) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
}

int main() {
    int original[] = {1, 200, 200, 4, -5, -5, 1000000};
    int size = sizeof(original)/sizeof(original[0]);

    Node *table[TABLE_SIZE] = { NULL }; // all buckets start empty

    for (int i = 0; i < size; i++) {
        insertOrIncrement(table, original[i]);
    }

    // print in first-appearance order
    Node *printed[TABLE_SIZE] = { NULL }; // reuse trick: track what's printed
    for (int i = 0; i < size; i++) {
        unsigned int idx = hash(original[i]);
        Node *curr = table[idx];
        while (curr != NULL) {
            if (curr->key == original[i] && curr->count != -1) {
                printf("%d:%d\n", curr->key, curr->count);
                curr->count = -1; // mark as printed, avoid duplicates
                break;
            }
            curr = curr->next;
        }
    }

    freeTable(table);
    return 0;
}