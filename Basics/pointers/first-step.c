/*
First-step:
Understanding : syntax, declaration, memory view
*/

/*
Learnings:

"Address itself is the data"

1. int *ptr; -> type affects the compiler behaviour, if we use char pointer then we only access 1 byte of data from that memory /
                if type is int it access 4 bytes.
                *Also has effect on pointer arithmatic operation Eg: ptr++ -> if char increment by 1, if int increement by 4
                Finally it tells compiler : how many bytes to access, how to interprete those bytes, how pointer arithmatic works
                LDR for int type, LDRB for char type -> this is what MCU sees.
2. Casting *(uint32_t*)ADDRESS -> Compiler creates temporary pointer to read 32 bits and the outer *(deference) reads from memory.
                                  Y this exist : in embedded we already know the addres of peripherals and all, storing it again in new var is just redundant data in RAm/stack

                                  Try : int *ptr = &(*(char*)&data); and observe how copiler thinks/interpretes 

*/
// What i know about pointers already
// 1. to define a varible pointer
#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    /*  01. type effect on compilation 

   int data = 256;
   int *ptr = &data;
   char *cptr = &data;
    
    printf("int ptr data : %d, char ptr data : %d",*ptr,*cptr);
    // output : int ptr data : 256, char ptr data : 0
    // Give it a guess why so!
    */
    
    /* 02. casting behaviour
    
    int data1 = 256;
    int *ptr = (char*)&data1; // Compiler showes warning and always the pointer type is considered to interprete bytes, think y?
    printf("casted data (int -> char): %d",*ptr);

    int data = 256;
    int ptr1 = *(char*)&data;
    printf("casted data (int -> char): %d",ptr1);

    */
    
    return 0;
}