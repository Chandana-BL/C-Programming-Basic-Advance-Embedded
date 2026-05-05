/*
5. ⚡ volatile

Challenge: Register Polling Bug

Simulate a hardware register:

uint8_t status_reg = 0;

Task:

Write:

void wait_for_flag();

Requirement:

* Loop until bit 0 becomes 1

while (!(status_reg & 0x01));

Then:

* Simulate another function updating status_reg
* Observe behavior with and without volatile

Goal:

* Demonstrate why optimization breaks logic

👉 Add comments explaining:

* What compiler might do
* Why volatile fixes it
*/
#include<stdio.h>
#include<stdint.h>

uint8_t status_reg = 0;

void wait_for_flag(){
  while (!(status_reg & 0x01));
}

int main(int argc, char const *argv[])
{
    wait_for_flag();
    return 0;
}


/*
 - Without volatile keyword -> compiler removes the status_reg
 - Without volatile -> reg stored in RAM

 - With volatile -> compiler keeps it even if there is no line of code udating this value
 - With volatile -> reg stores in RAM so it keeps visiting this address to see the updated value
*/