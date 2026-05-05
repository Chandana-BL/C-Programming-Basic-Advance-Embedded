/*
Challenge: UART Command Parser

You receive characters one by one.

void process_char(char c);

Requirement:

* Detect command "ON" → turn LED ON
* Detect command "OFF" → turn LED OFF
* Input comes one char at a time
* Example stream: O N X O F F

Constraint:

* No strings (strcmp not allowed)
* Use only char and state tracking
*/

#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

enum STATES {
    IDLE,
    GET_O,
    GET_ON,
    GET_OF
};

int process_char(char c){
  // Step 1: convert to upper case ( if lower)
  if (c > 'a' && c < 'z'){
    c -= 32;
  }
  //step 2: usage of static to keep the previous detected value

  static int state = IDLE;
  
  switch(state){
    case 0:
    {
        if( c == 'O'){
            state = GET_O;
            
        }
        break;
    }
    case 1:
    {
        if ( c == 'N'){
            state = GET_ON;
        }
        else if ( c == 'F'){
            state = GET_OF;
        }
        else{
            state = IDLE;
        }
        break;
    }
    case 2:
    case 3:{
        if (c == 'O'){
            state = GET_O;
            break;
        }
        else{
        state = IDLE;
            break;  
        }
    }
   
  }

  return state;
}

void print_state(char c) {
    int s = process_char(c);
    printf("%s\n",
        s == IDLE   ? "IDLE"   :
        s == GET_O  ? "GET_O"  :
        s == GET_ON ? "LED_ON" :
        s == GET_OF ? "LED_OFF":
                      "UNKNOWN");
}

int main(int argc, char const *argv[])
{
    print_state('O');
    print_state('F');
    print_state('O');
    print_state('N');
    print_state('F');
    print_state('O');
    print_state('X');
    print_state('O');
    print_state('N');

    
    return 0;
}


/*
Challenge 2 :
Call LED_ON & LED_OFF commands once strings are parsed.
Current status : only detects and prints the current state.

*/
