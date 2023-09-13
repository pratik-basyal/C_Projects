#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lcg.h"


int line_num = 1;
/**
 * checks if the given input of line is in valid format or not
*/
int is_valid_input(char *line)
{
    int i;
    for(i = 0; i < strlen(line); i++)
    {
        if(line[i] < 32 || line[i] > 126){
            return 0;
        }
    }
    return 1;
}

/***
 * function to encrypt character
*/
void encrypted(char *b, unsigned long m, unsigned long c)
{
    char byte;
    unsigned long encrypted_byte, random_value;

    struct LinearCongruentialGenerator lcg;

    lcg = makeLCG(m, c);

    while(*b != '\0')
    {
        if(lcg.a == 0 && lcg.m == 0 && lcg.x == 0 && lcg.c == 0)
    {
        printf("Error");
        break;
    }

        byte = *b;
        if(byte == '\n')
        {
            continue;
        }

       random_value = getNextRandomValue(&lcg); /*Generates random value*/

       encrypted_byte = byte ^ (random_value % 128); /*store encrypted ASCII value of character*/

       if(encrypted_byte < 32)
       {
        putchar('*');
        putchar('?'+encrypted_byte);
       }

       else if(encrypted_byte == 127)
       {
        putchar('*');
        putchar('$');
       }

       else if(encrypted_byte == '*')
       {
        putchar('*');
        putchar('*');
       }

       else
       {
        putchar(encrypted_byte);
       }

       b++;
    }
    printf("\n");
}
/****
 * Function to decrypt the character
*/
void decrypted(char *data, unsigned long m, unsigned long b)
{
    char c;
    unsigned long decrypted_byte, random_value;

    struct LinearCongruentialGenerator lcg = makeLCG(m, b);


    while(*data != '\0')
    {

    random_value = getNextRandomValue(&lcg);

    decrypted_byte = *data ^ (random_value % 128);

    if(*data == '*')
    {
        data++;
        c = *data;
        if(c == '$')
        {
            c = 127;
            decrypted_byte = (c)^(random_value%128);
            if(decrypted_byte < 32 || decrypted_byte > 126)
            {
                printf("Error");
                break;
            }
            putchar(decrypted_byte);
            
        }
        else if(c=='*')
        {
            decrypted_byte = (c)^(random_value%128);
            if(decrypted_byte < 32 || decrypted_byte > 126)
            {
                printf("Error");
                break;
            }
            putchar(decrypted_byte);
        }

        else
        {
        decrypted_byte = (c - '?')^(random_value%128);
        if(decrypted_byte < 32 || decrypted_byte > 126)
            {
                printf("Error");
                break;
            }
        putchar(decrypted_byte);
        }
    }


    else
    {
        if(decrypted_byte < 32 || decrypted_byte > 126)
            {
                printf("Error");
                break;
            }
        putchar(decrypted_byte);
    }

    data++;
    }
    printf("\n");
}

/**
 * function that returns value of m
*/

unsigned long m_value(char *str)
{
    unsigned long result;
    int i;
    char *store = malloc(sizeof(str));

    for(i = 0; i < strlen(str); i++)
    {
        store[i] = str[i+1];
    }

    result = strtoul(store, NULL, 10);


    return result;
}

unsigned long c_value(char *str)
{
    unsigned long result;
    
    result = strtoul(str, NULL, 10);

    return result;
}

/**
 * Function that checks if the given string is in the correct format
*/

int is_correct_format(char *str)
{
    int i, num_commas = 0;

    for(i = 0; i < strlen(str); i++)
    {
        if(str[i] ==',')
        {
            num_commas++;
        }
    }

    if(num_commas >= 2)
    {
        return 1;
    }
    return 0;
}

/** REMINDER - I have to deal with any non printable ASCII characters here*/
int main(void) 
{
    char input[1000];
    char *m_str;
    char *c_str;
    char *data;

    while(fgets(input, sizeof(input), stdin))
    {
        if(is_correct_format(input) == 0)
        {
            printf("%5d: Error\n", line_num);
            line_num++;
            continue;
        }

        m_str = strtok(input, ",");
        c_str = strtok(NULL, ",");
        data = strtok(NULL, "\n");

        if(is_valid_input(data))
        {
            if(strlen(m_str) <= 1 || strlen(c_str) < 1 || m_value(m_str) == 0 || c_value(c_str) == 0)
            {
                printf("%5d: Error\n", line_num);
                line_num++;
                continue;
            }

            if(m_str[0] == 'e') 
            {
                printf("%5d: ", line_num);
                encrypted(data, m_value(m_str), c_value(c_str));
                line_num++;
            }
            if(m_str[0] == 'd')
            {
                printf("%5d: ", line_num);
                decrypted(data, m_value(m_str), c_value(c_str));
                line_num++;
            }

            if(m_str[0] != 'e' && m_str[0] != 'd')
            {
                printf("%5d: Error\n", line_num);
                line_num++;
            }

        }

        else{
            printf("%5d: Error\n", line_num);
            line_num++;
        }
    }
    return 0;
}