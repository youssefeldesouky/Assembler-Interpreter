#include <stdio.h>
#include "assembler.h"

enum error_code { READ_ERROR, READ_OK };

enum error_code load_program_from_file(char *program_path, char **output_buffer);

char *first_program = "\
    ; My first program\n\
    mov  a, 5\n\
    inc  a\n\
    call function\n\
    msg  '(5+1)/2 = ', a    ; output message\n\
    end\n\
    \n\
    \n\
    function:\n\
        div  a, 2\n\
        ret\n";

char *factorial_program = "\
    mov   a, 5\n\
    mov   b, a\n\
    mov   c, a\n\
    call  proc_fact\n\
    call  print\n\
    end\n\
    \n\
    proc_fact:\n\
        dec   b\n\
        mul   c, b\n\
        cmp   b, 1\n\
        jne   proc_fact\n\
        ret\n\
    \n\
    print:\n\
        msg   a, '! = ', c ; output text\n\
        ret\n\
    ";

char *modulo_program = "\
    mov   a, 11           ; value1\n\
    mov   b, 3            ; value2\n\
    call  mod_func\n\
    msg   'mod(', a, ', ', b, ') = ', d        ; output\n\
    end\n\
    \n\
    ; Mod function\n\
    mod_func:\n\
        mov   c, a        ; temp1\n\
        div   c, b\n\
        mul   c, b\n\
        mov   d, a        ; temp2\n\
        sub   d, c\n\
        ret\n\
    ";

char *gcd_program = "\
    mov   a, 81         ; value1\n\
    mov   b, 153        ; value2\n\
    call  init\n\
    call  proc_gcd\n\
    call  print\n\
    end\n\
    \n\
    proc_gcd:\n\
        cmp   c, d\n\
        jne   loop\n\
        ret\n\
    \n\
    loop:\n\
        cmp   c, d\n\
        jg    a_bigger\n\
        jmp   b_bigger\n\
    \n\
    a_bigger:\n\
        sub   c, d\n\
        jmp   proc_gcd\n\
    \n\
    b_bigger:\n\
        sub   d, c\n\
        jmp   proc_gcd\n\
    \n\
    init:\n\
        cmp   a, 0\n\
        jl    a_abs\n\
        cmp   b, 0\n\
        jl    b_abs\n\
        mov   c, a            ; temp1\n\
        mov   d, b            ; temp2\n\
        ret\n\
    \n\
    a_abs:\n\
        mul   a, -1\n\
        jmp   init\n\
    \n\
    b_abs:\n\
        mul   b, -1\n\
        jmp   init\n\
    \n\
    print:\n\
        msg   'gcd(', a, ', ', b, ') = ', c\n\
        ret\n\
    ";

char *power_program = "\
    mov   a, 2            ; value1\n\
    mov   b, 10           ; value2\n\
    mov   c, a            ; temp1\n\
    mov   d, b            ; temp2\n\
    call  proc_func\n\
    call  print\n\
    end\n\
    \n\
    proc_func:\n\
        cmp   d, 1\n\
        je    continue\n\
        mul   c, a\n\
        dec   d\n\
        jmp  proc_func\n\
    \n\
    continue:\n\
        ret\n\
    \n\
    print:\n\
        msg a, '^', b, ' = ', c\n\
        ret\n\
    ";

void hashtable_rehash_element(hashtable_t *table, char *key, size_t previous_capacity);

//Either run the program without a command-line argument, to run one of the programs
//Define above, or run it with a command-line argument of an assembly file
//(for example ./build/assembler programs/first_program.s) to run the code inside it.
int main(int argc, char ** argv) {
    char *program_buffer = NULL;
    if(argc > 1){
        if (load_program_from_file(argv[1], &program_buffer) == READ_ERROR){
            return 0;
        }
    }else{
        program_buffer = power_program;
    }
    char *output = assembler(program_buffer);
    puts(output);
    print_registers();
    return 0;
}

enum error_code load_program_from_file(char *program_path, char **output_buffer){
    FILE *f = fopen(program_path, "r");
    if(!f){
        fprintf(stderr, "Error! File does not exist!");
        return READ_ERROR;
    }
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    *output_buffer = malloc(length + 1);
    if(!(*output_buffer)){
        fprintf(stderr, "Error! File too big!");
        return READ_ERROR;
    }
    fread(*output_buffer, sizeof(char), length, f);
    fclose(f);
    (*output_buffer)[length] = '\0';
    return READ_OK;
}
