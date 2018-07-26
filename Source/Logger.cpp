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

#include "Logger.h"

static ErrorLogger* logout = NULL;

ErrorLogger::ErrorLogger(const File &fileToWriteTo, const String &welcomeMessage, const int64 maxInitialFileSizeBytes) : 
			FileLogger(fileToWriteTo, welcomeMessage, maxInitialFileSizeBytes)
{
	logout = this;
}

ErrorLogger::~ErrorLogger()
{
	logout = NULL;
}

void ErrorLogger::logMessage(const String &message)
{
	FileLogger::logMessage(message);
}

void ToLog(const String &input)
{
	if(logout){
		Time t = Time::getCurrentTime();
		logout->logMessage(t.toString(true, true, true, true) + " " + input);
	}
}

