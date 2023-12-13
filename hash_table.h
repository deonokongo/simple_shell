#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <string.h>

#define INITIAL_TABLE_SIZE 100
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct KeyValuePair {
    const char *key;
    const char *value;
    struct KeyValuePair *next;
} KeyValuePair;

typedef struct Node {
    KeyValuePair *head;
} Node;

extern Node **table;
extern unsigned int table_size;
extern unsigned int num_elements;

void initialize_table();
void hash_table_put(const char *key, const char *value);
const char *hash_table_get(const char *key);
int hash_table_contains(const char *key);
KeyValuePair *hash_table_begin(void);
KeyValuePair *hash_table_next(KeyValuePair *pair);

#endif

