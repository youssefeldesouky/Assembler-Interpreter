//
// Created by Youssef on 5/23/2023.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dynamic_array.h"
#include "hashtable.h"
#include "helper.h"

#define MAXLINE 100
#define BUF_SIZE 100
#define MAX_OP_SIZE 30

#define STACK_SIZE 16
#define REGISTER_FILE_SIZE 26

typedef struct{
    list_t *instructions;
    hashtable_t *labels;
    char *output_buffer;
} program_t;

/**
 * @brief returns the index of a register in the registers array
 * @param reg the alphabetic representation of the register
 * @return the index of the register in the registers array
 */
uint8_t get_reg_idx(char reg);

/**
 * @brief copies an immediate value into a register
 * @param reg the register to be copied into
 * @param value the immediate value
 * @return void
 */
void mov_immediate(char reg, int32_t value);

/**
 * @brief copies a value from a source register to a destination register
 * @param reg_dest the destination register
 * @param reg_src the source register
 * @return void
 */
void mov(char reg_dest, char reg_src);

/**
 * @brief adds a value from a source register to a destination register
 * @param reg_dest the destination register
 * @param reg_src the source register
 * @return void
 */
void add(char reg_dest, char reg_src);

/**
 * @brief adds an immediate value to a register
 * @param reg the register to be added to
 * @param value the immediate value
 * @return void
 */
void add_immediate(char reg_dest, int32_t value);

/**
 * @brief subtracts a value in a source register from a destination register
 * @param reg_dest the destination register
 * @param reg_src the source register
 * @return void
 */
void sub(char reg_dest, char reg_src);

/**
 * @brief subtracts an immediate value from a register
 * @param reg the register to be subtracted from
 * @param value the immediate value
 * @return void
 */
void sub_immediate(char reg_dest, int32_t value);

/**
 * @brief multiplies a value in a destination register by a value in a source register
 * @param reg_dest the destination register
 * @param reg_src the source register
 * @return void
 */
void mul(char reg_dest, char reg_src);

/**
 * @brief multiplies a value in a register by an immediate value
 * @param reg the register to be subtracted from
 * @param value the immediate value
 * @return void
 */
void mul_immediate(char reg_dest, int32_t value);

/**
 * @brief divides a value in a destination register by a value in a source register
 * @param reg_dest the destination register
 * @param reg_src the source register
 * @return void
 */
void divide(char reg_dest, char reg_src);

/**
 * @brief divides a value in a register by an immediate value
 * @param reg the register to be subtracted from
 * @param value the immediate value
 * @return void
 */
void divide_immediate(char reg_dest, int32_t value);

/**
 * @brief increments a value in a register by one
 * @param reg the register
 * @return void
 */
void inc(char reg);

/**
 * @brief decrements a value in a register by one
 * @param reg the register
 * @return void
 */
void dec(char reg);

/**
 * @brief jumps to an address of a label
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jmp(const program_t *program, char *label);

/**
 * @brief subtracts a value from another whether any or both of them are immediate
 *        or in a register, then sets the N and Z flags in the Status Register
 * @param op1 the first operand (can be register or an integer)
 * @param op2 the second operand (can be register or an integer)
 * @return void
 */
void cmp(char *op1, char *op2);

/**
 * @brief jumps to an address of a label, if the Z flag is clear
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jne(const program_t *program, char *label);

/**
 * @brief jumps to an address of a label, if the Z flag is set
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void je(const program_t *program, char *label);

/**
 * @brief jumps to an address of a label, if the Z flag is set
 *        or the N flag is clear
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jge(const program_t *program, char *label);

/**
 * @brief jumps to an address of a label, if the N flag is clear
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jg(const program_t *program, char *label);

/**
 * @brief jumps to an address of a label, if the Z flag is set
 *        or the N flag is set
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jle(const program_t *program, char *label);

/**
 * @brief jumps to an address of a label, if the N flag is set
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void jl(const program_t *program, char *label);

/**
 * @brief jumps to an address of a subroutine label. it also pushes
 *        the next instruction's address onto the stack before jumping.
 * @param program the program that contains the label
 * @param label the label string
 * @return void
 */
void call(const program_t *program, char *label);

/**
 * @brief returns from a subroutine by setting the instruction pointer
 *        to the address pushed on the stack by the call instruction.
 *        using this instruction without a call to a subroutine will
 *        result in the failure
 * @return void
 */
void ret(void);

/**
 * @brief halts the execution of the program successfully, it also allows
 *        the output buffer to contain whatever is written to it by the msg
 *        instruction. if not encountered in the program, it will return a -1
 * @return void
 */
void end(void);

/**
 * @brief outputs a combination of strings and register values
 *        to the output buffer of the program
 * @param program the program that contains the output buffer
 * @param label the combination to be used
 * @return void
 */
void msg(const program_t *program, const char *message);

/**
 * @brief parses an instruction found in a string and calls the
 *        appropriate functions
 * @param program the program that contains the instruction
 * @param inst the instruction string
 * @return void
 */
void parse_inst(const program_t *program, const char *inst);

/**
 * @brief converts a string that contains the program into
 *        a program object that splits the instructions into
 *        separate lines, ignores comments and removes labels
 *        while keeping their addresses in a hashtable
 * @param program_str the string that contains the program
 * @param program_ptr pointer to the program object
 * @return void
 */
void parse_program(const char *program_str, program_t *program_ptr);

/**
 * @brief runs the program by calling the instruction parser
 *        on each instruction line in the program
 * @param program pointer to the program object
 * @return void
 */
void run_program(const program_t *program);

/**
 * @brief parses the program by calling the program parser and runs it
 * @param program_str the string that contains the program
 * @return the output buffer of the program, it will always result in -1
 *         if the program didn't contain an end instruction
 */
char *assembler(const char *program_str);

/**
 * @brief resets all the values of the registers
 * @return void
 */
void reset_registers();

/**
 * @brief prints the current values of the registers
 * @return void
 */
void print_registers(void);

/**
 * @brief reads a single line from a multiline
 *        string, while ignoring comments and
 *        empty lines
 * @param str pointer to the multiline string
 * @param buf the buffer that will keep the line
 * @param n the size of the buffer including '\0'
 * @return the end position of the line in the source string
 */
size_t read_line(char **str, char *buf, size_t n);

/**
 * @brief removes leading whitespace and multiple spaces
 *        to be ready for parsing by the instruction parser,
 *        it also keeps output strings as is
 * @param str the line to be refactored
 * @return the end position of the word in the source string
 */
size_t refactor_line(char *str);

/**
 * @brief extracts the labels addresses found in a program
 *        and saves them in a hashtable
 * @param program the program that contains the output buffer
 * @return void
 */
void extract_labels(program_t *program);

#endif //ASSEMBLER_ASSEMBLER_H
