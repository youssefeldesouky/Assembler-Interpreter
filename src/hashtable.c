//
// Created by Youssef on 6/11/2023.
//
#include "hashtable.h"

//Private Prototypes
static inline void pop_entry(hashtable_t *table, ht_entry *previous, ht_entry *current);
static size_t hash(char *key, size_t capacity);

hashtable_t *hashtable_init(){
    hashtable_t *table = malloc(sizeof(hashtable_t));
    table->capacity = 8;
    table->length = 0;
    table->hashing_func = hash;
    table->table = list_init();
    return table;
}

ht_entry *entry_create(char *key, size_t value){
    ht_entry *entry = malloc(sizeof(ht_entry));
    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

void hashtable_set(hashtable_t *table, char *key, size_t value){
    list_t *list = table->table;
    

    size_t hashed_key = table->hashing_func(key, table->capacity);
    ht_entry *entry = entry_create(key, value);
    if(!list_get(list, hashed_key)){
        list_insert(list, hashed_key, (void *)entry);
        table->length++;
        return;
    }

    if(!strcmp(key, ((ht_entry *)list->data[hashed_key])->key)){
        ((ht_entry *)list->data[hashed_key])->value = value;
    }else{
        ht_entry *current_last_entry = list->data[hashed_key];
        for(; current_last_entry->next; (current_last_entry = current_last_entry->next));
        current_last_entry->next = entry;
        table->length++;
    }

    float load_factor = table->length / (float)table->capacity;
    if(load_factor > LOAD_FACTOR){
        table->capacity += ADD_CAP;
        hashtable_rehash(table);
    }
}

size_t hashtable_get(hashtable_t *table, char *key){
    size_t hashed_key = table->hashing_func(key, table->capacity);
    list_t *list = table->table;

    ht_entry *entry = list->data[hashed_key];
    
    while(entry && strcmp(entry->key, key) != 0){
        entry = entry->next;
    }

    if(!entry){
        fprintf(stderr, "Error: Key not found!\n");
        return 0;
    }
    return entry->value;
}

void hashtable_rehash(hashtable_t *table){
    hashtable_t *_temp = hashtable_init();
    _temp->capacity = table->capacity;
    for(size_t i = 0; i < table->table->capacity; i++){
        ht_entry *entry = table->table->data[i];
        if(!entry) continue;
        do{
            char *key = strdup(entry->key);
            size_t value = entry->value;
            entry = entry->next;
            hashtable_set(_temp, key, value);
            free(key);
        }while(entry);
    }
    free(table->table);
    table->table = _temp->table;
    free(_temp);
}

size_t hashtable_remove(hashtable_t *table, char *key){
    size_t hashed_key = table->hashing_func(key, table->capacity);
    list_t *list = table->table;
    size_t value = 0;

    ht_entry *entry = list->data[hashed_key];
    ht_entry *previous_entry = NULL;

    while (entry && strcmp(entry->key, key) != 0){
        previous_entry = entry;
        entry = entry->next;
    }

    if(!entry){
        fprintf(stderr, "Error: Key not found!\n");
        return 0;
    }

    value = entry->value;

    pop_entry(table, previous_entry, entry);
    return value;
}

void hashtable_clear(hashtable_t *table){
    for(size_t i = 0; i < table->table->capacity; i++){
        ht_entry *entry = table->table->data[i];
        ht_entry *next_entry = NULL;
        if(!entry) continue;
        do{
            next_entry = entry->next;
            pop_entry(table, NULL, entry);
            entry = next_entry;
        }while(entry);
    }
    list_clear(table->table);
    table->capacity = ADD_CAP;
    table->length = 0;
}

void hashtable_purge(hashtable_t **table){
    hashtable_clear(*table);
    list_purge(&(*table)->table);
    free(*table);
    *table = NULL;
}

void hashtable_print(const hashtable_t *table){
    if(!table){
        fprintf(stderr, "Error: Table is not allocated in memory!\n");
        return;
    }
    for(size_t i = 0; i < table->table->capacity; i++){
        ht_entry *entry = table->table->data[i];
        if(!entry) continue;
        do{
            printf("%lu: (%s, %lu)\n", i, entry->key, entry->value);
            entry = entry->next;
        }while(entry);
    }
}

/**
 * @brief hashes the given string key into a 64-Bit index
 * @param key the key to be hashed
 * @param capacity the current capacity of the table
 * @return the hashed key to be used as an index
 */
static size_t hash(char *key, size_t capacity){
    size_t value = 0;
    while(*key){
        value = value * 13 + *key;
        key++;
    }
    value = value % capacity;
    return value;
}

/**
 * @brief Removes a linked-list node (Hash table entry), given its preceding entry
 * @param table the table that contains the entry
 * @param previous the preceding entry, if exists
 * @param current the entry to be removed
 * @return void
 */
static inline void pop_entry(hashtable_t *table, ht_entry *previous, ht_entry *current){
    if(!current){
        fprintf(stderr, "Error: Entry does not exist!\n");
        return;
    }
    size_t hashed_key = table->hashing_func(current->key, table->capacity);
    if(previous){
        previous->next = current->next;
    }else{
        table->table->data[hashed_key] = current->next;
    }
    free(current->key);
    free(current);
    table->length--;
}