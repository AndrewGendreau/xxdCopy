/*
NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: fileReader.c
PURPOSE: This will be a module to handle file writing and opening for the myxxd program
 */

#include "fileReader.h"

/*
Name: inputFileOpen
Purpose: This function will open the given file for reading and return the corresponding file pointer.
Parameters:
	 --target: target file
Returns: 
	FILE *
Author: Andrew Gendreau
 */
FILE *inputFileOpen(char *target)
{
	FILE *file;						//file to open

	file = fopen(target, "r");

	return file;
}

/*
Name: outputFileOpen
Purpose: This function will open the given file for writing and return the corresponding file pointer.
Parameters:
	 --target: target file
Returns: 
	FILE *
Author: Andrew Gendreau
 */
FILE *outputFileOpen(char *target)
{
	FILE *file;						//file to open

	file = fopen(target, "w");

	return file;
}

/*
Name: ASCIIform
Purpose: This function will, given a char pointer will form the ASCII part to be attached to the output.
	meant really to scan and replace \n and \t. It is going to walk through the given string one character
	at a time and if it encounters \n or \t it will replace them with '.' just as xxd does.
Parameters:
	 --char *line: line to scan
Returns: 
	char pointer to the new converted line
Author: Andrew Gendreau
 */
char *ASCIIform(char *line)
{
	char currentChar;						//pointer to the current line
	char *convertedLine;						//line converted to ASCII form
	int stringLength;						//string length
	int i;								//loop controller

	stringLength = strlen(line);					//get the length of the line to process

	convertedLine = malloc(stringLength);				//malloc space to hold it

	for(i = 0; i < stringLength; i++)
	{
		currentChar = line[i];

		if(currentChar == '\n' || currentChar == '\t')
		{
			convertedLine[i] = '.';
		}
		else
		{
			convertedLine[i] = currentChar;
		}
	}
	return convertedLine;
}
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
void fileWrite(FILE *fileTarget, char *inputLine, char *ASCIILine)
{
	char *convertedASCII;						//ASCII form of the given line

	convertedASCII = ASCIIform(ASCIILine);

	fprintf(fileTarget, "%07X: %s %s\n", lineNumber, inputLine, convertedASCII);

	free(convertedASCII);

	lineNumber += numOfOctetsPerLine;				//update the line number with the number of octets we wrote
}
