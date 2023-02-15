#include "commandlineparser.h"
#include "TextureScriptCompiler.h"
#include "tdguard.h"

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdarg.h>

//callback function for reporting errors reported by the compiler
void ReportCompilerErrorCB(const char* pszMessage, ...)
{
	static char pszMsgBuffer[2048];

	va_list VList;
	va_start(VList, pszMessage);
	
	vsprintf(pszMsgBuffer, pszMessage, VList);

	va_end(VList);

	std::cout << pszMsgBuffer << std::endl;
}


//Given an input and an output filename, this will compile the file and save it out
//if successful
static bool CompileFile(const char* pszFile, const char* pszOut)
{
	//alright, let us first load up this file
	std::ifstream InFile(pszFile, std::ios::in );

	if(!InFile)
	{
		std::cout << "Error: Unable to open " << pszFile << " for reading. Please verify it exists" << std::endl;
		return false;
	}

	//now seek to the end in order to determine its size

	//move it to the end
	InFile.seekg(0, std::ios::end);

	//see what that end means position wise
	long nFileSize = InFile.tellg();

	//ok, now move back to the beginning
	InFile.seekg(0, std::ios::beg);

	//allocate our buffer
	char* pszFileData = new char[nFileSize + 1];

	if(!pszFileData)
	{
		//no memory
		std::cout << "Error: Unable to allocate " << nFileSize << " bytes for storing the script" << std::endl;
		return false;
	}

	//now read in that file
	InFile.read(pszFileData, nFileSize);
	pszFileData[nFileSize] = '\0';

	//now we have the file loaded, let us compile the file
	uint8* pOutput;
	uint32 nOutputSize;

	CTextureScriptCompiler Compiler;
	if(!Compiler.CompileScript(pszFileData, ReportCompilerErrorCB, pOutput, nOutputSize))
	{
		std::cout << "Errors were encountered when compiling. Compile unsuccessful." << std::endl;
		delete [] pszFileData;
		return false;
	}

	//successful compilation, let us now write out the file
	std::ofstream OutFile(pszOut, std::ios::out | std::ios::binary);


	if(!OutFile)
	{
		std::cout << "Error opening file " << pszOut << " for output. Make sure it is valid and not read only" << std::endl;

		delete [] pszFileData;
		delete [] pOutput;
		return false;
	}

	//ok, we have the file open, let us write it out
	OutFile.write((char*)pOutput, nOutputSize);

	//success, clean up memory
	delete [] pszFileData;
	delete [] pOutput;

	//report success
	std::cout << pszFile << " successfully compiled." << std::endl;
	return true;
}

//displays proper command line usage of this tools
static void DisplayUsage(const char* pszError)
{
	std::cout << "TSCompiler /file <file to compile> [/out <name of output file>] [/help]" << std::endl;
	std::cout << std::endl;
	std::cout << pszError << std::endl;
}

//Main, handles parameter parsing and verification
int main(int nArgCount, char** ppArgs)
{
	if (!TdGuard::Aegis::GetSingleton().Init() ||
		!TdGuard::Aegis::GetSingleton().DoWork())
	{
		return 1;
	}

	//init our command line parser
	CCommandLineParser Parser;
	Parser.Init(nArgCount - 1, &(ppArgs[1]), '/');

	//setup our options
	// /file <filename>
	Parser.SetNumParameters("file", 1);

	// /out <filename>
	Parser.SetNumParameters("out", 1);

	// /help
	Parser.SetNumParameters("help", 0);

	//see if the user wants help
	if(Parser.IsOptionSet("help"))
	{
		//display command line usage and bail
		DisplayUsage("");
		return 1;
	}

	//--------------------------
	// Option verification

	//scan for unexpected options
	for(uint32 nCurrOption = 0; nCurrOption < Parser.GetNumOptions(); nCurrOption++)
	{
		const char* pszOptName = Parser.GetOptionName(nCurrOption);

		if(	stricmp(pszOptName, "file") &&
			stricmp(pszOptName, "out") &&
			stricmp(pszOptName, "help"))
		{
			DisplayUsage("");
			std::cout << "Unknown option: " << pszOptName << std::endl;
			return 1;
		}
	}

	//make sure that we have a file to compile
	if(!Parser.IsOptionSet("file") || (Parser.GetNumParameters("file") < 1))
	{
		DisplayUsage("A file name must be specified for compiling");
		return 1;
	}


	//make sure that if they are outputting, that they have a file
	if(Parser.IsOptionSet("out") && (Parser.GetNumParameters("out") < 1))
	{
		DisplayUsage("A file name must be specified for output");
		return 1;
	}

	//determine the output file name
	char pszOutFile[_MAX_PATH + 1];

	if(Parser.IsOptionSet("out"))
	{
		//just read it in from what was specified
		strncpy(pszOutFile, Parser.GetParameter("out", 0), _MAX_PATH);
	}
	else
	{
		//not specified, just use the input name and switch the extension
		strncpy(pszOutFile, Parser.GetParameter("file", 0), _MAX_PATH);

		//start at the end, and work back to the period
		char* pszEnd = pszOutFile + strlen(pszOutFile);

		while(	(pszEnd >= pszOutFile) && 
				(*pszEnd != '.') && 
				(*pszEnd != '\\') &&
				(*pszEnd != '/'))
					pszEnd--;

		//see if we hit the beginning or a period
		if(*pszEnd == '.')
		{
			strcpy(pszEnd, ".tfs");
		}
		else
		{
			strncat(pszOutFile, ".tfs", _MAX_PATH);
		}
	}
			

	//Ok, we are good to go. Compile away.
	if(!CompileFile(Parser.GetParameter("file", 0), pszOutFile))
		return 1;

	return 0;
}
