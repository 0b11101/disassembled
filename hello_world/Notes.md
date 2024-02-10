# Hello_World.c break down
AT&T Syntax compiled with gcc disassebled in gdb

## <main+15>
### Operation: 
Move the literal '0' into the memory location 8 bytes
           above the base pointer.
### Purpose: 
Initialize the local variable 'i' to 0 & define -0x4(%rpb)
         (i.e. 4 bytes above the current bp location) as the location
         where it'll be stored.
0x0000000100003f4f <+15>:    movl   $0x0,-0x8(%rbp)

### Notes 
When setting a break-point at main & running the first
break happens at line 6 
``` c
for(i=0; i<10; i++)
```
which correlates to 
``` asm
B+>0x100003f4f <main+15>   movl   $0x0,-0x8(%rbp)
```
This correlates to line 5 ` int i; `
`i` is being initialized to `0` & stored in the memory location `-0x8(%rbp)`.

#### Investigating -0x8(%rbp)
The address at `%rbp - 0x8` is address `0x7ff7bfeff3b8`.
##### 0x7ff7bfeff3b8
``` asm
(gdb) x/4xb 0x7ff7bfeff3b8
0x7ff7bfeff3b8: 0x90    0x1b    0x60    0x00
(gdb) nexti # this runs <main+15>
(gdb) x/4xb 0x7ff7bfeff3b8                               
0x7ff7bfeff3b8: 0x00    0x00    0x00    0x00
```
This confirms that this is `int i`.

## <main+22>
Operation: Compare the value 0xa with the value at the memory locaiton
           8 bytes above the base pointer.
Purpose: Checks if i < a in the loop condition. The comparison result
         is used by the subsequent conditional jump instruction.
0x0000000100003f56 <+22>:    cmpl   $0xa,-0x8(%rbp)

Notes:
Still in line 6 of the C code. 
Checks to see if `i` is equal to `0xa` and passes that value to the next instruction.

## <main+26>
Operation: Jump to 0x100003f7c <main+60> if the prev comparision in 
           greater than or equal.
Purpose: Exiting the for loop when i is >= 10. 
0x0000000100003f5a <+26>:    jge    0x100003f7c <main+60>

Notes:
If the result of the last value was greater-than or equal-to jump to <main+60>.

## <main+32>
Operation: load effective address (lea) of the string "Helo, World\n"
           into %rdi. 
Purpose: Prepares the first argument for the printf call, which is the
         address of the format string. 
0x0000000100003f60 <+32>:    lea    0x23(%rip),%rdi        # 0x100003f8a
Notes:  
This only happens when the prev. check fails...
Two lines below we see a call instruction suggesting that the address is being used as an argmument to a function.
Here the effective address of rip + 0x23 is loaded into (LEA) %rdi.
The effective address of the instruction pointer is the addrenn of the NEXT instruction—i.e. <main+32>.
This address is listed in the comments of the disassembly as `# 0x100003f8a`.
The contents of that address are `0x100003f8a:    "Hello, world!\n"`
The destination index (`rdi`) is commonly used for the first argument in function calls.

## <main+39>
### Operation: 
Move 0 into %al
### Purpose: 
Clears the %al register.
Notes: The %al register is to indicate the number of floating-point 
       parameters passed in vector registers for variadic functions
       like printf. There are none in this case.
0x0000000100003f67 <+39>:    mov    $0x0,%al

## <main+41>
### Operation: 
Call the function at the address 0x100003f84  
### Purpose: 
Calls printf. The actual address of printf is resolved at runtime.
Notes: Examaning that address won't tell you that printf is that function
       without compliling the source with symbols. All we know here is 
       that a function is being called. 2 lines above we see the rdi register 
       being populated with "Hello, World\n" and it's safe to assume that 
       this funciton call would be using that.
0x0000000100003f69 <+41>:    call   0x100003f84

## <main+46>
### Operation: 
Move the value from 8 bytes above the base pointer
           into %eax
### Purpose: 
Loads the value i into %eax for incrementing.
Notes: We know it's for incrementing because of the next line.
0x0000000100003f6e <+46>:    mov    -0x8(%rbp),%eax

## <main+49>
### Operation: 
Add 1 to %eax
### Purpose: 
Increment i
0x0000000100003f71 <+49>:    add    $0x1,%eax

## <main+52>
### Operation: 
Move the value in %eax back to 8 bytes above %rbp
### Purpose: 
Stores the incremented value of i back into its location
0x0000000100003f74 <+52>:    mov    %eax,-0x8(%rbp)

## <main+55>
### Operation: 
Unconditional jump back to the address 
           0x0000000100003f56 <+22>:    cmpl   $0xa,-0x8(%rbp)
### Purpose: 
Continue the loop
0x0000000100003f77 <+55>:    jmp    0x100003f56 <main+22>

## <main+60>
### Operation: 
Exclusive or %eax with itself
### Purpose: 
Clears %eax to return 0 from main() 
Notes:0 is the return value of main()
0x0000000100003f7c <+60>:    xor    %eax,%eax

## <main+62>
### Operation: 
Add 0x10 to the stack pointer.
### Purpose: 
Deallocates the 0x10 bytes from <+4main> 
         sub    $0x10, %rsp. 
Notes: Space was allocated on the stack for local variables
0x0000000100003f7e <+62>:    add    $0x10,%rsp

## <main+66>
### Operation: 
Pop the top of the stac into the base pointer.
### Purpose: 
Restore the base pointer %rbp to its value before 
         the function calls.
Notes: Unwinds the current stack frame.
0x0000000100003f82 <+66>:    pop    %rbp

## <main+67>
### Operation: 
Return from the function.
### Purpose: 
Pops the return address of the stack and jumps to it, returning control
         to the calling function.
0x0000000100003f83 <+67>:    ret

# Before break-point
## <main+0>
### Operation: 
Push the current base pointer onto the stack
### Purpose: 
Save the base pointer from the calling funciton on the stack
         to establish a stack frame for the current func 'main()'
0x0000000100003f40 <+0>:     push   %rbp

## <main+1>
### Operation: 
Move the stack pointer value to the base pointer.
### Purpose: 
Set up the base pointer for the current stack frame. Allows
         local variables & function parameters to be accessed realitive
         to %rbp.
0x0000000100003f41 <+1>:     mov    %rsp,  %rbp

## <main+4>
### Operation: 
Subtrack 0x10 from the stack pointer.
### Purpose: 
Allocates 0x10 bytes of space onto the stack for local vars.
         This is for the int i; on line 5 plus some extra padding.
         An int in C has either 2 or 4 bytes depending on the OS.
0x0000000100003f44 <+4>:     sub    $0x10, %rsp

## <main+8>
### Operation: 
Move the literal '0' into the memory location 4 bytes
           above the base pointer.
### Purpose: 
Appears to be setting up another local variable or temporary
         space to 0. Might be unused or reserved for other reasons.
0x0000000100003f48 <+8>:     movl   $0x0,-0x4(%rbp)

## <main






