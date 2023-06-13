#include <stdio.h>
#include <stdint.h>
#include "assembler.h"
#include "hashtable.h"

int main() {
    int arr[] = {4, 7, 7, [3 ... 7]=4, 9, 0, -1, -3, -3};
    int n = sizeof(arr) / sizeof(arr[0]);
    char *prgrm = "\
        mov   a,11           ; value1\n\
        mov   b, 3            ; value2\n\
        call  mod_func\n\
        msg   'mod(', a, ', ', b, ') = ', d        ; output\n\
        end\n\
        ;\n\
        ; Mod function\n\
        mod_func:\
            mov   c, a        ; temp1\n\
            div   c, b\n\
            mul   c, b\n\
            mov   d, a        ; temp2\n\
            sub   d, c\n\
            ret\n\
";

    puts(assembler(prgrm));
    print_regs();
    return 0;
}



