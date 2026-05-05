/*
Challenge: Software Debounce Logic

Simulate a noisy button input.

bool is_button_pressed(bool raw_signal);

Requirement:

* Input: noisy signal like → 1 0 1 1 0 1 1 1
* Output should be true only if signal is stable HIGH for 3 consecutive reads

Constraint:

* Use static variable internally
* No arrays allowed

*/
#include <stdio.h>
#include<stdint.h>
#include <stdbool.h>

bool detect_edge(bool prev_sig, bool current_sig){
    static bool edge_detected = false;
    if (!prev_sig && current_sig){
        edge_detected = true;
        return edge_detected;
    }
    edge_detected = false;
    return edge_detected;
}

bool is_button_pressed(bool raw_signal){
    static bool button_pressed = false;
    static uint8_t count = 0;
    static bool previous_state = false;
    static bool current_state;
    current_state = raw_signal;
    printf("%d,%d",previous_state, current_state);
    bool edge_detected = detect_edge(previous_state,current_state);
    
    printf(edge_detected ? "\nEDGE DETECTED\n" : "\nNOT DETECTED\n");

    if (raw_signal){
        previous_state = true;
    }
    if (!raw_signal){
        count = 0;
        button_pressed = false;
        previous_state = false;
        return button_pressed;
    }
    
    if (++count >= 3){
        count = 3;
        button_pressed = true;
    }

    return button_pressed;
}
void tick(bool signal) {
    if (is_button_pressed(signal))
        printf("Input %d -> BUTTON PRESSED\n", signal);
    else
        printf("Input %d -> NOT PRESSED\n", signal);
}

int main(void) {
    tick(1);
    tick(0);
    tick(1);
    tick(0);
    tick(1);
    tick(1);
    tick(1);  
    tick(1); 
    tick(1); 
    tick(1); 
    tick(1); 
    tick(1); 
    tick(0);
    return 0;
}

/*
Challenge 2:

Detected the rising edge press :
E.g, when 0 -> 1 only detect

*/