# pointer.c break down

## Prologue
### <main+0>
``` asm 
0x100003ec0 <main>      push   %rbp
```
#### Operation
Push the current base pointer onto the stack.
#### Purpose
Save the base pointer from the calling function on the stack
to establish a stack frame for the current function.

### <main+1>
``` asm
0x100003ec1 <main+1>    mov    %rsp,%rbp
```
#### Operation
Move the stack pointer **value** onto the base pointer.
#### Purpose
Set up the base pointer for the current stack frame.
Allows local varibales & function parameters to be accessed
realtive to %rbp.

### <main+4>
``` asm
0x100003ec4 <main+4>    sub    $0x30,%rsp
```
#### Operation
Subtract `0x30` from the stack pointer.
#### Purpose
Allocates `0x30` bytes of space onto the stack for local variables.

### <main+8>
``` asm
0x100003ec8 <main+8>    mov    0x139(%rip),%rax      # 0x100004008
```
#### Operation
Load the effective address of the instruction pointer of a global variable or memory location into rax.
#### Purpose
To access a global variable or mem location that's used in the function. `0x100004008` is likely a reference to a global 
or static variable. 

### <main+15>
``` asm
0x100003ecf <main+15>   mov    (%rax),%rax
```
### Operation
Dereference the memory address contained in the RAX register and load it back into the rax value.
### Purpose
Loads in the contents of the pointer.

### <main+18>
``` asm
0x100003ed2 <main+18>   mov    %rax,-0x8(%rbp)
```
### Operation
Move the value dereferenced value to the memory location 8 bytes above the base pointer.
### Purpose
Probably storing the pointer.

### <main+22>
``` asm
0x100003ed6 <main+22>   lea    -0x20(%rbp),%rdi
```
### Operation
Load the effective address from the memory location `0x20` bytes above the base pointer and move it into the destination index.
The destination index is usually pass args into fucntions.
### Purpose
Prepare the first agrument for a function call. Probably for `strcpy`.

### <main+26>
``` asm 
0x100003eda <main+26>   lea    0xa3(%rip),%rsi        # 0x100003f84
```
### Operation
Load the effective address offset by 0xa3 bytes from the instruction pointer into the stack index.
### Purpose
Likely loading the address of "Hello, world!\n".

### <main+33>
``` asm 
0x100003ee1 <main+33>   mov    $0x14,%edx
```
### Operation
Move the immediate value 0x14 (20 in decimal) into the EDX register.
### Purpose
Might be setting up a length or size argument for a function.

### <main+38>
``` asm
0x100003ee6 <main+38>   call   0x100003f78
```
### Operation
Call the function at the address `0x100003f78`.

