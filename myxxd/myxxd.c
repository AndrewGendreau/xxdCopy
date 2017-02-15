/*
NAME: Andrew Gendreau
DATE: April 20th 2016
VERSION: 1.0
FILENAME: myxxd.c
PURPOSE: This will be a program to emulate the function of xxd with 3 options specified.
*/

#include <stdio.h>
#include <stdlib.h>

//include guards
#ifndef _HEX_H_
#define _HEX_H_
#include "hexdump.h"
#endif

#ifndef _FILE_H_
#define _FILE_H_
#include "fileReader.h"
#endif

#ifndef _BINARY_H_
#define _BINARY_H_
#include "binary.h"
#endif

int lineNumber;								//global variable for the line number
int lineLimitSet = 0;							//global variable to test if an octet limit is set, 1 if so
int octetsLeft = 0;							//global variable to keep track of how many octets are left
									//only not 0 in the case when we have set an octet limit.
int numOfOctetsPerLine = 16;						//number of octets per line, set by -c or defaults to 16 for hex
									//and 6 for binary
/*Name: main
Purpose: This function will process the input from the command line and call the needed functions based on the input.
	The form of the command will be:
		./myxxd [options] [infile [outfile]]
	if infile is not entered in its place we read from stdin (requires a second loop).
	if outfile is not entered , then we send the output to stdout.
	This main method will first parse the command line input and set the approprate flags.
	Once it has done this, it will, according to the set flags, make calls to the correct functions in order to
	perform the dump.
Parameters:
	int argc --arguement count
	char *argv[] --array of pointers that holds the command line input.
Returns:
	0
Author: Andrew Gendreau
*/
int main(int argc, char* argv[])
{
	int binaryMode = 0;						//binary mode or not? 0 if no, 1 if yes
	int inputFileGiven = 0;						//were we given an input file? 0 if no, 1 if yes
	int outputFileGiven = 0;					//were we given an output file? 0 if no, 1 if yes
	int EOFMarker;							//marker to signify we've hit the end of the file, 0 = no, 1 = yes
	FILE *inputFile;						//input file pointer
	FILE *outputFile;						//output file pointer

	lineNumber = 0;							//set the line number to 0

	while(argc > 1 && argv[1][0] == '-')				//parse the options
	{
			if(argv[1][1] == 'c')				//check if we have a column option
			{
				numOfOctetsPerLine = atoi(argv[2]);
				
				argc--;					//decrement argc so we know we've just worked one arguement
				argv++;					//move the pointer in argv to the next arguement
			}
			else if(argv[1][1] == 'l')			//check if we have a length option
			{
				octetsLeft = atoi(argv[2]);

				lineLimitSet = 1;			//set the length flag

				
				argc--;					//decrement argc so we know we've just worked one arguement
				argv++;					//move the pointer in argv to the next arguement
			}
			else if(argv[1][1] == 'b')			//check if we have a binary mode option set
			{
				binaryMode = 1;				//turn on binary mode
				if(numOfOctetsPerLine == 16)
					numOfOctetsPerLine = 6;		//set binary mode line length default if it was not changed
			}
			else
			{
				printf("Invalid input! See the readme for the supported options\n");
				return 0;
			}

		argc--;							//decrement argc so we know we've just worked one arguement
		argv++;							//move the pointer in argv to the next arguement
	}

									//we have no more options at this point

	if(argc > 1 && argv[1][0] != ' ')				//were we given an input file?
	{
		inputFileGiven = 1;					//set the input flag if so
		inputFile = inputFileOpen(argv[1]);

		if(inputFile == NULL)
		{
			printf("Non-Existant input file! Terminating..\n");
			return 0;
		}

		argc--;							//decrement argc so we know we've just worked one arguement
		argv++;							//move the pointer in argv to the next arguement
	}
	else								//otherwise we have no input file
	{
		//read from stdin
		argc--;							//decrement argc so we know we've just worked one arguement
		argv++;							//move the pointer in argv to the next arguement
	}

	if(argc > 1 && argv[1][0] != ' ')				//check if we're given an output file
	{
		outputFileGiven = 1;					//set the mode for given output file
		outputFile = outputFileOpen(argv[1]);

		argc--;							//decrement argc so we know we've just worked one arguement
		argv++;							//move the pointer in argv to the next arguement
	}
	else
	{
		argc--;							//decrement argc so we know we've just worked one arguement
		argv++;							//move the pointer in argv to the next arguement
	}

									//at this point, check for which modes are set to active
									//and call the corresponding functions
	
	if(inputFileGiven == 1 && outputFileGiven == 0)			//if we were given an input file but no output file		
	{
		if(binaryMode == 1)					//if binaryMode is set
		{
			if(lineLimitSet == 1)				//if a total limit was set
			{
				while(octetsLeft > 0)			//perform the dump while we are not at our limit
				{
					binaryDumpInputFile(inputFile, numOfOctetsPerLine);
					octetsLeft -= numOfOctetsPerLine;
				}
			}
			else						//if we're running to the end of the file
			{
				do
				{
					EOFMarker = binaryDumpInputFile(inputFile, numOfOctetsPerLine);
				} while(EOFMarker == 0);
			}
		}
		else							//if we're not in binary mode, we're in hex mode
		{
			if(lineLimitSet == 1)				//if we have a total limit
			{
				while(octetsLeft > 0)			//perform the dump while we haven't hit it
				{
					hexdumpInputFile(inputFile, numOfOctetsPerLine);
					octetsLeft -= numOfOctetsPerLine;
				}
			}
			else						//otherwise, we're running to the end of the file
			{
				do
				{
					EOFMarker = hexdumpInputFile(inputFile, numOfOctetsPerLine);
				} while(EOFMarker == 0);
			}
		}
	}
	else
	{
		if(binaryMode == 1)					//same as above, check the binary mode flag
		{
			if(lineLimitSet == 1)				//if we have a total limit
			{
				while(octetsLeft > 0)			//while we haven't hit the limit
				{
					binaryDumpBothFiles(inputFile, outputFile, numOfOctetsPerLine);
					octetsLeft -= numOfOctetsPerLine;
				}
			}
			else							//otherwise, we're running to the end
			{
				do
				{
					EOFMarker = binaryDumpBothFiles(inputFile, outputFile, numOfOctetsPerLine);
				} while(EOFMarker == 0);
			}
		}
		else								//if we are in hex mode
		{
			if(lineLimitSet == 1)					//if we have a total limit
			{
				while(octetsLeft > 0)				//do the dump while we're in that limit
				{
					hexdumpBothFiles(inputFile, outputFile, numOfOctetsPerLine);
					octetsLeft -= numOfOctetsPerLine;
				}
			}
			else							//otherwise, run to the end
			{
				do
				{
					EOFMarker = hexdumpBothFiles(inputFile, outputFile, numOfOctetsPerLine);
				} while(EOFMarker == 0);
			}
		}
	}
	return 0;
}
