/*
NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: myxxd.c
PURPOSE: This will be a program to enact the binary operation mode of myxxd. 
	The functions here will each convert one character at a time.
 */

#include "binary.h"
#include <string.h>
#include <stdlib.h>

#ifndef _HEX_H_
#define _HEX_H_
#include "hexdump.h"
#endif


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
char *binaryOctet(char charToConvert)
{
	int i;							//index for the inital for loop
	int j;							//index for a second loop to move the binary digits to the correct places
	int k;							//index for the second loop, meant to help place the digits correctly
	char *binaryReturn;					//return from the function, the given character in binary, 8+1 for the null
	int binaryTemp[9];					//tempory holding space for the binary values
	int ascii;						//ascii form
	binaryReturn = malloc(1);				//malloc 1 byte for the character's binary form
	i = 0;

	ascii = (int)charToConvert;

	while(ascii >= 1)					//convert to binary
	{
		binaryTemp[i] = ascii % 2;
		ascii = ascii / 2;
		i++;
	}

	while(i<8)						//pad with 0s in the event we need to
	{
		binaryTemp[i] = 0;
		i++;
	}		

	k = 0;

	for(j = i-1; j >= 0; j--)				//Loop to move through the binary array backards and place it in the right
								//place in the return string
	{
		binaryReturn[k] = binaryTemp[j] + '0';
		k++;
	}
	return binaryReturn;
}

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
int binaryDumpInputFile(FILE *fileName, int octets)
{
	FILE *file;							//input file pointer
	char currentChar;						//current character we're looking at
	char *binaryForm;						//character pointer to hold the binary line
	int i;								//loop controller
	char *binary;							//binary version of currentChar
	char ASCIILine[octets];						//ASCII version of the line, set to be octets big because that's
	//how many characters we'll have

	file = fileName;						//set the file variable to the given file pointer
	binaryForm = malloc(octets);					//reserve octets bytes of memory to hold the binary form

	i = 0;

	while(i < octets)						//while we're forming this line
	{
		currentChar = getc(file);				//get the next character to convert

		if(currentChar == EOF)					//if it's the end of the file, write this line and return 1
		{
			ASCIILine[i] = '\0';
			fileWrite(stdout, binaryForm, ASCIILine);
			return 1;
		}

		binary = binaryOctet(currentChar);			//otherwise, convert this character 
		//and attatch it to the binary form
		strcat(binaryForm, binary);
		strcat(binaryForm, " ");

		ASCIILine[i] = currentChar;				//build the ASCII form to pass to fileWrite
		i++;
	}

	ASCIILine[i] = '\0';						//if we have not hit the end of the file
	fileWrite(stdout, binaryForm, ASCIILine);			//write the current line
	return 0;
}

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
int binaryDumpBothFiles(FILE *inputFileName, FILE *outputFileName, int octets)
{
	FILE *inputFile;						//input file
	FILE *outputFile;						//input file
	char currentChar;						//current char to convert
	char *binaryForm;						//character pointer to hold the binary line
	int i;								//loop controller
	char *binary;							//binary octet
	char ASCIILine[octets];						//ASCII version of the line

	inputFile = inputFileName;
	outputFile = outputFileName;
	binaryForm = malloc(octets);					//number of bits per line

	i = 0;

	while(i < octets)						//while we have octets left to create
	{
		currentChar = getc(inputFile);

		if(currentChar == EOF)					//if we read EOF, end the ASCII line and print
		{
			ASCIILine[i] = '\0';
			fileWrite(outputFile, binaryForm, ASCIILine);
			return 1;
		}

		binary = binaryOctet(currentChar);			//otherwise, create the line

		strcat(binaryForm, binary);
		strcat(binaryForm, " ");

		ASCIILine[i] = currentChar;
		i++;
	}
	ASCIILine[i] = '\0';
	fileWrite(outputFile, binaryForm, ASCIILine);
	return 0;
}
