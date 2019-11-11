//
//  configreader.h
//  Logger
//
//  Created by Albert Bode on 9/15/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef configreader_h
#define configreader_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "filereader.h"

// Default config values
#ifdef __APPLE__
#define DEFAULT_RESOURCE_PATH "curdir/resources/"
#
#else
#define DEFAULT_RESOURCE_PATH "installdir\\resources\\"
#endif

#define DEFAULT_LOG_FILE "logFile.txt"
#define DEFAULT_DEBUG_LEVEL LOG_MSG_WARNING

struct configReader : public fileReader {
	std::string filePath;	// Config file to load from
	std::string userDirectory;
	std::string resourceDirectory;
	std::string logFilename;
	int debugLevel;
	
	void load_config(){
		// Open file stream
		std::fstream fh;
		fh.open(this->filePath, 'r');
		if(!fh.is_open()){
			// Logger will not be initalized yet, so send debug msg to cout
			std::cout << "Unable to open user config" << std::endl;
		}
		
		// Read file line by line
		std::string linebuf;
		while(fh.peek() != -1) {
			safeGetline(fh, linebuf);
			
			// Skip empty lines
			if (linebuf.empty()){
				continue;
			}
			
			// Skip comment lines
			if(linebuf[0] == '#' || linebuf[0] == ';'){
				continue;
			}
			
			// if delim is not found it's not a problem
			size_t delim = linebuf.find('=');
			std::string field = linebuf.substr(0,delim);
			std::string value = linebuf.substr(delim+1);

			// Trim whitespace from both values
			trim(field);
			trim(value);
			
			// Value lines
			if (std::strcmp(field.c_str(), "install") != 0){
				this->userDirectory = value;
			}
			else if (std::strcmp(field.c_str(), "resources") != 0){
				this->resourceDirectory = value;
			}
			else if (std::strcmp(field.c_str(), "debug") != 0){
				this->debugLevel = std::atoi(value.c_str());
			}
			else {
				std::cout << "Unknown Line: " << linebuf << std::endl;
			}
		}
		fh.close();
	}
	
	configReader(){
		this->filePath = "";
		this->userDirectory = "";
		this->resourceDirectory = DEFAULT_RESOURCE_PATH;
		this->logFilename = DEFAULT_LOG_FILE;
		this->debugLevel = DEFAULT_DEBUG_LEVEL;
	}
};

#endif /* configreader_h */
