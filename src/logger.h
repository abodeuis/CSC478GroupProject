//
//  logger.h
//
//  Created by Albert Bode on 9/12/19.
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

typedef struct logger {
	struct logMsg{
		int msg_type;
		std::string msg;

		logMsg(int msg_type, const std::string msg){
			this->msg_type = msg_type;
			this->msg = msg;
		}
	};
private:
	std::string logLocation;
	std::ofstream logfh;
	std::queue<logMsg> msgBuffer;
	int debugLevel;

public:
	void set_logfile(std::string filelocation){this->writeLog();this->logLocation = filelocation;};
	void set_debug_level(int debugLevel){this->writeLog();this->debugLevel = debugLevel;};
	void log_msg(int msg_type, const std::string& msg){this->msgBuffer.push(logMsg(msg_type,msg));if (msgBuffer.size() > 10){this->writeLog();}};
	void writeLog(){
		while(!this->msgBuffer.empty()){
			logMsg curmsg = this->msgBuffer.front();
			std::string linebuf;
			if (curmsg.msg_type <= this->debugLevel){
				std::time_t t = std::time(0);
				char tstring[100];
				std::strftime(tstring, sizeof(tstring), "[%H:%M:%S]", std::localtime(&t));
				linebuf = tstring;
				switch(curmsg.msg_type){
					case LOG_MSG_STATUS:
						linebuf.append("[STATUS]\t: ");
						break;
					case LOG_MSG_WARNING:
						linebuf.append("[WARNING]\t: ");
						break;
					case LOG_MSG_ERROR:
						linebuf.append("[ERROR]\t: ");
						break;
					case LOG_MSG_FATAL:
						linebuf.append("[FATAL ERROR]\t:");
						break;
					case LOG_MSG_OTHER:
						break;
					default:
						linebuf.append("[INVALID CODE]\t: ");
						break;
				};
				linebuf.append(curmsg.msg);
				logfh << linebuf << std::endl;
			}
			this->msgBuffer.pop();
		};
	};

	logger(std::string logLocation="project_log.txt", int debugLevel=LOG_MSG_ERROR){
		this->logLocation = logLocation;
		this->debugLevel = debugLevel;

		logfh.open(logLocation);
		if(!logfh.is_open()){
			std::cout << "[FATAL ERROR] : Unable to start error logger" << std::endl;
		}
		this->log_msg(LOG_MSG_STATUS, "Logger initalized");
	}

	~logger() {
		this->log_msg(LOG_MSG_STATUS, "Logger exiting");
		writeLog();
		logfh.close();
	}
} logger;

#endif /* logger_h */
