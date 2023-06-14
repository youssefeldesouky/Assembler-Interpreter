//
// Created by Youssef on 6/10/2023.
//

#include "dynamic_array.h"


list_t *list_init(){
    list_t *list = malloc(sizeof(*list));
    list->capacity = 8;
    list->length = 0;
    list->data = calloc(list->capacity, sizeof(void *));
    return list;
}

int8_t list_expand(list_t *list, size_t times){
    void ** _temp = realloc(list->data, (list->capacity + ADD_CAP * times) * sizeof(void *));
    if(!_temp){
        return -1;
    }
    for(size_t i = list->capacity; i < list->capacity + ADD_CAP * times; i++){
        _temp[i] = NULL;
    }
    list->data = _temp;
    list->capacity += ADD_CAP * times;
    return 0;
}

void list_clear(list_t *list){
    for(size_t i = 0; i < list->length; i++){
        free(list->data[i]);
        list->data[i] = NULL;
    }
    list->length = 0;
}

void list_purge(list_t **list){
    list_clear(*list);
    free((*list)->data);
    *list = NULL;
}

void list_insert(list_t *list, size_t idx, void *item){
    if(idx >= list->capacity){
        int8_t error = list_expand(list, idx/ADD_CAP - list->capacity/ADD_CAP + 1);
        if(error == -1){
            fprintf(stderr, "Error: Insufficient Memory!/"
                            "Cannot expand List. Item not added.\n");
            return;
        }
    }
    list->data[idx] = item;
    list->length = idx + 1;
}

void list_remove(list_t *list, size_t idx){
    if(idx >= list-> length){
        fprintf(stderr, "Error: Out of Bounds Access.\n");
        return;
    }
    free(list->data[idx]);
    if(idx != list->length - 1 && list->length > 1){
        for(size_t i = idx + 1; i < list->length; i++){
            list->data[i-1] = list->data[i];
        }
    }
    list->length--;
}

void list_append(list_t *list, void *item){
    if(list->length == list->capacity){
        int8_t error = list_expand(list, 1);
        if(error == -1){
            fprintf(stderr, "Error: Insufficient Memory!/"
                            "Cannot expand List. Item not added.\n");
            return;
        }
    }
    list->data[list->length++] = item;
    //This function was used when the dynamic array was string-oriented only.
    //Now it is generic, so it needs no allocation for the string item.
    //The user is now responsible for allocating the string in memory.
    /*
     * char *_temp = malloc(sizeof(char *) * (strlen(item) + 1));
    if(!_temp){
        fprintf(stderr, "Error: Insufficient Memory!/"
                        "Cannot Allocate memory for string. Item not added.");
        return;
    }
    strcpy(_temp, item);
    list->data[list->length++] = _temp;
    */
}

void *list_get(list_t *list, size_t idx){
    if(idx >= list->capacity || !list->length){
        return NULL;
    }
    return list->data[idx];
}