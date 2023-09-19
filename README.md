[![Try with Replit Badge](https://replit.com/badge?caption=Try%20with%20Replit)](https://replit.com/@JoeSamir/AssemblerSimulator)
# Assembler Interpreter
A simulator for a simple assembler interpreter that is a soultion to a codewars.com kata found <a href="https://www.codewars.com/kata/58e61f3d8ff24f774400002c/c">here</a> using the C language.
I have solved it 4 years before using Javascript <a href="https://replit.com/@JoeSamir/Assembler-Interpreter">Here</a>.

## Problem Description
This description is taken from the Author of the Kata (Problem).
We want to create an interpreter of assembler which will support the following instructions:

* `mov x, y` - copy y (either an integer or the value of a register) into register x.
* `inc x` - increase the content of register x by one.
* `dec x` - decrease the content of register x by one.
* `add x, y` - add the content of the register x with y (either an integer or the value of a register) and stores the result in x (i.e. register[x] += y).
* `sub x, y` - subtract y (either an integer or the value of a register) from the register x and stores the result in x (i.e. register[x] -= y).
* `mul x, y` - same with multiply (i.e. register[x] *= y).
* `div x, y` - same with integer division (i.e. register[x] /= y).
* `label:` - define a label position (`label = identifier + ":"`, an identifier being a string that does not match any other command). Jump commands and call are aimed to these labels positions in the program.
* `jmp lbl` - jumps to the label `lbl`.
* `cmp x, y` - compares x (either an integer or the value of a register) and y (either an integer or the value of a register). The result is used in the conditional jumps (`jne`, `je`, `jge`, `jg`, `jle` and `jl`)
* `jne lbl` - jump to the label `lbl` if the values of the previous `cmp` command were not equal.
* `je lbl` - jump to the label `lbl` if the values of the previous `cmp` command were equal.
* `jge lbl` - jump to the label `lbl` if x was greater or equal than y in the previous `cmp` command.
* `jg lbl` - jump to the label `lbl` if x was greater than y in the previous `cmp` command.
* `jle lbl` - jump to the label `lbl` if x was less or equal than y in the previous `cmp` command.
* `jl lbl` - jump to the label `lbl` if x was less than y in the previous `cmp` command.
* `call lbl` - call to the subroutine identified by `lbl`. When a `ret` is found in a subroutine, the instruction pointer should return to the instruction next to this `call` command.
* `ret` - when a `ret` is found in a subroutine, the instruction pointer should return to the instruction that called the current function.
* `msg 'Register: ', x` - this instruction stores the output of the program. It may contain text strings (delimited by single quotes) and registers. The number of arguments isn't limited and will vary, depending on the program.
* `end` - this instruction indicates that the program ends correctly, so the stored output is returned (if the program terminates without this instruction it should return the default output: see below).
* `; comment` - comments should not be taken in consideration during the execution of the program.

### Output format:
The normal output format is a string (returned with the end command). For Scala and Rust programming languages it should be incapsulated into Option.

If the program does finish itself without using an end instruction, the default return value is:

```
-1 (as an integer)
```

### Input format:
The function/method will take as input a multiline string of instructions, delimited with EOL characters. Please, note that the instructions may also have indentation for readability purposes.

For example:
```c
char *program = "\
  ; My first program\n\
  mov  a, 5\n\
  inc  a\n\
  call function\n\
  msg  '(5+1)/2 = ', a    ; output message\n\
  end\n\
  \n\
  function:\n\
    div  a, 2\n\
    ret\n\
  ";
assembler(program);
```
The above code would set register a to 5, increase its value by 1, calls the subroutine function, divide its value by 2, returns to the first call instruction, prepares the output of the program and then returns it with the end instruction. In this case, the output would be (5+1)/2 = 3.

## My Implementation Description
In this program I wrote an implementation of Dynamic Arrays which can expand in real time once the number of elements added to it exceeds its capacity.
I used it to hold the parsed lines of the program whatever the number of lines it contains, that is instead of using a fixed array of a large size.

It accepts `void *` types so it can be used as a generic implementation of the Dynamic Array data structure.
I also wrote an implementation of Hashtables that takes `(string, uint64_t)` Key-Value pairs. It is made specifically to hold pairs of labels and their addresses, hence the Integer type Value.

### How It Works
* `assembler` takes in a multilined string that contains instructions, labels and comments then passes it `parse_program`.
* `parse_programs` separates each line, removes comments, extracts labels from the string then refactors the remaining instruction lines to be used in the next step.
* `run_program` passes each line to `parse_inst` which parses each instruction and executes it by calling the corresponding function which in turn keeps the results in the registers array.
* Usually each program contains a `msg` instruction that can be used to output a combination of strings and register values, only if the program contains an `end` instruction, otherwise it returns a `-1` .

### How to Run
Call `make` and the executable will be created in the build directory with `assembler` as its name.
``` bash
$ make
```
Then you can either run it without providing an assembly file as a command-line argument, which will run the `power_program` string by default
``` bash
$ ./build/assembler
```
Or you can provide an assembly file to the command to run it, by providing its path as an argument.
``` bash
$ ./build/assembler program/first_program.asm
```

### Notes
* This implementation is far from perfect, I've done a fair share of manual unit tests to most of the units in the program, but it is not enough of course, so bugs and errors can happen here or there.
* I used `sscanf` instead of the far superior regex expressions library, due to coding in Windows, which doesn't have the Linux `regex` library, but I may use PCRE later instead.
