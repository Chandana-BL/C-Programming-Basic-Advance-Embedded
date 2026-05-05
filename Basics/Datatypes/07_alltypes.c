/*
Battery Monitoring System (Mini)

Simulate:

* ADC value (uint16_t)
* Threshold (const)
* Status flag (volatile)
* State machine (static)
* Boolean decisions

Requirement:

* If voltage < threshold → trigger warning
* Maintain previous state
* Handle noise (boolean debounce logic)

*/

#include <stdio.h>
#include <stdint.h>
#include<stdbool.h>

const uint8_t THRESHOLD = 4; //4V
volatile bool FLAG;

typedef enum {
  STATUS_OK,
  STATUS_NOK
} BATTERY_STATUS;

volatile BATTERY_STATUS STATUS_FLAG = STATUS_OK;

// Status 

float ADC_value_generator(){
    const int adc_data[10] = {2,3,2,5,6,7,1,0,3,6};
    static int8_t index = 0;
    if (index <=10){
        return adc_data[index++];    
    }
    else{
        index = 0;
        return adc_data[index++];    
    }
}

void update_battery_status(uint16_t adc_data){
    static uint8_t debounce_counter = 0u;
      if (adc_data < THRESHOLD){ 
        debounce_counter++;

        if (debounce_counter == 3){
            if (STATUS_FLAG != STATUS_NOK){ 
            STATUS_FLAG  = STATUS_NOK;  
                   
            printf("\nLOW BATTERY LEVEL\n");
            }            
            debounce_counter = 0; 
        }
        }
        else{
                STATUS_FLAG = STATUS_OK;
            }
}
int main(int argc, char const *argv[])
{
    for( int i =0; i <10; i++){
        uint16_t adc_data = ADC_value_generator();
        printf("\nADC data : %d",adc_data);
        update_battery_status(adc_data);
    }
       
    return 0;
}