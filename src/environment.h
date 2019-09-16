//
//  environment.h
//  Logger
//
//  Created by Albert Bode on 9/15/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef environment_h
#define environment_h

#include "logger.h"
#include "config.h"

class environment {
public:
	config config;
	logger *debug_log;
	
	environment(){
		this->config.read_config();
		
		this->debug_log = new logger(this->config.user_dir + this->config.logfile,this->config.debug_level);
		
	}
};

#endif /* environment_h */
