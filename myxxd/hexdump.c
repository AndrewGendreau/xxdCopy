/*
NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: hexdump.c
PURPOSE: This will be a program to emulate the hexdump functionality of xxd. This will have functions 
to print the hexdumps. One function for each option that may be specified.
 */

#include "hexdump.h"
#include <stdlib.h>
#include <string.h>

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
char *hexLine(char ASCIIChar)
{
	char *buffer;							//buffer to hold the hex form before we return it
	char *returnString;						//string to be filled with the hex version of ASCIIChar

	buffer = malloc(sizeof(char *));

	returnString = malloc(sizeof(char *));

	sprintf(buffer, "%02x", ASCIIChar);				//send the character in ASCIIChar to the buffer in hex form

	strcat(returnString, buffer);					//concatenate the buffer to the end of return string

	return returnString;
}

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
int hexdumpInputFile(FILE *fileName, int octets)
{
	FILE *file;							//input file
	char currentChar;						//current dump line
	char *hexTranslation;						//hex version of the line
	char *hexForm;							//character pointer to hold the binary line
	int i;								//loop controller
	char ASCIILine[octets];						//ASCII version of the line

	file = fileName;
	hexForm = malloc(octets);

	i = 0;

	while(i < octets)
	{
		if(i % 2 == 0 && i != 0)				//have we printed an even number of characters and i isn't 0?
			strcat(hexForm, " ");

		currentChar = getc(file);

		if(currentChar == EOF)					//check if we've hit the end of the file
		{
			ASCIILine[i] = '\0';
			fileWrite(stdout, hexForm, ASCIILine);
			return 1;
		}

		hexTranslation = hexLine(currentChar);			//if not, convert to hex and build the output
		strcat(hexForm, hexTranslation);			
		ASCIILine[i] = currentChar;
		i++;
	}
	ASCIILine[i] = '\0';
	fileWrite(stdout, hexForm, ASCIILine);
	return 0;	
}

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
int hexdumpBothFiles(FILE *inputFilename, FILE *outputFilename, int octets)
{
	FILE *inputFile;						//input file pointer
	FILE *outputFile;						//output file pointer
	char currentChar;						//current dump line
	char *hexTranslation;						//hex version of the line
	int i;								//loop controller
	char *hexForm;							//character pointer to hold the binary line
	char ASCIILine[octets];						//ASCII version of the line

	inputFile = inputFilename;
	outputFile = outputFilename;
	hexForm = malloc(octets);

	i = 0;

	while(i < octets)
	{

		currentChar = getc(inputFile);
		if(currentChar == EOF)
		{
			ASCIILine[i] = '\0';
			fileWrite(outputFile, hexForm, ASCIILine);
			return 1;
		}

		hexTranslation = hexLine(currentChar);
		strcat(hexForm, hexTranslation);
		ASCIILine[i] = currentChar;
		i++;

		if(i % 2 == 0 && i != 0)				//have we printed an even number of characters and i is not 0?
			strcat(hexForm, " ");
	}
	ASCIILine[i] = '\0';
	fileWrite(outputFile, hexForm, ASCIILine);
	return 0;	
}
