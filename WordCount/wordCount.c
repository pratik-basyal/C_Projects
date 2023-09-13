/**                                                                                                                                                                                                         
 * Pratik Basyal                                                                                                                                                                                     
 * CS241L 2dk                                                                                                                                                                                              
 * LAB02                                                                                                                                                                                                   
**/

/******
 * DESCRIPTION:
 * This C program analyzes text input, counting lines, words, and characters. 
 * It processes input line by line, keeping track of these counts for each line 
 * and printing the results. The program distinguishes between words and 
 * non-words (spaces and tabs) and identifies the line with the most words and 
 * characters. It also prints the line number alongside word and character counts 
 * for each line. Finally, it displays the total number of lines, words, and 
 * characters in the entire input.
*/

#include <stdio.h>

#define IN 1  /* inside a word*/
#define OUT 0 /* outside a word */

/* count lines, words, and charactrs in input */

int main()
{
        int i = 1;
	int c, nl, nw, nc, state;
        int line_char, line_word;
	int max_char_line = 0;
	int max_words_line = 0;
	int store_word = 0;
	int store_char = 0;
	
	state = OUT;
	nl = nw = nc = 0;
	line_char = line_word = 0;

        while ((c = getchar()) != EOF)
        {
                if(c == '\n')
		{
                    if(i < 10){
                    printf("( %d) [%d, %d]\n",i, line_word, line_char);
                    ++i;
                    ++nl;
                    line_char = -1;
		    nc = nc -1;
                    line_word = 0;
                    }

                    else
                    {
                    printf("(%d) [%d, %d]\n",i, line_word, line_char);
                    ++i;
                    ++nl;
                    line_char = 0;
                    line_word = 0;
                    }
                }
                
		if(i < 10) printf("( %d) ",i);

                else
                {
                        printf("(%d) ", i);
                }
        
                do
                {
                        if(c != '\n') putchar(c);
                        ++line_char;
                        ++nc;

                        if(c == ' ' || c == '\t')state = OUT;
                        else if(state == OUT)
			{
                        state = IN;
                        line_word += 1;
                        ++nw;
                       }
                }
                while((c = getchar()) != '\n');
                
                if(c == ' ' || c == '\n' || c == '\t') state =  OUT;
                else if(state == OUT)
		{
                        state = IN;
                        line_word += 1;
                        ++nw;
                }

		if(store_word < line_word)
		{
		  store_word = line_word;
		  max_words_line = i;
		}

                if(store_char < line_char)
		{
			store_char = line_char;
			max_char_line = i;
		}

                printf("[%d, %d]", line_word, line_char);

                if(c == '\n')
		{
                        ++nl;
                        ++i;
                        line_char = 0;
                        line_word = 0;
                }

                printf("\n");                
        }

	printf("\n");
        printf("%d lines, %d words, %d characters\n", nl, nw, nc);
	printf("Line %d has the most words with %d\n", max_words_line, store_word);
	printf("Line %d has the most characters with %d\n", max_char_line, store_char);
        return 0;
}
