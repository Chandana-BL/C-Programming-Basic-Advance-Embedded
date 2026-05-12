/*
Date:07.05.2026
1. Arrays
2. Pointers
3. Functions
4. Loops

Understanding the memory -> then realistic emebeded problems solve

*/


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_DATA_SIZE 32

char rx_circular_buffer[MAX_DATA_SIZE] ={0};
uint8_t head = 0;
uint8_t tail = 0;
volatile uint8_t overflow_flag = 0;
volatile uint8_t count = 0;

void write_into_rx_circular_buffer(char sensor_data);
int read_from_rx_circular_buffer(char *c);
void on_frame_complete(char label, int value);
void parse_data(char c);

int main(int argc, char const *argv[])
{
    //TEST CODE
    /*
    int arr[10] = {1,2,3,4,5,6,1,2};
    arr[11] = 10;
    printf("%d",arr[10]);
    */

    // 01. Reverse array
    /*
    char array[5] = {1,2,3,4,5};

    int length = sizeof(array)/sizeof(array[0]);

    for(int i = 0; i <= (length -1)/2 ; i++){
        char temp = array[i];
        array[i] = array[length-1-i];
        array[length-1-i] = temp;
    }
    for(int i = 0; i <= length-1;i++){
        char rev_array = array[i];
        printf(" %d ", rev_array);
    }
   */

   // 02. Find Maximum Element in array
    /*
   char array[5] = {1,2,30,4,5};

   int length = sizeof(array)/sizeof(array[0]);

   char max_element = array[0];

   for(int i = 0; i <= length - 1; i++){
       if ( array[i] > max_element){
        max_element = array[i];
       }
   }
   printf("MAX Element : %d", max_element);
*/
   //03. Second Max element
/*
   char array[5] = {1,127,30,4,5};

   int length = sizeof(array)/sizeof(array[0]);

   char max_element = array[0];
   char secmax_element = array[0];

   for(int i = 1; i <= length - 1; i++){
       if ( array[i] > max_element){
        secmax_element = max_element;
        max_element = array[i];
}
        else if (array[i] > secmax_element){
            secmax_element = array[i];
        }
   }
   printf("MAX Element : %d ; Sec-MAX Element : %d", max_element, secmax_element);
*/
/*

    //04. Sentinel Traverse - for unknow array length
    // Problem Statment : UART data parser and extract data as per labels

    char uart_data[] = "xyz$T270H121D190#xyzc"; // $ = start, T = temp label, H is humid label, # is end, rest all garbage
    
    typedef enum {
        WAITING_FOR_START,
        START,
        DONE
    }STATE;

    int i = 0;
    int status = 0u;
    char labels[10] = {0};
    int data[10] = {0};
    int index = 0;
    int num = 0;
    bool first_label = true;

    while(uart_data[i]){

        if(uart_data[i] == '$') status = START;
        if(status == WAITING_FOR_START){
            i++;
            continue;
        } 
        else if(status == DONE) break;
        
        if (status == START){
            if(uart_data[i] >= 65 && uart_data[i] <= 90){ 
                if (!first_label) index++;
                labels[index] = uart_data[i];
                num = 0;
                first_label = false;
            }
            else if (uart_data[i] >= 48 && uart_data[i] <= 57){
                num = num * 10 + (uart_data[i] - '0');
                data[index] = num;
            }
        }
        i++;        
    }
    if(!first_label) index++;

    for (int i = 0; i < index ; i++){
        printf("%c : %d \n", labels[i],data[i]);
    }
    
    // Learnings : 
    // 1. if 2 arrays shares the same index -> should handle it properly to avaid sync
    // 2. while or any loops -> always watch out to the infinite condition, the index in while should increement, even if it won't parse data at that time
    // 3. In run-time data length scenario -> the incremented index will be the length , but watch out to empty length case ( if you do <= index -> for data works , if empty = garbag
    //  so, make sure to use < index ( nad to miss the last stored data always increment index after loop)) -> example explained but take care of the edge cases liek empty array etc..
    
    */

    //04. Circular buffer -> index shifting instead element shifting
    // 1. Data keeps coming from the sensor like -> $T10#, $H10# -> uart buffer recives one at atime
    // Have 8bit char rx_buffer -> use circular shifting to store continuous streaming data
    // Also read meanwhile each data -> write 1 read previous one
    // I use 2 function(API) -> one to write and other 2 read & this data comes from the big array continuously

    char sensor_stream[] = "$T20#$H22#$T15#$H45#$P101#$T22#$H50#$T18#$H48#$P100#"
"$T25#$H55#$T19#$H47#$P102#$T21#$H52#$T17#$H49#$P99#";
    char c;

    for (int i = 0; sensor_stream[i] != '\0' ; i++){
        if (!overflow_flag){
            write_into_rx_circular_buffer(sensor_stream[i]);
            while(read_from_rx_circular_buffer(&c)){
            parse_data(c);
        }
        
    }
        if (overflow_flag){
            overflow_flag = 0;
        }
    }

    return 0;
}

void write_into_rx_circular_buffer(char sensor_data){
    
    if (count >= MAX_DATA_SIZE){
        overflow_flag = 1;
        return;
    }
   
        rx_circular_buffer[head] = sensor_data;
        head = (head + 1) % 8u;
        count++;    
}

int read_from_rx_circular_buffer(char *c){
    if (count == 0) return 0;
    *c = rx_circular_buffer[tail];
    tail = (tail + 1) % 8u;
    count--;
    return 1;
}

typedef struct {
    int temp;
    int humidity;
    int pressure;
}SensorData;

typedef enum {
    UNKNOWN,
    START,
    LABEL_FOUND,
    DATA_FOUND
}data;

SensorData g_sensor = {0};

void parse_data(char c){
    static int status = UNKNOWN;
    static char label = 0;
    static int data = 0;

    if (c == '$'){
        status = START;
        data = 0;
        label = 0;
        return;
    }

    if (c == '#'){
       if (status != UNKNOWN && label != 0) {
            on_frame_complete(label, data);
        }
        status = UNKNOWN;
        return;
    }

    if (status == UNKNOWN) return;

    if (status == START){
        if (c == 'H' || c =='P' || c =='T'){
        label = c;
        status = LABEL_FOUND;
    }
    }

    else if (status ==LABEL_FOUND){
        if ((c -'0') >= 0 && (c - '0') <= 9){
        data = data * 10 + (c-'0');
    }
    }   
}

void on_frame_complete(char label, int value){
    switch (label){
        case 'T' : g_sensor.temp = value;
                   printf("\nTemp data : %d",g_sensor.temp);
                   break;
        case 'H' : g_sensor.humidity = value; 
                    printf("\nHumid data : %d",g_sensor.humidity);            
                    break;
        case 'P' : g_sensor.pressure = value; 
                    printf("\nPressure data : %d",g_sensor.pressure); 
                    break;
    }
}