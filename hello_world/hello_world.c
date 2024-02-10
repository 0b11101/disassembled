#include <stdio.h>

int main()
{
  int i;
  for(i=0; i < 10; i++)
  {
    printf("Hello, world!\n");
  }
  return 0;
}

/* AT&T Syntax compiled with gcc disassebled in gdb
Dump of assembler code for function main:
   instr addr               operation  source  destination (stack)

   Operation: Push the current base pointer onto the stack
   Purpose: Save the base pointer from the calling funciton on the stack
            to establish a stack frame for the current func 'main()'
   0x0000000100003f40 <+0>:     push   %rbp

   Operation: Move the stack pointer value to the base pointer.
   Purpose: Set up the base pointer for the current stack frame. Allows
            local variables & function parameters to be accessed realitive
            to %rbp.
   0x0000000100003f41 <+1>:     mov    %rsp,  %rbp

   Operation: Subtrack 0x10 from the stack pointer.
   Purpose: Allocates 0x10 bytes of space onto the stack for local vars.
            This is for the int i; on line 5 plus some extra padding.
            An int in C has either 2 or 4 bytes depending on the OS.
   0x0000000100003f44 <+4>:     sub    $0x10, %rsp

   Operation: Move the literal '0' into the memory location 4 bytes
              above the base pointer.
   Purpose: Appears to be setting up another local variable or temporary
            space to 0. Might be unused or reserved for other reasons.
   0x0000000100003f48 <+8>:     movl   $0x0,-0x4(%rbp)

   Operation: Move the literal '0' into the memory location 8 bytes
              above the base pointer.
   Purpose: Initialize the local variable 'i' to 0 & define -0x4(%rpb)
            (i.e. 4 bytes above the current bp location) as the location
            where it'll be stored.
   0x0000000100003f4f <+15>:    movl   $0x0,-0x8(%rbp)

   Operation: Compare the value 0xa with the value at the memory locaiton
              8 bytes above the base pointer.
   Purpose: Checks if i < a in the loop condition. The comparison result
            is used by the subsequent conditional jump instruction.
   0x0000000100003f56 <+22>:    cmpl   $0xa,-0x8(%rbp)

   Operation: Jump to 0x100003f7c <main+60> if the prev comparision in 
              greater than or equal.
   Purpose: Exiting the for loop when i is >= 10. 
   0x0000000100003f5a <+26>:    jge    0x100003f7c <main+60>

   Operation: load effective address (lea) of the string "Helo, World\n"
              into %rdi. 
   Purpose: Prepares the first argument for the printf call, which is the
            address of the format string. 
   Notes: %rdi is often used for the first argument in function calls. 
          Two lines below we see a call instruction suggesting that the 
          address is being used as an argmument to a function.
          Examaning the address (x/s 0x100003f8a) shows
          0x100003f8a: "Hello, world!\n"
   0x0000000100003f60 <+32>:    lea    0x23(%rip),%rdi        # 0x100003f8a

   Operation: Move 0 into %al
   Purpose: Clears the %al register.
   Notes: The %al register is to indicate the number of floating-point 
          parameters passed in vector registers for variadic functions
          like printf. There are none in this case.
   0x0000000100003f67 <+39>:    mov    $0x0,%al

   Operation: Call the function at the address 0x100003f84  
   Purpose: Calls printf. The actual address of printf is resolved at runtime.
   Notes: Examaning that address won't tell you that printf is that function
          without compliling the source with symbols. All we know here is 
          that a function is being called. 2 lines above we see the rdi register 
          being populated with "Hello, World\n" and it's safe to assume that 
          this funciton call would be using that.
   0x0000000100003f69 <+41>:    call   0x100003f84
   
   Operation: Move the value from 8 bytes above the base pointer
              into %eax
   Purpose: Loads the value i into %eax for incrementing.
   Notes: We know it's for incrementing because of the next line.
   0x0000000100003f6e <+46>:    mov    -0x8(%rbp),%eax

   Operation: Add 1 to %eax
   Purpose: Increment i
   0x0000000100003f71 <+49>:    add    $0x1,%eax

   Operation: Move the value in %eax back to 8 bytes above %rbp
   Purpose: Stores the incremented value of i back into its location
   0x0000000100003f74 <+52>:    mov    %eax,-0x8(%rbp)

   Operation: Unconditional jump back to the address 
              0x0000000100003f56 <+22>:    cmpl   $0xa,-0x8(%rbp)
   Purpose: Continue the loop
   0x0000000100003f77 <+55>:    jmp    0x100003f56 <main+22>

   Operation: Exclusive or %eax with itself
   Purpose: Clears %eax to return 0 from main() 
   Notes:0 is the return value of main()
   0x0000000100003f7c <+60>:    xor    %eax,%eax

   Operation: Add 0x10 to the stack pointer.
   Purpose: Deallocates the 0x10 bytes from <+4main> 
            sub    $0x10, %rsp. 
   Notes: Space was allocated on the stack for local variables
   0x0000000100003f7e <+62>:    add    $0x10,%rsp

   Operation: Pop the top of the stac into the base pointer.
   Purpose: Restore the base pointer %rbp to its value before 
            the function calls.
   Notes: Unwinds the current stack frame.
   0x0000000100003f82 <+66>:    pop    %rbp

   Operation: Return from the function.
   Purpose: Pops the return address of the stack and jumps to it, returning control
            to the calling function.
   0x0000000100003f83 <+67>:    ret
End of assembler dump.
*/
