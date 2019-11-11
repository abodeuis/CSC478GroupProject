//
//  enviroment.h
//  MergedSystem
//
//  Created by Albert Bode on 10/29/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef enviroment_h
#define enviroment_h

#include <map>
#include <string>
#include <vector>

#include "cvar.h"

// Forward declare
class scene;
class assetmanager;
class window;
class logger;

class engine_enviroment {
public:
	std::map<std::string, cvarInterface*> global_variables;
	
	assetmanager *assets;
	scene *activeScene;
	logger *log;
	
	// Should be changed to windows
	window *mainWindow;
	
	// Default Constructor
	engine_enviroment(const char* projectName="Untitled Project", const char* configPath="");
};

#endif /* enviroment_h */
