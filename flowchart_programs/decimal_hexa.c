// C Program to demonstrate Decimal to Hexadecimal 
// Conversion using the modulus division operator 
#include <stdio.h> 
  
int main() 
{ 
  
    int decimal_Number;
   printf("enter the decimal number:");
   scanf("%d",&decimal_Number); 
    int i = 1, j, temp; 
    char hexa_Number[100]; 
    
    // if decimal number is not  
    // equal to zero then enter in 
    // to the loop and execute  
    // the statements 
    while (decimal_Number != 0) { 
        temp = decimal_Number % 16; 
        
        // converting decimal number  
        // in to a hexa decimal 
        // number 
        if (temp < 10) 
            temp = temp + 48; 
        else
            temp = temp + 55; 
        hexa_Number[i++] = temp; 
        decimal_Number = decimal_Number / 16; 
    } 
    // printing the hexa decimal number 
    printf("Hexadecimal value is: "); 
    for (j = i - 1; j > 0; j--) 
        printf("%c", hexa_Number[j]); 
  
    return 0; 
}
