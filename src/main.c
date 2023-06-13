#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "assembler.h"
#include "hashtable.h"

void swap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}

void print_arr(int *arr, size_t n){
    for(size_t i = 0; i < n; printf("%d\t", arr[i++]));
    putchar('\n');
}

void selection_sort(int *arr, size_t n){
    for(int i = 0; i < n - 1; i++){
        int idx_to_swap = i;
        for(int j = i + 1; j < n; j++){
            (arr[j] < arr[idx_to_swap]) ? idx_to_swap = j : 0;
        }
        if(idx_to_swap > i) swap(&arr[i], &arr[idx_to_swap]);
    }
}

void insertion_sort(int *arr, size_t n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j;
        for(j = i - 1; j >= 0 && arr[j] > key; j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }
}

void shell_sort(int *arr, size_t n){
    for(int i = n / 2; i > 0; i /= 2){
        for(int j = i; j < n; j++){
            int key = arr[j];
            int k;
            for(k = j - 1; k >= 0 && arr[k] > key; k--){
                arr[k+1] = arr[k];
            }
            arr[k+1] = key;
        }
    }
}

void bubble_sort(int *arr, size_t n){
    uint8_t swapped = 0;
    for(int i = 0; i < n - 1; i++){
        swapped = 0;
        for(int j = 0; j < n - i - 1; j++){
            (arr[j] > arr[j+1]) ? swapped = 1, swap(&arr[j], &arr[j+1]) : 0;
        }
        if(!swapped) break;
    }
}

int linear_search(const int *arr, size_t n, int value){
    for(int i = 0; i < n; i++){
        if(arr[i] == value) return i;
    }
    return -1;
}

int binary_search(const int *arr, size_t n, int value){
    int left = 0, right = n - 1, mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(value < arr[mid]) right = mid - 1;
        else if(value > arr[mid]) left = mid + 1;
        else return mid;
    }
    return -1;
}
//double half();
struct point{
    double x;
    double y;
};
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
    char * prg2 = "\
; My first program\n\
mov  a, 5\n\
inc  a\n\
call function\n\
msg  '(5+1)/2 = ', a    ; output message\n\
end\n\
\n\
function:\n\
    div  a, 2\n\
    ret\n";
    puts(assembler(prgrm));
    print_regs();
    return 0;
}



