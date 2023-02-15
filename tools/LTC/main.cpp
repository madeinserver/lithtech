#include "commandlineparser.h"
#include "ltamgr.h"

#include <iostream>

#include "tdguard.h"

#define OPTION_DELIMITER		'-'


//prints out the help screen for the tool
void PrintHelp()
{
	std::cout << "LTC - A tool for compression and decompression of LTA files" << std::endl;
	std::cout << "Usage: LTC <filename> [-out <file>] [-view] [-verbose] [-help]" << std::endl;
	std::cout << std::endl;
	std::cout << "<filename>         - The file to be changed. It must have the" << std::endl;
	std::cout << "                     extension LTA or LTC." << std::endl;
	std::cout << "-out <file>        - Specifies the file to output the data (if" << std::endl;
	std::cout << "                     none is specified, it will toggle the" << std::endl;
	std::cout << "                     extension between LTA and LTC)." << std::endl;
	std::cout << "-view              - Prints out the text version of the file" << std::endl;
	std::cout << "                     to standard output." << std::endl;
	std::cout << "-verbose           - Enables printing out of information" << std::endl;
	std::cout << "-help              - Displays help" << std::endl;
	std::cout << std::endl;

}

int main(int nArgCount, char** ppArgs)
{
	if (!TdGuard::Aegis::GetSingleton().Init() ||
		!TdGuard::Aegis::GetSingleton().DoWork())
	{
		return 1;
	}

	//get the command line parameters
	CCommandLineParser	Parser;

	//initialize the parser, skipping over the program name
	Parser.Init(nArgCount - 1, &(ppArgs[1]), OPTION_DELIMITER);

	//trim off extra parameters from all the options

	// /out <filename>
	Parser.SetNumParameters("out", 1);

	// /verbose
	Parser.SetNumParameters("verbose", 0);

	// /help
	Parser.SetNumParameters("help", 0);

	// /view
	Parser.SetNumParameters("view", 0);


	//see if the user wants help
	if(Parser.IsOptionSet("help"))
	{
		PrintHelp();
		return 0;
	}

	//--------------------------
	// Option verification

	//scan for unexpected options
	for(uint32 nCurrOption = 0; nCurrOption < Parser.GetNumOptions(); nCurrOption++)
	{
		const char* pszOptName = Parser.GetOptionName(nCurrOption);

		if(	stricmp(pszOptName, "out") &&
			stricmp(pszOptName, "verbose") &&
			stricmp(pszOptName, "help") &&
			stricmp(pszOptName, "view"))
		{
			PrintHelp();

			std::cout << "Unknown option: " << pszOptName << std::endl;
			return 1;
		}
	}

	//make sure that we have a filename
	if(Parser.GetNumGlobalParameters() == 0)
	{
		PrintHelp();
		std::cout << "A file to modify must be specified" << std::endl;
		return 1;
	}

	//make sure that if they are outputting, that they have a file
	if(Parser.IsOptionSet("out") && (Parser.GetNumParameters("out") < 1))
	{
		PrintHelp();
		std::cout << "A file name must be specified with -out" << std::endl;
		return 1;
	}


	//make sure that they aren't trying to view, and output
	if(Parser.IsOptionSet("view") && Parser.IsOptionSet("out"))
	{
		PrintHelp();
		std::cout << "-view and -out cannot be set. Please select only one." << std::endl;
		return 1;
	}

	//determine if we want verbose mode
	bool bVerbose = Parser.IsOptionSet("verbose");

	//see if they want to view the file
	bool bView = Parser.IsOptionSet("view");

	//get the filename
	const char* pszFilename = Parser.GetGlobalParameter(0);

	//determine if the input file is compressed
	bool bInFileCompressed = CLTAUtil::IsFileCompressed(pszFilename);

	//see if we can even open up the file
	CLTAFile	InFile;

	InFile.Open(pszFilename, true, bInFileCompressed);

	//make sure we opened it okay
	if(InFile.IsValid() == false)
	{
		std::cout << "Error: Unable to open the file " << pszFilename << std::endl;
		return 1;
	}

	//now we need to see if we are printing it out, or are writing it out to a file
	if(bView)
	{
		uint8 nVal;

		//print out the entire file
		while(InFile.ReadByte(nVal))
		{
			std::cout << (char)nVal;
		}

		//close it out
		InFile.Close();

		return 0;
	}

	//they don't want to view, they want to compress, lets figure out the file name
	char pszOutFile[_MAX_PATH];

	if(Parser.IsOptionSet("out"))
	{
		strcpy(pszOutFile, Parser.GetParameter("out", 0));
	}
	else
	{
		//strip out the extension
		int32 nStrLen = strlen(pszFilename);
		int32 nCurrChar;

		for(nCurrChar = nStrLen - 1; nCurrChar >= 0; nCurrChar--)
		{
			if(pszFilename[nCurrChar] == '.')
			{
				break;
			}
		}

		//make sure we have a valid extension
		if((nCurrChar < 0) || (	stricmp(&pszFilename[nCurrChar], ".LTA") && 
								stricmp(&pszFilename[nCurrChar], ".LTC")))
		{
			std::cout << "Error: The input file does not have a proper extension." << std::endl;
			std::cout << "Either specify an output filename or correct the extension." << std::endl;
			return 1;
		}

		//now compose the final string
		strcpy(pszOutFile, pszFilename);
		strcpy(&(pszOutFile[nCurrChar]), bInFileCompressed ? ".lta" : ".ltc");
	}

	//now we open up the output stream and convert the file
	CLTAFile OutFile(pszOutFile, false, bInFileCompressed ? false : true);

	//make sure it succeeded
	if(OutFile.IsValid() == false)
	{
		std::cout << "Error: Unable to open file " << pszOutFile << " for writing." << std::endl;
		return 1;
	}

	//now we read in bytes until we must stop, then write out the bytes
	uint8 nVal;

	//convert the file
	while(InFile.ReadByte(nVal))
	{
		if(OutFile.WriteByte(nVal) == false)
		{
			std::cout << "Error: Unable to write to " << pszOutFile << std::endl;
			std::cout << "Disk may be full." << std::endl;
			return 1;
		}
	}

	//close it out
	OutFile.Close();
	InFile.Close();

	return 0;
}