/*************************************
 * Pratik Basyal
 * CS 241L
 * This header file consists of diffferent functions that can be used as reference for other files.
**************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

/*This is the struct of each node in huffman Tree*/
struct huffTree
{
	int symbol;
	unsigned long frequency;
	struct huffTree* right;
	struct huffTree* left;
};


/*The main two functions which starts the enocding and decoding process  */
void encodeFile(FILE* in, FILE* out);
void decodeFile(FILE* in, FILE* out);

/*******************************************************************************
 * This function compares two huffTrees by their frequency values.
 * If the frequencies are equal, it returns the tree with the smaller symbol value.
 ******************************************************************************/
int compareFreq(const void* a, const void* b);

/*******************************************************************************
 * This function traverses a Huffman tree and generates a binary code for each symbol in the tree
 * Stores them in a lookup table.
 * ******************************************************************************/
void traverseTree(struct huffTree *tree, char *prefix, char **table);

/*******************************************************************************
 *The function takes a prefix string and a single character
 *And combines them to form a new string, which is returned as the result.
 ******************************************************************************/
char *chain(char *prefix, char letter);

/*******************************************************************************
 * This code counts the frequency of each symbol from a file by initializing an array to zero for each possible symbol 
 * Also reading through the file character by character, and incrementing the frequency count for each symbol encountered 
 *The total number of characters read is also counted.
 ******************************************************************************/
unsigned long countFrequency(FILE* in);

/*******************************************************************************
 * This function returns the most leftnode value.
 ******************************************************************************/
int minVal(struct huffTree* root);

/*******************************************************************************
 * This function builds a Huffman tree from the frequency of characters.
 * Generates codes for each symbol in the tree, and stores them in an array called table.
 ******************************************************************************/
void BuildHuffmanTable(char **table);


/*******************************************************************************
 * This function reads the frequency table from the header of the input file, reconstructs the huffman tree
 ******************************************************************************/
void TreeBuilder();


/*******************************************************************************
 * This function creates a new node for a Huffman tree with the given symbol and frequency, and returns it
 ******************************************************************************/
struct huffTree* createNodes(unsigned long *frequency, int i);

/*******************************************************************************
 * This function takes a pointer to an array of huffman trees, and an index as input
 * It returns a pointer to the huffman tree in the array at the given index, and updates the frequency of that tree
 ******************************************************************************/
struct huffTree** getTree(struct huffTree** headRef, int i);

/*******************************************************************************
 * These functions help Print list data on single line, separated with spaces.
 ******************************************************************************/
void printList(struct huffTree* queue);
void printTable(unsigned long *frequency, char** table);
void freeList(struct huffTree* head);

/*******************************************************************************
 * This function writes header that contains frequency and symbol of each character in hufftree.
 ******************************************************************************/
void WriteHeader(FILE *out, unsigned long frequencies[]);

/*******************************************************************************
 * This function takes a binary number in the form of an integer and flips its bits
 * Produces the complement of the original binary number
 ******************************************************************************/
unsigned int flipBinary(int num);

/*******************************************************************************
 * This function takes a binary string and writes it to a file bit by bit 
 * It uses a pointer to a remaining integer and the length of remaining bits to keep track of the remaining bits
 * Once the remaining bits reach 8, the function writes the value to the output file.
 ******************************************************************************/
void writeChar(char *code, unsigned int *rem, int *remLength, FILE *out);

/*******************************************************************************
 * This function reads the header 
 * And recreates the frequency table from the header
 ******************************************************************************/
void readHeader(FILE* in);

/*******************************************************************************
 * This function returns a single bit from the FILE* in
 * an character is stored in static int a single bit is returned
 * A new character is read after returning 8 bits
 ******************************************************************************/
int getBit(FILE *in);

/*******************************************************************************
 * Decode a symbol from the Huffman tree by traversing it using bits passed from the getBit function until a leaf node is reached. 
 * Return the decoded character from the leaf node.
 ******************************************************************************/
int DecodeSymbol(FILE*in, struct huffTree *tree);

/*******************************************************************************
 * This function reads the frequency table from the header of the input file, reconstructs the huffman tree
 * And also decodes the symbols written in the input file by writing the decoded symbols to the output file.
 ******************************************************************************/
void decodeFile(FILE* in, FILE* out);

/*******************************************************************************
 * This function frees huffTree along with its branches below
 ******************************************************************************/
void freeList(struct huffTree* head);

#endif
