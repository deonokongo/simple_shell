#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdlib.h>
#include <string.h>
#define INITIAL_TABLE_SIZE 100
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct Node {
    const char *key;
    const char *value;
    struct Node *next;
} Node;

static Node **table;
static unsigned int table_size;
static unsigned int num_elements;

static void initialize_table()
{
    table_size = INITIAL_TABLE_SIZE;
    table = (Node **)calloc(table_size, sizeof(Node *));
    if (table == NULL)
    {
        exit(EXIT_FAILURE);
    }
}
void hash_table_put(const char *key, const char *value);
char *hash_table_get(const char *key);
int hash_table_contains(const char *key);
KeyValuePair *hash_table_begin(void);
KeyValuePair *hash_table_next(KeyValuePair *pair);


#endif
