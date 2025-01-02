#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TABLE_SIZE 20 // ��ʼɢ�б��С
#define NAME_LENGTH 20 // ������󳤶�

typedef struct HashEntry {
    char name[NAME_LENGTH]; // �洢����
    int isOccupied; // ��Ǹ�λ���Ƿ�ռ��
} HashEntry;

HashEntry* hashTable; // ɢ�б�
int tableSize; // ��ǰɢ�б��С
int itemCount; // ��ǰ�洢����������

// ��ʼ��ɢ�б�
void initHashTable() {
    tableSize = INITIAL_TABLE_SIZE;
    itemCount = 0;
    hashTable = (HashEntry*)malloc(tableSize * sizeof(HashEntry));
    for (int i = 0; i < tableSize; i++) {
        hashTable[i].isOccupied = 0; // ��ʼ��Ϊδռ��
    }
}

// ɢ�к���
unsigned long hashFunction(char* name) {
    unsigned long hash = 5381;
    int c;
    while ((c = *name++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tableSize; // ����ɢ��ֵ
}

// ��չɢ�б�
void resizeHashTable() {
    int oldSize = tableSize;
    tableSize *= 2; // ��չΪ����
    HashEntry* newTable = (HashEntry*)malloc(tableSize * sizeof(HashEntry));
    for (int i = 0; i < tableSize; i++) {
        newTable[i].isOccupied = 0; // ��ʼ��Ϊδռ��
    }

    // ����ɢ�оɱ��е�����Ԫ��
    for (int i = 0; i < oldSize; i++) {
        if (hashTable[i].isOccupied) {
            int index = hashFunction(hashTable[i].name);
            while (newTable[index].isOccupied) {
                index = (index + 1) % tableSize; // ����̽��
            }
            newTable[index] = hashTable[i];
        }
    }
    free(hashTable);
    hashTable = newTable;
}

// ����������ɢ�б�
void insert(char* name) {
    if ((float)(itemCount + 1) / tableSize > 0.7) { // �������ӳ���0.7ʱ��չ
        resizeHashTable();
    }

    int index = hashFunction(name);
    while (hashTable[index].isOccupied) {
        if (strcmp(hashTable[index].name, name) == 0) {
            printf("����: %s, �Ѵ����ڴ洢λ��: %d\n", name, index);
            return; // ����Ѵ��ڣ�����
        }
        index = (index + 1) % tableSize; // ����̽��
    }

    strcpy(hashTable[index].name, name);
    hashTable[index].isOccupied = 1; // ���Ϊ��ռ��
    itemCount++;
    printf("����: %s, �洢λ��: %d\n", name, index);
}

// ��ӡɢ�б�����
void printHashTable() {
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i].isOccupied) {
            printf("λ�� %d: %s\n", i, hashTable[i].name);
        } else {
            printf("λ�� %d: NULL\n", i);
        }
    }
}

// �ͷ�ɢ�б��ڴ�
void freeHashTable() {
    free(hashTable);
}

int main() {
    initHashTable();
    insert("����");
    insert("����");
    insert("����");
    insert("����");
    insert("����"); // �ظ�����
    insert("��С��");
    insert("��С��");
    insert("��С��");
    insert("��С��");

    printf("\nɢ�б�����:\n");
    printHashTable();

    freeHashTable(); // �ͷ��ڴ�
    return 0;
}
