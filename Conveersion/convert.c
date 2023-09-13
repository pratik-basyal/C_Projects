 /**
 * Name : Pratik Basyal
 * CS 241L
*/

/************
 * DESCRIPTION:
 * This C program converts numbers between decimal, binary, and hexadecimal representations based on user-provided arguments. 
 * It includes functions for conversion, formatting, and error handling. 
 * The main function parses command-line arguments, performs conversions, and prints the results. 
 * The code ensures valid inputs, proper formatting, and limits the output to the specified number of bits.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

/**
 * Function that converts from decimal to binary.
*/
char* decimal_to_binary(unsigned long num, int bits)
{
    int count = 0;
    int index = 0;
    int i, j = 0, space_count = 0;
    char* binary = (char*) malloc(sizeof(char) * (bits+1)); /* allocate memory for the binary string */
    char* result = (char*) malloc(sizeof(char) * (bits+26)); /* allocate memory for the result string */

    /**
     * Here I counted bits, and tried to store result with formatted string
    */
    while(bits != 0)
    {
        if(count == 4)
        {
            binary[index] = ' ';
            count = 0;
            index++;
            continue;
        }

        binary[index] = num % 2 + '0';
        num = num / 2;
        index++;
        count++;
        bits--;
    }

    /**
     * This loop reverses the given result
    */
    for(i = index - 1; i >= 0; i--)
    {
        result[j] = binary[i];
        space_count++;
        j++;
    }
    result[index] = '\0'; /*terminate the result string with a null character*/

    free(binary); /* free the memory allocated for the binary string */

    return result;
}

/**
 * Function to remove spaces
 * I had to use this, to remove spaces from the binary number I got
 * from conversion of decimal_binary (-inD and -outD)
 * Since I had to read bits for formatting and I had to use decimal_to_binary function
*/
char* remove_spaces(const char* input) {
    int i, j;
    size_t len = strlen(input);
    char* result = malloc(len + 1);
    j = 0;
    for (i = 0; i < len; i++) {
        if (input[i] != ' ') {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';
    return result;
}

/**
 * Function that converts from binary to decimals
*/
unsigned long binary_to_decimal(char* binary_num, int bits)
{
    unsigned long num;
    unsigned long decimal;
    unsigned long binaryNum = strtoul(binary_num, NULL, 2);

    /**
     * here I am assigining the greates unsigned number, acoording to bits
     * and using "&" operator to simply remove unwanted bits.
    */
    if(bits == 8) num = 255;

    if(bits == 16) num = 65535;

    if(bits == 32) num = 4294967295;

    if(bits == 64) num = 9223372036854775807;
    
    if(binaryNum > num)
    {
        num = binaryNum & num;
        decimal = num;
    }
    else{
    decimal = binaryNum;
    }

    return decimal;
}

/**
 * Function that converts from decimal to hexa-decimal
*/
char* decimal_to_hex(unsigned long decimal, int bits)
{
    int req_bits = bits / 4; /* this is to count size, to put spaces*/
    int index = 0, count = 0;
    int remainder, i, j;
    char* hexa_result = malloc(sizeof(char) * (bits + 1));
    char* hexa = (char*) malloc(sizeof(char) * (bits+1));

    while(req_bits != 0)
    {
        remainder = decimal % 16;
        if(count == 2)
        {
            hexa[index] = ' ';
            count = 0;
            index++;
            continue;
        }
        if(remainder < 10)
        {
            hexa[index] = remainder + '0';
            index++;
            count++;
            req_bits--;
        }
        else{
            hexa[index] = remainder + 55;
            index++;
            count++;
            req_bits--;
        }
        decimal = decimal / 16;
    }

    /* Constructing the hexadecimal string in reverse order */
    j = 0;
    for(i = index - 1; i >= 0; i--)
    {
        hexa_result[j] = tolower(hexa[i]);
        j++;
    }
    hexa_result[j] = '\0'; /* Null-terminate the string */
    
    free(hexa);

    return hexa_result;
}

/**
 * Function to convert hexadecimal to decimal
*/
unsigned long hex_to_decimal(char* hex, int bits)
{
    unsigned long num;
    unsigned long hexa;
    unsigned long hexaNum = strtoul(hex, NULL, 16);

    /**
     * I used the same technique as for binary_to_decimal
    */
    if(bits == 8) num = 255;

    if(bits == 16) num = 65535;

    if(bits == 32) num = 4294967295;

    if(bits == 64) num = 9223372036854775807;
    
    if(hexaNum > num)
    {
        num = hexaNum & num;
        hexa = num;
    }
    else
    {
    hexa = hexaNum;
    }

return hexa;
}

/**
 * Function to convert binary to hexadecimal
 * I am just calling function from above, which makes it lot easier
*/
char* binary_to_hex(char* binary_str, int bits)
{
    
    unsigned long decimal = binary_to_decimal(binary_str, bits);

    return decimal_to_hex(decimal, bits);

}

/**
 * Function to convert hexadecimal to binary
*/
char* hex_to_binary(char* hexa, int bits)
{
    unsigned long decimal = hex_to_decimal(hexa, bits);

    decimal_to_binary(decimal, bits);

    return decimal_to_binary(decimal, bits);
}

/**
 * This function simply returns formatted decimal in string.
 * I used this in main function to put space, and comma accordinggly in string.
*/
char* format_to_decimal(unsigned long num, int bits)
{
    int i, count = 0, index = 0;
    char* decimal_result = malloc(sizeof(char) * (bits + 1));
    char* result = malloc(sizeof(char) * (bits + 1));
    char* final_result = malloc(sizeof(char) * (bits + 1));


    sprintf(decimal_result, "%lu", num); 

    for (i = strlen(decimal_result) - 1; i >= 0; i--) {
        if(count == 3)
        {
            result[index] = ',';
            index++;
            count = 0;
            i++;
            continue;
        }
        result[index] = decimal_result[i];
        index++;
        count++;
    }

    index = 0;
    for(i = strlen(result) - 1; i >= 0; i--)
    {
        final_result[index] = result[i];
        index++;
    }

    return final_result;
}


/**
 * Function to print formatted hexadecimal number.
 * I used similar concept as for decimal to hexa above.
*/

void hexa_to_hexa(char* str, int bits)
{
    int index = 0, count = 0, i;
    int req_bits = bits / 4;
    int length = strlen(str);

    char* hexa_result = malloc(sizeof(char) * (bits + 1));

    while(req_bits != 0)
    {
        if (count == 2)
        {
            hexa_result[index] = ' ';
            index++;
            count = 0;
            continue;
        }
        hexa_result[index] = str[length -1];
        req_bits--;
        length--;
        count++;
        index++;
    }

    for (i = strlen(hexa_result) - 1; i >= 0; i--)
    {
        printf("%c", hexa_result[i]);
    }
    printf("\n");
}
        
/*
* Function to print error message.
*/
void print_error()
{
printf("usage:\n");
printf("convert IN OUT SIZE NUMBER\n");
printf("  IN:\n");
printf("    -inB  NUMBER is binary.\n");
printf("    -inD  NUMBER is decimal.\n");
printf("    -inH  NUMBER is hexadecimal.\n\n");
printf("  OUT:\n");
printf("    -outB Output will be in binary.\n");
printf("    -outD Output will be in decimal.\n");
printf("    -outH Output will be in hexadecimal.\n\n");
printf("  SIZE:\n");
printf("    -8    input is an unsigned 8-bit integer.\n");
printf("    -16   input is an unsigned 16-bit integer.\n");
printf("    -32   input is an unsigned 32-bit integer.\n");
printf("    -64   input is an unsigned 64-bit integer.\n\n");
printf("  NUMBER:\n");
printf("    number to be converted.\n\n");
}

/**
 * Main function
 *
*/

int main(int argc, char* argv[])
{
    unsigned long number, final;
    int num_spaces, i;
    char* input_str = argv[1];
    char* output_str = argv[2];
    char* bits = argv[3];
    char* num = argv[4];
    int size = -(atoi(bits)); /** I made this number of bit positive.*/
    char* renewed = malloc(sizeof(char) * (size + 1));


    /*
    * This if statements simply will throw error if argc is not 5
    */
    if(argc != 5)
    {
        printf("ERROR: incorrect number of arguments\n");
        print_error();
        return 0;
    }

    /**
     * here I simply copied this from formatted decimal code above.
     * Its for proper number of spaces for decimal
    */

    if(size == 8) num_spaces = 3; /* the greatest unsigned number in 8 bits is 255 */

    if(size == 16) num_spaces = 6;  /* the greatestunsigned number in 16 bits is 655,535 */

    if(size == 32) num_spaces = 13; /* the greatest unsigned number in 32 bits is 4,294,967,295 */

    if(size == 64) num_spaces =  26; /* the greatest unsigned number in 64 bits is 9,223,372,036,854,775,807 */

   /**
    * More Errror Checks here
    * We are checking if -inD and argument[4] matches in this loop
    * If not we throw the error.
   */

   for(i = 0; i < strlen(argv[4]); i++)
    {
        /*
        * For Decimal number
        */
        if(input_str[3] == 'D' && !isdigit(num[i]))
        {
        printf("ERROR: argument 4 is not a decimal integer\n");
        print_error();
        return 0;
        }

        /*
        * For Hexa-Decimal number
        */
        else if(input_str[3] == 'H' && !isxdigit(num[i]))
        {
            printf("ERROR: argument 4 is not a hexadecimal integer\n");
            print_error();
            return 0;
        }

        /*
        * For Binary number
        */
        else if(input_str[3] == 'B' && num[i] != '0' && num[i] != '1')
        {
            printf("ERROR: argument 4 is not a binary integer\n");
            print_error();
            return 0;
        }
    }

    number = strtoul(argv[4], NULL, 0);

    /**
     * Here I used Switch case method to read argv[1] and argv[2]
     * Convert and print the appropriate result
    */
   
    if(size == 8 || size == 16 || size == 32 || size == 64)
    {
        switch(input_str[3])
        {
        /**
         * Conversion : Decimal to other Numbers
        */
        case 'D' :

            switch(output_str[4])
            {
                case 'H' :
                printf("%s\n", decimal_to_hex(number, size));
                break;

                case 'B' :
                printf("%s\n", decimal_to_binary(number, size));
                break;

                case 'D' :
                renewed = remove_spaces(decimal_to_binary(strtoul(argv[4], NULL,10), size));
                final = binary_to_decimal(renewed, size);
                printf("%*s\n", num_spaces, format_to_decimal(final, size));
                break;

                default :
                printf("ERROR: argument 2 must be -outB | -outD | -outH\n");
                print_error();
                break;
            }
            break;  
        /**
         * Conversion : Binary to other Numbers
        */
        case 'B' :
            switch(output_str[4])
            {
                case 'D' :
                printf("%*s\n", num_spaces, format_to_decimal(binary_to_decimal(argv[4], size), size));
                break;

                case 'H' :
                printf("%s\n", binary_to_hex(argv[4], size));
                break;

                case 'B' :
                binary_to_decimal(argv[4], size);
                printf("%s\n", decimal_to_binary(binary_to_decimal(argv[4], size), size));
                break;

                default :
                printf("ERROR: argument 2 must be -outB | -outD | -outH\n");
                print_error();
                break;
            }
            break;
        /**
         * Conversion : Hexa-decimal to other Numbers
        */
        case 'H' :
            switch(output_str[4])
            {
                case 'B' :
                printf("%s\n", hex_to_binary(argv[4], size));
                break;

                case 'D' :
                setlocale(LC_ALL, "");
                printf("%*s\n", num_spaces, format_to_decimal(hex_to_decimal(argv[4], size), size));
                break;

                case 'H' :
                hexa_to_hexa(argv[4], size);
                break;

                default :
                printf("ERROR: argument 2 must be -outB | -outD | -outH\n");
                print_error();
                break;
            }
        
        }

        /**
         * This statement is to check argv[1]
         * If its proper command or not
         * For some reason using default method above didn't work
         * so I checked here
        */
        if((input_str[3] == 'H' || input_str[3] == 'D' || input_str[3] == 'B'))
        {
            return 1;
        }

        else{
        printf("ERROR: argument 1 must be -inB | -inD | -inH\n");
        print_error();
        return 0;
        }
    }

    /**
     * This checks number of bits
     * and print errror
    */
    else
   {
    printf("ERROR: argument 3 must be: -8 | -16 | -32 | -64\n");
    print_error();
   }
   return 0;
}

