#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Existing Useful Functions ("True" means values other than 0, "False" means 0) */ 

atoi() /* int atoi(const char *str) [#include <stdlib.h>]*/
	/* converts the number in string type into integer
	 * returns integer
	 */

isalpha() /* int isalpha(int c) [#include <ctype.h>]*/
	/* returns TRUE if the input character is alphabetic
	 * returns False if the input character is not alphabetic
	 */

fscanf() /*int fscanf(FILE *stream, const char *format, ...) [#include <stdio.h>]*/
	/* formatted input from file
	 * returns EOF when end of file is reached
	 */

fgetc() /* int fgetc(FILE *stream) [#include <stdio.h>]*/
	/* get one character from the input file.
	 * similar to fscanf 
	 * fscanf(in,"%c", &ch) --> ch = fgetc(in)
	 */

feof() /* int feof(FILE *stream) [#include <stdio.h>]*/
	/* returns TRUE if end of file is reached
	 * returns False if end of file is not reached
	 */
/*-------------------------------------------------------------------------------*/
/* Functions and structures that may be helpful for implementing this project */
typedef struct{
	char name[15];
	float initial_balance;
	...
	float total_sum;
	float average_sum;
}Person;
	/* This structure should include the player attributes that you need to print out
	 * for the game statistics. You need to figure these attributes out so that you can
	 * use them for printing. (It will be helpful if you initialize this as an array in 
	 * main.) (Don't store all the data for every round, process them within
	 * each round, and only store the important statistics)
	 *
	 * Think about how you can use this in the game stat below:
	 * -----------------------------------------------------------
	 * (detailed information of each round in the following format)
	 *
	 *  Round 1: 
	 *	Alice: 27-->09  Bob: 62-->08  Carol:21-->03  David:49-->13 
	 *	David contributes $13.00 to the pool. New balance: $32.00 
	 *	Alice takes $5.08, new balance is $45.08 
	 *	Bob takes $2.64, new balance is $38.49 
	 *	Carol takes $1.37, new balance is $51.62 
	 *	David takes $3.91, new balance is $35.91 
	 *
	 * -----------------------------------------------------------
	 * (individual player information at the end of the game)
	 * 
	 *  Alice:  
	 *	initial balance: $40.00 
	 *	ending balance: $20.14 
	 *	lost $19.86 
	 *	average random numbers: 49.97 
	 *	average sum: 8.67 
	 *	number of rounds won: 7 
	 */

typedef struct{
	int round;
	int specific_value;
	int values[4];
}Stat;
	/* This stores the statistics that you will print at the end of the game.
	 * However, some of these stats include float values instead of int. In 
	 * this case, you might want to declare a similar structure, but stores
	 * float data type.
	 *
	 * Think about why we can use this structure for the following example:
	 * game information at the end of the game:
	 * 
	 * largest winning sum: 18 in round 21 (15 18 9 17) 
	 * smallest winning sum: 8 in round 15 (8 5 3 7) 
	 * largest non-winning sum: 17 in round 21 (15 18 9 17) 
	 * average winning sum: 12.33 
	 * largest net win: $15.09 Alice in round 21 ($15.09 $-17.50 $1.11 $1.30) 
	 * largest net loss: $17.50 Bob in round 21 ($15.09 $-17.50 $1.11 $1.30) 
	 * number of rounds with 2-way tied winning sum: 5 
	 * number of rounds with 3-way tied winning sum: 0 
	 *
	 */

int add(int input);
	/* This function sums up the two digits of a specific value.
	 * For example, if input is 57, you should return 12.
	 * This is similar to HW1 question 2
	 */

/* For these 3 functions below, if you want to implement them by sorting the array first, 
 * be sure to make a copy first. Othewise, the sequence of the values may become different*/
int maximum(int array[]);
	/* This returns the maximum value within an array
	 * You can directly assume the array length for this project as 4
	 * Some of the game stat are in int while some are in float, so you might want to declare
	 * a float type of this function as well, with float input array.
	 */

int second_maximum(int array[]);
	/* This returns the second maximum value within an array
	 * Some of the game stat are in int while some are in float, so you might want to declare
	 * a float type of this function as well, with float input array.
	 * This comes in handy for determining the largest non-winning sum in a round and 
	 * a two-way-tie.
	 */

float get_third_float_max(float array[]);
	/* This function returns the third largest value within an array.
	 * This comes into handy for determining a three-way-tie.
	 */

int get_max_index(float array[]);
	/* This function returns the index associated with the maximum value within the array.
	 * This is helpful for determining the player who has the largest net win
	 */

int get_second_max_index(float array[]);
	/* This function returns the index associated with the second maximum value within the array.
	 * This is helpful for determining the player who has the largest net loss
	 */

void copy_values(int a[], int b[]);
    /* Copies whatever is in b to a
     * You can use this whenever the game stat needs to be renewed.
     * In this case, you want to report all the associated values in that round for
     * every player. This is the time this functions may be helpful.
     * Also, some stat are in float, so you might want to make a function with 
     * float type input array.
     */

/*Some hint*/
/* How to get player names and initial_balances from names.txt?
 *
 * names.txt: 
 * 
 * Alice 40.00
 * Bob 35.85
 * Carol 50.25
 * David 45.00
 *
 * Think about using a for-loop (i = 0:3). In each iteration, you parse a line of data.
 * In each line, you first need to keep asking a char until it reaches ' '.
 * You can use a do-while loop, and fgetc to copy the characters one by one
 * into the player[i].name[index] until the character is ' '. Before using 
 * the do-while loop, set index to 0 so that for every player, you will be 
 * copying the name into the first char element for every player at first.
 *
 * When you reach ' ', you should assign player[i].name[index] as '\0' so that
 * later on if you try to print player name, you can use the %s format specifier.
 *
 * After you get the name, use fscanf(input_file_ptr,"%f ", &player[i].initial_balance)
 * to get the initial balance. Note that there is a space after %f. This reason for
 * having it is because at the end of each line, there is a newline character.
 * The space acts as a buffer so that in the next iteration when you use fgetc,
 * you won't scan '\n' as part of the player's name. 
 */
