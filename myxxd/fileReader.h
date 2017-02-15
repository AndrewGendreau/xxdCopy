/*
NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: fileReader.c
PURPOSE: This will be a module to handle file opening and writing for the myxxd program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int lineNumber;								//global variable for the line number.
extern int numOfOctetsPerLine;							//global number of octets per line

/*
Name: inputFileOpen
Purpose: This function will open the given file for reading and return the corresponding file pointer.
Parameters:
	 --target: target file
Returns: 
	FILE *
Author: Andrew Gendreau
 */
FILE *inputFileOpen(char *target);

/*
Name: outputFileOpen
Purpose: This function will open the given file for writing and return the corresponding file pointer.
Parameters:
	 --target: target file
Returns: 
	FILE *
Author: Andrew Gendreau
 */
FILE *outputFileOpen(char *target);

/*
Name: fileWrite
Purpose: This function will, given a file pointer, a line, and the ASCII version of that line,
	 write that line out to the given file. It will also handle updating and prepending the line number
	and changing the ASCII version.
Parameters:
	--FILE *fileTarget: file to write to
	--char *inputLine: line to write
	--ASCII version of the line to write
Returns: 
	void
Author: Andrew Gendreau
 */
void fileWrite(FILE *, char *, char *);
