//
//  logger.h
//  Logger
//
//  Created by Albert Bode on 2/19/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef logger_h
#define logger_h

#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <queue>

#define LOG_MSG_STATUS 4
#define LOG_MSG_WARNING 3
#define LOG_MSG_ERROR 2
#define LOG_MSG_FATAL 1
#define LOG_MSG_OTHER 0

struct logger {
	struct logMsg{
		int msg_type;
		std::string msg;
		
		logMsg(int msg_type, const std::string msg){
			this->msg_type = msg_type;
			this->msg = msg;
		}
	};
private:
	std::string logFilename;
	std::ofstream logfh;
	std::queue<logMsg> msgBuffer;
public:
	int debugLevel;
	
	void setlogfile(std::string filename){this->logFilename = filename;};
	void log_msg(int msg_type, const std::string& msg){this->msgBuffer.push(logMsg(msg_type,msg));};
	void writeLog(){
		while(!this->msgBuffer.empty()){
			logMsg curmsg = this->msgBuffer.front();
			if (curmsg.msg_type <= this->debugLevel){
				std::time_t t = std::time(0);
				char tstring[100];
				std::strftime(tstring, sizeof(tstring), "[%H:%M:%S]", std::localtime(&t));
				logfh << tstring;
				switch(curmsg.msg_type){
					case LOG_MSG_STATUS:
						logfh << "[STATUS]	: ";
						break;
					case LOG_MSG_WARNING:
						logfh << "[WARNING] : ";
						break;
					case LOG_MSG_ERROR:
						logfh << "[ERROR] : ";
						break;
					case LOG_MSG_FATAL:
						logfh << "[FATAL ERROR] :";
						break;
					case LOG_MSG_OTHER:
						break;
					default:
						logfh << "[INVALID CODE] : ";
						break;
				};
				logfh << curmsg.msg << std::endl;
				
			}
			this->msgBuffer.pop();
		};
	};
	
	logger(){
		std::string logpath = "/Users/Albert/software/Logger/";
		this->logFilename = logpath + "project_log.txt";
		this->debugLevel = LOG_MSG_WARNING;
		logfh.open(logFilename);
		if(!logfh.is_open()){
			std::cout << "[FATAL ERROR] : Unable to start error logger" << std::endl;
		}
		this->log_msg(LOG_MSG_STATUS, "Logger initalized");
	}
	
	~logger() {
		writeLog();
		logfh.close();
	}
};

#endif /* logger_h */
