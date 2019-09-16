//
//  config.h
//  Logger
//
//  Created by Albert Bode on 9/15/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef config_h
#define config_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

//#include "utils.h"

struct config {
	std::string user_dir;
	std::string resource_dir;
	
	std::string logfile;
	int debug_level;
	
	/* Temporary override function until reading from config.ini is ready */
	void read_config(){
		this->user_dir = "";
		this->resource_dir = "";
		this->logfile = "my_project_log.txt";
		this->debug_level = LOG_MSG_WARNING;
	}
	
	/*
	void read_config(){
		const std::string config_filename = "/Users/Albert/software/UIS/CSC478GroupProject/CSC478GroupProject/config/config.ini";
		// Open file stream
		std::fstream fh;
		fh.open(config_filename);
		if(!fh.is_open()){
			std::cout << "Unable to open user config" << std::endl;
		}
		
		// Read file line by line
		std::string linebuf;
		while (fh.peek() != -1) {
			safeGetline(fh, linebuf);
			
			// Skip empty lines
			if (linebuf.empty()){
				continue;
			}
			size_t delim = linebuf.find('=');
			std::string token = linebuf.substr(0, delim);
			std::string value = linebuf.substr(delim);
			
			// Skip comment lines
			if(token[0] == '#' || token[0] == ';'){
				continue;
			}
			// Value lines
			else if (std::strcmp(token.c_str(), "install") != 0){
				this->my_config.user_dir = value;
			}
			else if (std::strcmp(token.c_str(), "resources") != 0){
				this->my_config.resource_dir = value;
			}
			else if (std::strcmp(token.c_str(), "debug") != 0){
				this->my_config.debug_level = std::atoi(value.c_str());
			}
			else {
				std::cout << "Unknown Line: " << linebuf << std::endl;
			}
		}
		fh.close();
	}
	 */
};

#endif /* config_h */
