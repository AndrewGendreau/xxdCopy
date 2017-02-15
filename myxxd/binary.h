/*
AUTHOR: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: myxxd.c
PURPOSE: This will be a program to enact the binary operation mode of myxxd. 
Note: xxd's default line size is 6 in binary mode
*/

#include <stdio.h>

#ifndef _FILE_H_
#define _FILE_H_
#include "fileReader.h"
#endif

extern int lineNumber;							//global variable for the line number.
extern int lineLimitSet;						//global variable to test if an octet line limit is set, 1 if so
extern int octetsLeft;							//global variable to keep track of how many octets are left
									//only used in the case when we have set a max octet limit
extern int numOfOctetsPerLine;						//number of octets per line given by -c option, defaults to 6 here

/*
Name: binaryOctet
Purpose: This function will, given a character to convert, change it into its binary form
and return a pointer to the new representation.
Parameters:
	 --char charToConvert: Character to change to a binary represenation
Returns: 
	pointer to the new form
Author: Andrew Gendreau
 */
char *binaryOctet(char);

/*
Name: binaryDumpInputFile
Purpose: This function will, given a file pointer to the input file, read from the file pointer
	and write the next line in its binary form. It will return 0 if we haven't reached the end of the file
	and 1 if we have. It will concatinate the binary octet to the end of the line and also create the ASCII
	form to be appended to the end.
Parameters:
	--FILE *fileName: the file to read from
	--int octets: The number of octets on this line
Returns: 
	0 if file has not ended
	1 if it has
Author: Andrew Gendreau
 */
int binaryDumpInputFile(FILE *, int);

/*
Name: binaryDumpBothFiles
Purpose: This function will, given a file pointer to the input file, 
	and one to the output file, read from the file pointer
	and write the next line in its binary form to the output file.
	 It will return 0 if we haven't reached the end of the file
	and 1 if we have. It will concatinate the binary octet to the end of the line
	and also create the ASCII form to be appended to the end.
Parameters:
	--FILE *inputFileName: the file to read from
	--FILE *outputFileName: the file to write to
	--int octets: The number of octets on this line
Returns: 
	0 if file has not ended
	1 if it has
Author: Andrew Gendreau
 */
int binaryDumpBothFiles(FILE *, FILE*, int);
