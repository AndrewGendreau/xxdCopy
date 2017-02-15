/*NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: hexdump.h
PURPOSE: This will be a program to emulate the hexdump functionality of xxd. This will have functions 
to print the hexdumps. One function for each option that may be specified.
 */

#include <stdio.h>

#ifndef _HEX_H_
#define _HEX_H_
#include "hexdump.h"
#endif

#ifndef _FILE_H_
#define _FILE_H_
#include "fileReader.h"
#endif

extern int lineNumber;							//global variable for the line number.
extern int lineLimitSet;						//global variable to test if an octet line limit is set, 1 if so
extern int octetsLeft;							//global variable to keep track of how many octets are left
									//only used in the case when we have set a max octet limit
extern int numOfOctetsPerLine;						//number of octets per line given by -c option, defaults to 16

/*
Name: hexLine
Purpose: This function will take one character as input and return its hex form.
	This function does not handle a whoel line due to formatting reasons.
Parameters:
	--ASCIIChar: character to change
Returns:
	pointer to the new hex character
Author: Andrew Gendreau
 */
char *hexLine(char);

/*
Name: hexdumpInputFile
Purpose: This function will handle the case where we are given an input file. In this case,
We must read from that file and print to stdout. Here, we will read in one character at a time,
convert it to hex and do the same as we would with the binary form. In this case, there is an extra check to seperate
between hex outputs as xxd does. This checks if our current i is even, if so, it prints a space.
Parameters:
	 --fileName: input file name
	 --octets: number of octets
Returns: 
	void
Author: Andrew Gendreau
 */
int hexdumpInputFile(FILE *, int);

/*
Name: hexdumpBothFiles
Purpose: This function will handle the case where we are given output and input files. In this case,
We must read from the input file and print to the output file. This is almost identical to the function above,
the only difference is the file we write to.
Parameters:
	 --inputFile: input file pointer
	 --outputFile: output file pointer
	 --octets: number of octets
Returns: 
	void
Author: Andrew Gendreau
 */
int hexdumpBothFiles(FILE *, FILE *, int);
