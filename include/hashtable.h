//
// Created by Youssef on 6/11/2023.
//

#ifndef ASSEMBLER_HASHTABLE_H
#define ASSEMBLER_HASHTABLE_H
#include <stdint.h>
#include "dynamic_array.h"
#include "helper.h"

#define ADD_CAP 8

typedef struct ht_entry{
    char *key;
    size_t value;
    struct ht_entry *next;
} ht_entry;

typedef struct{
    list_t *table;
    size_t capacity;
    size_t length;
    size_t (*hashing_func)(char *, size_t);
} hashtable_t;

/**
 * @brief allocates memory for a hashtable and initializes it
 * @return a pointer to the initialized hashtable
 */
hashtable_t *hashtable_init(void);

/**
 * @brief sets (Add/Modify) a key-value pair to a hashtable
 * @param table the table to add the pair to
 * @param key the string key of the pair
 * @param value the unsigned 64-Bit int value of the piar
 * @return void
 */
void hashtable_set(hashtable_t *table, char *key, size_t value);

/**
 * @brief gets a value corresponding to a key from a hashtable
 * @param table the table to be searched for the key
 * @param key the string key to be searched for
 * @return the value if found, if not, it will return 0
 *         and print an error message to the stderr file
 */
size_t hashtable_get(hashtable_t *table, char *key);

/**
 * @brief removes a value corresponding to a key from a hashtable
 * @param table the table to be searched for the key
 * @param key the string key to be removed
 * @return the value if found, if not, it will return 0
 *         and print an error message to the stderr file
 */
size_t hashtable_remove(hashtable_t *table, char *key);

/**
 * @brief removes all the key-value pairs in a hashtable
 * @param table the table to be cleared
 * @return void
 */
void hashtable_clear(hashtable_t *table);

/**
 * @brief prints all the key-value pairs in a hashtable
 * @param table the table to be printed
 * @return void
 */
void hashtable_print(const hashtable_t *table);

/**
 * @brief hashes the given string key into a 64-Bit index
 * @param key the key to be hashed
 * @param capacity the current capacity of the table
 * @return the hashed key to be used as an index
 */
size_t hash(char *key, size_t capacity);
#endif //ASSEMBLER_HASHTABLE_H
