#ifndef INIFILE_H_
#define INIFILE_H_

#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

class IniFile{
	public:
		int Create(char szDir[]);
		void WriteString(char szCat[], char szName[], char szValue[]);
		char* ReadString(char szCat[], char szName[]);
	private:

	protected:

};

#endif