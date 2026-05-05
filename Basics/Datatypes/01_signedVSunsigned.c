/*
Challenge : Overflow Detector(Without using flags)
Requirement:

* Return 1 if signed overflow occurs, else 0
* You are NOT allowed to use compiler flags or built-in overflow checks
* Use only logic and bit understanding

Hint:

* Overflow happens when:
    + * + → -
    - * - → +

Test cases:

* 100 + 30 → overflow
* -100 + -40 → overflow
* 50 + 20 → no overflow

*/
#include<stdio.h>
#include<stdbool.h>

int detect_overflow(__int8,__int8);

int main(void)
{
    
    __int8 num1 = -1;
    __int8 num2 = -1;

    __int8 result = detect_overflow(num1,num2);

    if (result){
        printf("OVERFLOW");
    }
    else{
       printf("NON-OVERFLOW"); 
    }

    return 0;
}

int detect_overflow(__int8 num1,__int8 num2){

    __int8 result = num1 + num2;

    bool result_sign = result & 0x80;
    bool num1_sign = num1 & 0x80;
    bool num2_sign = num2 & 0x80;

    printf("%d , %d, %d",num1_sign,num2_sign, result);

    // if (~(result_sign) & num1_sign & num2_sign){
    //     return 1; // 1 : overflow, 0: not overflow
    // }
    // else if ((result_sign) & (num1_sign | num2_sign)){
    //     return 1;
    // }
    // else if (~(result_sign) & (num1_sign | num2_sign)){
    //     return 0;
    // }
    // else if ((result_sign) & (~num1_sign | ~num2_sign)){
    //     return 1;
    // }
    // else if (~(result_sign) & (~num1_sign | ~num2_sign)){
    //     return 0;
    // }

    // onliner
    if ((num1_sign == num2_sign) && (result_sign != num1_sign)){
        return 1;
    }
    else{
        return 0;
    }

}

/*Challenge 2:

- Identify which type of overflow -> Negative overflow or Positive overflow
- E.g: if - + - => + ->positive OV, + + + => - -> neg OV


*/
