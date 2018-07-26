#ifndef ErrorLogger_h
#define ErrorLogger_h

#include "../JuceLibraryCode/JuceHeader.h"

/*
CloudBurst DAPP
Copyright (C) 2018  CurbShifter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

class ErrorLogger : public FileLogger
{
public:
	ErrorLogger(const File &fileToWriteTo, const String &welcomeMessage, const int64 maxInitialFileSizeBytes = 128 *1024);
	~ErrorLogger();	
	virtual void logMessage(const String &message);
};

extern void ToLog(const String &input);

#endif

