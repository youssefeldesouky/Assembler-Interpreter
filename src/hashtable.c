//
// Created by Youssef on 6/11/2023.
//
#include "hashtable.h"

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

void hashtable_add(hashtable_t *table, char *key, size_t value){
    list_t *list = table->table;
    if(table->length >= table->capacity){
        table->capacity += ADD_CAP;
    }
    size_t hashed_key = table->hashing_func(key, table->capacity);
    if(!list_get(list, hashed_key)){
        ht_entry *entry = entry_create(key, value);
        list_insert(list, hashed_key, (void *)entry);
        table->length++;
        return;
    }

    if(!strcmp(key, ((ht_entry *)list->data[hashed_key])->key)){
        ((ht_entry *)list->data[hashed_key])->value = value;
    }else{
        ht_entry *next_entry = entry_create(key, value);
        ((ht_entry *)list->data[hashed_key])->next = next_entry;
        table->length++;
    }
}

size_t hashtable_get(hashtable_t *table, char *key){
    size_t hashed_key = table->hashing_func(key, table->capacity);
    list_t *list = table->table;

    ht_entry *entry = list->data[hashed_key];
    if(!entry){
        fprintf(stderr, "Error: Key not found!");
        return 0;
    }

    while(entry && strcmp(entry->key, key) != 0){
        entry = entry->next;
    }
    return entry->value;
}

void hashtable_print(const hashtable_t *table){
    for(size_t i = 0; i < table->table->capacity; i++){
        ht_entry *entry = table->table->data[i];
        if(!entry) continue;
        do{
            printf("(%s, %llu)\n", entry->key, entry->value);
            entry = entry->next;
        }while(entry);
    }
}

size_t hash(char *key, size_t capacity){
    size_t value = 0;
    while(*key){
        value = value * 13 + *key;
        key++;
    }
    value = value % capacity;
    return value;
}