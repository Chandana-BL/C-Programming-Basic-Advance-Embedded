/*
 Understanding pointer++ -> it increments the access address by size of its type
 Declaration , Dereferencing, Accessing, Writing 
 Note : 
 1. *p++ -> *(p++) here ++ has first importance; means dereference and increement
 2. when we pass array in function call -> the function see it has address -> so sizeof(arr) inside function is invalid
    it checks the size of pointer not arrays.
 3. arr[10] ={} -> arr : pointer to first element ( arr++ -> gives next element address); 
                   &arr : pointes to whole array (&arr++ -> give after array byte address)
 4. call back functions -> these are passed as address to the function pointer eg. void (*call_back)(void); 
    whenever we call this function it_executes the function whose address is stored in it.


*/
#include <stdio.h>
#include <stdint.h>

void led_toggle(void);
void motor_start(void);
void Button_ISRHandler();
void Register_callback(void (*callback));
void (*call_back)(void);
// The ISR, Register_callback, and *call_back -> generally will be part of drivers

// void led_mode(void); // for C3 : need definition before use with printf statement
// void motor_mode(void);
// void sleep_mode(void);

void (*functions_of_array[2])(void)={motor_start,led_toggle};
void command_parser(uint8_t index);

typedef enum {
    START_MOTOR,
    BLINK_LED
} operations;

int main(void)
{
    /* Challenge 1:  Receive UART packet and Use pointer to read all bytes
   
   uint8_t UART_data[] = {0xAA, 0x05, 0x10, 0x20, 0x30, 0x40, 0x50};
   uint8_t *p = UART_data;
   uint8_t header = *(p);
   uint8_t length = *(p + 1);
   uint8_t *payload_address = p+2;

   printf("Header : %x\nLength : %d",header,length);
   printf("\nData : ");
   for (int a = 0; a < length;a ++){
    printf(" %x",*(payload_address++));
   }*/
    
   /*  Challenge 2 : Button Callback Handler
        Requirement: 2 function (led_toggle(), motor_start()), Function Pointer (stores callback),
                     one registrations function(accepts func pointer), one interrupt simulation(calls registered callback)
   
    
    Register_callback(led_toggle);
    Button_ISRHandler();
    Register_callback(motor_start);
    Button_ISRHandler(); */

   /*  Challenge 3 : Run time device mode switching -> same as before instead Button handler -> have scheduler func with switch(mode)*/

   /*  Challenge 4 : Smart Device Command Handler -> array of functions*/

   command_parser(START_MOTOR);
   command_parser(BLINK_LED);

    return 0;
}

void led_toggle(void){
    printf("LED_TOGGLED \n"); // In real embedded system we write into the register bit
}

void motor_start(void){
    printf("MOTOR_STARTED\n"); // IN rela emebedded system we give PWM to the motor
}

void Button_ISRHandler(void){
    call_back(); // calling call back funciton using pointer function
}

void Register_callback(void (*callback)){
    call_back = callback; // Assigning call back function to function pointer
}

void command_parser(uint8_t index){
    functions_of_array[index](); // Calling array function pointer
}
