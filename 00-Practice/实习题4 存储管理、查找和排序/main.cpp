#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TABLE_SIZE 20 // 初始散列表大小
#define NAME_LENGTH 20 // 姓名最大长度

typedef struct HashEntry {
    char name[NAME_LENGTH]; // 存储姓名
    int isOccupied; // 标记该位置是否被占用
} HashEntry;

HashEntry* hashTable; // 散列表
int tableSize; // 当前散列表大小
int itemCount; // 当前存储的姓名数量

// 初始化散列表
void initHashTable() {
    tableSize = INITIAL_TABLE_SIZE;
    itemCount = 0;
    hashTable = (HashEntry*)malloc(tableSize * sizeof(HashEntry));
    for (int i = 0; i < tableSize; i++) {
        hashTable[i].isOccupied = 0; // 初始化为未占用
    }
}

// 散列函数
unsigned long hashFunction(char* name) {
    unsigned long hash = 5381;
    int c;
    while ((c = *name++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % tableSize; // 返回散列值
}

// 扩展散列表
void resizeHashTable() {
    int oldSize = tableSize;
    tableSize *= 2; // 扩展为两倍
    HashEntry* newTable = (HashEntry*)malloc(tableSize * sizeof(HashEntry));
    for (int i = 0; i < tableSize; i++) {
        newTable[i].isOccupied = 0; // 初始化为未占用
    }

    // 重新散列旧表中的所有元素
    for (int i = 0; i < oldSize; i++) {
        if (hashTable[i].isOccupied) {
            int index = hashFunction(hashTable[i].name);
            while (newTable[index].isOccupied) {
                index = (index + 1) % tableSize; // 线性探测
            }
            newTable[index] = hashTable[i];
        }
    }
    free(hashTable);
    hashTable = newTable;
}

// 插入姓名到散列表
void insert(char* name) {
    if ((float)(itemCount + 1) / tableSize > 0.7) { // 负载因子超过0.7时扩展
        resizeHashTable();
    }

    int index = hashFunction(name);
    while (hashTable[index].isOccupied) {
        if (strcmp(hashTable[index].name, name) == 0) {
            printf("姓名: %s, 已存在于存储位置: %d\n", name, index);
            return; // 如果已存在，返回
        }
        index = (index + 1) % tableSize; // 线性探测
    }

    strcpy(hashTable[index].name, name);
    hashTable[index].isOccupied = 1; // 标记为已占用
    itemCount++;
    printf("姓名: %s, 存储位置: %d\n", name, index);
}

// 打印散列表内容
void printHashTable() {
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i].isOccupied) {
            printf("位置 %d: %s\n", i, hashTable[i].name);
        } else {
            printf("位置 %d: NULL\n", i);
        }
    }
}

// 释放散列表内存
void freeHashTable() {
    free(hashTable);
}

int main() {
    initHashTable();
    insert("张三");
    insert("李四");
    insert("王五");
    insert("赵六");
    insert("张三"); // 重复插入
    insert("王小明");
    insert("李小华");
    insert("赵小刚");
    insert("王小丽");

    printf("\n散列表内容:\n");
    printHashTable();

    freeHashTable(); // 释放内存
    return 0;
}
