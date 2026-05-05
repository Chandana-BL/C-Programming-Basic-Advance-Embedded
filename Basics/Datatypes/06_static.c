/*
6. 🧠 static

Challenge: Function Call Counter

int call_counter();

Requirement:

* Each time function is called → increment and return count
* Value must persist across calls
* Cannot use global variable

Expected:

call_counter() → 1
call_counter() → 2
call_counter() → 3

*/
#include<stdio.h>
#include<stdint.h>

static uint8_t call_counter = 0;

int call_counter_funct(){

return call_counter++;
}
int main(int argc, char const *argv[])
{
    for (int i=0; i<=5;i++){
        uint8_t count = call_counter_funct();
        printf("Count : %d\n",count);
    }
    
    return 0;
}

/*
Learnings:

- With static : variable available lifetime (because it will be stored in data segment)
                visible only in the initialised file
                init only once by compiler even it is inside funct call
*/