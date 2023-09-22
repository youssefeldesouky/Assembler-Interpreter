//
// Created by Youssef on 6/13/2023.
//

#ifndef ASSEMBLER_HELPER_H
#define ASSEMBLER_HELPER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @brief copies the first non-blank string from a source into a destination buffer
 *        with the ability to specify the cursor starting position, so it eliminates
 *        the need to modify the source string pointer.
 * @param src the source string
 * @param dst the destination string buffer
 * @param starting_idx where to start capturing from the source string
 * @param dst_buffer_size the maximum size of the buffer, to eliminate overflowing it
 * @return the last position of the cursor in the source string
 */
size_t get_word(const char *src, char *dst, size_t starting_idx, size_t dst_buffer_size);

/**
 * @brief copies the first line from a source into a destination buffer
 *        with the ability to specify the cursor starting position, so it eliminates
 *        the need to modify the source string pointer.
 * @param src the source string
 * @param dst the destination string buffer
 * @param starting_idx a pointer of where to start capturing from the source string
 * @param dst_buffer_size the maximum size of the line, to eliminate overflowing it
 * @return the last position of the cursor in the source string
 */
int get_line(const char *src, char *dst, size_t *starting_idx, size_t dst_buffer_size);

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
