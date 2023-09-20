//
// Created by Youssef on 6/13/2023.
//

#ifndef ASSEMBLER_HELPER_H
#define ASSEMBLER_HELPER_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief duplicates (Allocate and copy) a string
 * @param s the string to be duplicated
 * @return a pointer to the duplicate string
 */
char *strdup(const char *s);

/**
 * @brief converts a string to lowercase
 * @param s the string to be affected
 * @return the string after conversion
 */
char *strtolower(char *s);

/**
 * @brief removes leading whitespace from a string
 * @param s the string to be affected
 * @return the string after removal
 */
char *ltrim(char *s);

/**
 * @brief removes trailing whitespace from a string
 * @param s the string to be affected
 * @return the string after removal
 */
char *rtrim(char *s);

#endif //ASSEMBLER_HELPER_H
