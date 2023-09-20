#include "assembler.h"

/**
 * @brief a status register that uses the same
 *        style of AVR SREG
 *        Most of the flags aren't used currently
 */
union{
    uint8_t value;
    struct {
        uint8_t C : 1;
        uint8_t Z : 1;
        uint8_t N : 1;
        uint8_t V : 1;
        uint8_t S : 1;
        uint8_t H : 1;
        uint8_t T : 1;
        uint8_t I : 1;
    };
} s_reg;

int32_t registers[26] = {0};
size_t inst_ptr = 0;
size_t tiny_stack = 0;
bool end_reached = false;
bool subroutine_called = false;
bool erroneous_ret = false;

uint8_t get_reg_idx(char reg){
    return (reg < 'a') ? reg - 'A' : reg - 'a';
}

void mov(char reg_dest, char reg_src){
    registers[get_reg_idx(reg_dest)] = registers[get_reg_idx(reg_src)];
}

void mov_immediate(char reg, int32_t value){
    registers[get_reg_idx(reg)] = value;
}

void add(char reg_dest, char reg_src){
    registers[get_reg_idx(reg_dest)] += registers[get_reg_idx(reg_src)];
}

void add_immediate(char reg_dest, int32_t value){
    registers[get_reg_idx(reg_dest)] += value;
}

void sub(char reg_dest, char reg_src){
    registers[get_reg_idx(reg_dest)] -= registers[get_reg_idx(reg_src)];
}

void sub_immediate(char reg_dest, int32_t value){
    registers[get_reg_idx(reg_dest)] -= value;
}

void mul(char reg_dest, char reg_src){
    registers[get_reg_idx(reg_dest)] *= registers[get_reg_idx(reg_src)];
}

void mul_immediate(char reg_dest, int32_t value){
    registers[get_reg_idx(reg_dest)] *= value;
}

void divide(char reg_dest, char reg_src){
    registers[get_reg_idx(reg_dest)] /= registers[get_reg_idx(reg_src)];
}

void divide_immediate(char reg_dest, int32_t value){
    registers[get_reg_idx(reg_dest)] /= value;
}

void inc(char reg){
    registers[get_reg_idx(reg)]++;
}

void dec(char reg){
    registers[get_reg_idx(reg)]--;
}

void jmp(const program_t *program, char *label){
    inst_ptr = hashtable_get(program->labels, label) - 1;
}

void cmp(char *op1, char *op2){
    int32_t x, y, _temp;
    if(isalpha(op1[0])){
        x = registers[get_reg_idx(op1[0])];
    }else{
        x = atoi(op1);
    }
    if(isalpha(op2[0])){
        y = registers[get_reg_idx(op2[0])];
    }else{
        y = atoi(op2);
    }
    _temp = x - y;
    s_reg.Z = (!_temp) ? 1 : 0;
    s_reg.N = (_temp < 0) ? 1 : 0;
}

void jne(const program_t *program, char *label){
    if(!s_reg.Z) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void je(const program_t *program, char *label){
    if(s_reg.Z) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void jge(const program_t *program, char *label){
    if(!s_reg.N || s_reg.Z) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void jg(const program_t *program, char *label){
    if(!s_reg.N) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void jle(const program_t *program, char *label){
    if(s_reg.N || s_reg.Z) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void jl(const program_t *program, char *label){
    if(s_reg.N) inst_ptr = hashtable_get(program->labels, label) - 1;
}

void call(const program_t *program, char *label){
    tiny_stack = inst_ptr + 1;
    subroutine_called = true;
    jmp(program, label);
}

void ret(){
    if(!subroutine_called){
        erroneous_ret = true;
        return;
    }
    inst_ptr = tiny_stack - 1; //decrement by 1 to make for the auto increment of the loop
    subroutine_called = false;
}

void end(){
    end_reached = true;
}

void msg(const program_t *program, const char *message){
    bool in_str = false;
    size_t buffer_idx = 0;
    for(size_t i = 0; message[i]; i++){
        if(message[i] == '\'' && message[i-1] != '\\'){
            in_str = !in_str;
            continue; //skip quotes
        }
        if(in_str){
            program->output_buffer[buffer_idx++] = message[i];
        }
        else{
            if(isalpha(message[i])){
                char _temp[100];
                //itoa(registers[get_reg_idx(message[i])], _temp, 10); //Not POSIX Compliant
                snprintf(_temp, 100, "%d", registers[get_reg_idx(message[i])]);
                for(uint32_t j = 0; _temp[j]; program->output_buffer[buffer_idx++] = _temp[j++]);
            }
        }
    }
}

void run_program(const program_t *program){
    for(inst_ptr = 0; inst_ptr < program->instructions->length && !end_reached && !erroneous_ret; inst_ptr++){
        parse_inst(program, (char *)list_get(program->instructions, inst_ptr));
    }
    if(!end_reached){
        strcpy(program->output_buffer, "-1");
    }
}

char *assembler(const char *program_str){
    program_t program = {.instructions = list_init(),
                         .labels = hashtable_init(),
                         .output_buffer = calloc(BUF_SIZE, sizeof(char))
                        };
    reset_registers();
    parse_program(program_str, &program);
    run_program(&program);
    hashtable_purge(&program.labels);
    list_purge(&program.instructions);
    return program.output_buffer;
}

void parse_inst(const program_t *program, const char *inst){
    char operator[5], operand_1[100], operand_2[100];
    sscanf(inst, "%[^ ]%*c%[^ ]%*c%[^\n]", operator, operand_1, operand_2);
    strtolower(operator);
    strtolower(operand_1);
    strtolower(operand_2);
    if(!strcmp(operator, "mov")){
        if(strlen(ltrim(rtrim(operand_1))) > 1){
            goto ENDL;
        }
        if(isalpha(operand_2[0])){
             if(strlen(ltrim(rtrim(operand_2))) > 1){
            goto ENDL;
        }
            mov(operand_1[0], operand_2[0]);
        }else{
            int32_t _temp;
            _temp = atoi(operand_2);
            mov_immediate(operand_1[0], _temp);
        }
    }else if(!strcmp(operator, "inc")){
        inc(operand_1[0]);
    }else if(!strcmp(operator, "dec")){
        dec(operand_1[0]);
    }else if(!strcmp(operator, "add")){
        if(isalpha(operand_2[0])){
            add(operand_1[0], operand_2[0]);
        }else{
            int32_t _temp;
            _temp = atoi(operand_2);
            add_immediate(operand_1[0], _temp);
        }
    }
    else if(!strcmp(operator, "sub")){
        if(isalpha(operand_2[0])){
            sub(operand_1[0], operand_2[0]);
        }else{
            int32_t _temp;
            _temp = atoi(operand_2);
            sub_immediate(operand_1[0], _temp);
        }
    }
    else if(!strcmp(operator, "mul")){
        if(isalpha(operand_2[0])){
            mul(operand_1[0], operand_2[0]);
        }else{
            int32_t _temp;
            _temp = atoi(operand_2);
            mul_immediate(operand_1[0], _temp);
        }
    }
    else if(!strcmp(operator, "div")){
        if(isalpha(operand_2[0])){
            divide(operand_1[0], operand_2[0]);
        }else{
            int32_t _temp;
            _temp = atoi(operand_2);
            divide_immediate(operand_1[0], _temp);
        }
    }
    else if(!strcmp(operator, "cmp")){
        cmp(operand_1, operand_2);
    }
    else if(!strcmp(operator, "jmp")){
        jmp(program, operand_1);
    }
    else if(!strcmp(operator, "jne")){
        jne(program, operand_1);
    }
    else if(!strcmp(operator, "je")){
        je(program, operand_1);
    }
    else if(!strcmp(operator, "jg")){
        jg(program, operand_1);
    }
    else if(!strcmp(operator, "jge")){
        jge(program, operand_1);
    }
    else if(!strcmp(operator, "jl")){
        jl(program, operand_1);
    }
    else if(!strcmp(operator, "jle")){
        jle(program, operand_1);
    }
    else if(!strcmp(operator, "jg")){
        jg(program, operand_1);
    }
    else if(!strcmp(operator, "call")){
        call(program, operand_1);
    }
    else if(!strcmp(operator, "jg")){
        jg(program, operand_1);
    }
    else if(!strcmp(operator, "msg")){
        sscanf(inst, "%*[^ ] %[^\n]", operand_1);
        msg(program, operand_1);
    }
    else if(!strcmp(operator, "ret")){
        ret();
    }
    else if(!strcmp(operator, "end")){
        end();
    }else{
ENDL:   fprintf(stderr, "Error: Unknown Instruction (%s)!\n", inst);
        end();
    }
}

size_t read_line(char **str, char *buf, size_t n){
    char *ptr = *str;
    size_t idx = 0;
    bool in_comment = false;
    while(*ptr != '\n' && idx < n){
        if(*ptr == ';') in_comment = true;
        if(!in_comment){
            buf[idx++] = *ptr;
        }
        ptr++;
    }
    buf[idx] = 0;
    *str = ptr + 1;
    return idx;
}

size_t refactor_line(char *str){
    bool in_str = false;
    bool in_inst = false;
    char *ptr = str;
    uint32_t idx = 0;
    while(*ptr){
        if(!in_inst && isalpha(*ptr)){
            in_inst = true;
        }
        if(*ptr == '\'' && *(ptr-1) != '\\'){
            in_str = !in_str;
        }
        if(in_inst){
            if(!in_str && *ptr == ','){
                *ptr = ' ';
            }
            if(!in_str && *ptr == ' ' && *(ptr-1) == ' '){
                //skip
            }else{
                str[idx++] = *ptr;
            }
        }
        ptr++;
    }
    str[idx] = 0;
    return idx;
}
void extract_labels(program_t *program){
    for(size_t i = 0; i < program->instructions->length; i++){
        bool in_str = false;
        uint32_t idx = 0;
        char *line = list_get(program->instructions, i);
        while(line[idx]){
            if(line[idx] == '\''){
                in_str = !inst_ptr;
            }
            if(line[idx] == ':' && !in_str){
                line[idx] = '\0';
                hashtable_set(program->labels, line, i);
                line[idx] = ':';
                if(idx == strlen(line) - 1){
                    list_remove(program->instructions, i);
                    i--;
                    break;
                }else{
                    for(; !isalpha(line[idx]); idx++);
                    program->instructions->data[i] += idx;
                }
            }
            idx++;
        }
    }
}

void parse_program(const char *program_str, program_t *program_ptr){
    char buffer[MAXLINE];
    // A copy is need because read_line() move the pointer passed
    // ahead with every call, hence the original string is unusable
    // after the program is read using read_line().
    char *program_copy = strdup(program_str);
    // This pointer is needed, to keep track of the beginning of
    // the string for it to be freed later.
    char *program_copy_start = program_copy;
    while(*program_copy){
        if(!read_line(&program_copy, buffer, MAXLINE)) continue;
        if(refactor_line(buffer)){
            list_append(program_ptr->instructions, strdup(buffer));
        }
    }
    extract_labels(program_ptr);
    free(program_copy_start);
}

void reset_registers(){
    for(int i = 0; i < 26; i++){
        registers[i] = 0;
    }
    inst_ptr = tiny_stack = 0;
    end_reached = subroutine_called = erroneous_ret = false;
}

void print_registers(){
    puts("<========= Registers =========>");
    for(int i = 0; i < 26; i++){
        if (i > 0 && !(i % 2)){
            putchar('\n');
        }
        printf("%c: %d\t\t", 'A' + i, registers[i]);   
    }
    putchar('\n');
}