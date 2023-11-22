#include "String_to_array.h"
int input[22] = {0};

int* convertStrtoArr(String str, int* arr)
{
    // get length of string str
    int str_length = str.length();
    int negflag = 0;
    // create an array with size as string
    // length and initialize with 0
    //int arr[str_length] = { 0 };
 
    int j = 0, i, sum = 0;
 
    // Traverse the string
    for (i = 0; i<str.length(); i++) {
        if (str[i] == '-'){
          negflag = 1;
        }
        // if str[i] is ', ' then split
        if (str[i] == ',' || str[i] == '[' || str[i] == '-')
            continue;
         if (str[i] == ' ' || str[i] == ']' ){
            // Increment j to point to next
            // array location
            if(negflag == 1){
              arr[j] = arr[j] * -1;
            }
            j++;
            negflag = 0;
        }
        else {
 
            // subtract str[i] by 48 to convert it to int
            // Generate number by multiplying 10 and adding
            // (int)(str[i])
            arr[j] = arr[j] * 10 + (str[i] - 48);
        }
    }
 
//    for (i = 0; i <= j; i++) {
//        Serial.println(arr[i]);
//    }
//    Serial.println(" ");
    return arr;
}
