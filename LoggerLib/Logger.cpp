#include "stdafx.h"
#include "Logger.h"

bool Logger::openStream(){
	_outputStream.open(_fileName, std::ios::out | std::ios::app);
	
	getCurrentDateTime();
	_outputStream << timebuf << " > <<Log started>>" << "\n";
	delete timebuf;
	
	return _outputStream.is_open();
}
void Logger::closeStream() { 
	getCurrentDateTime();
	_outputStream << timebuf << " > <<Log ended>>" << "\n";
	delete timebuf;

	_outputStream.close();
}
void Logger::write(char* record) { _outputStream << " > " << record << "\n"; }
void Logger::write(const char* record) { _outputStream << " > " << record << "\n"; }
void Logger::write(std::string record) { _outputStream << " > " << record << "\n"; }
void Logger::getCurrentDateTime(){
	struct tm newtime;
	__time64_t long_time;
	timebuf = new char[80];

	_time64(&long_time);
	_localtime64_s(&newtime, &long_time);
	strftime(timebuf, 80, "%c", &newtime);
}

Logger::Logger() : _fileName("log.txt") { openStream(); }
Logger::Logger(char* fileName) : _fileName(fileName) { openStream(); }
Logger::~Logger() { closeStream(); }