#include "stdafx.h"
#include "Logger.h"

void Logger::GetCurrentDateTime(){
	struct tm newtime;
	__time64_t long_time;
	timebuf = new char[80];

	_time64(&long_time);
	_localtime64_s(&newtime, &long_time);
	strftime(timebuf, 80, "%c", &newtime);
}

bool Logger::OpenStream(){
	outputStream.open(fileName, std::ios::out | std::ios::app);
	
	GetCurrentDateTime();
	outputStream << timebuf << " > <<Log started>>" << "\n";
	delete timebuf;
	
	return outputStream.is_open();
}
void Logger::CloseStream() { 
	GetCurrentDateTime();
	outputStream << timebuf << " > <<Log ended>>" << "\n";
	delete timebuf;

	outputStream.close();
}

void Logger::Write(char* _record) { outputStream << " > " << _record << "\n"; }
void Logger::Write(const char* _record) { outputStream << " > " << _record << "\n"; }
void Logger::Write(std::string _record) { outputStream << " > " << _record << "\n"; }

Logger::Logger() : fileName("log.txt") { OpenStream(); }
Logger::Logger(char* _fileName) : fileName(_fileName) { OpenStream(); }
Logger::~Logger() { CloseStream(); }