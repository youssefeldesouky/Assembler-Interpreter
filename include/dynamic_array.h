//
// Created by Youssef on 6/10/2023.
//

#ifndef ASSEMBLER_DYNAMIC_ARRAY_H
#define ASSEMBLER_DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ADD_CAP 8

typedef struct{
    void ** data;
    size_t capacity;
    size_t length;
} list_t;

/**
 * @brief allocates memory for a list and initializes it
 * @return a pointer to the initialized list
 */
list_t *list_init(void);

/**
 * @brief increases the capacity of the list by reallocating it
 * @param list the list to be expanded
 * @param times the number of times the list is increased by the added capacity
 * @return an error code that indicates the success or failure of the reallocation
 */
int8_t list_expand(list_t *list, size_t times);

/**
 * @brief clears a list by freeing all its elements without affecting capacity
 * @param list the list to be cleared
 * @return void
 */
void list_clear(list_t *list);

/**
 * @brief deallocates the list from memory. it nullifies the list passed
 * through the pointer to avoid dangling pointer issues
 * @param list a pointer to the list to be freed
 * @return void
 */
void list_purge(list_t **list);

/**
 * @brief insert an element at a given index
 * @param list the list to be inserted to
 * @param idx the index of the element
 * @param item a pointer to the item
 * @return void
 */
void list_insert(list_t *list, size_t idx, void *item);

/**
 * @brief appends an element to a list
 * @param list the list to be added to
 * @param item the element to be added
 * @return void
 */
void list_append(list_t *list, void *item);

/**
 * @brief gets the value of an element in a list
 * @param list the list to find the element in
 * @param idx the element to be added
 * @return a pointer to the element
 */
void *list_get(list_t *list, size_t index);

/**
 * @brief removes an element from a list at a given index
 * @param list the list to be removed from
 * @param idx the index of the element to be removed
 * @return void
 */
void list_remove(list_t *list, size_t idx);
#endif //ASSEMBLER_DYNAMIC_ARRAY_H
