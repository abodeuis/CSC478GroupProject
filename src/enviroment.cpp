//
//  enviroment.cpp
//  MergedSystem
//
//  Created by Albert Bode on 10/29/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#include "enviroment.h"
#include "assetmanager.h"
#include "configreader.h"
#include "logger.h"
#include "scene.h"
#include "window.h"
/*
// Default Constructor
engine_enviroment::engine_enviroment(const char* projectName, const char* configPath){
	// Initalize required global variables
	this->global_variables["projectName"] = new cvar<const char*>(projectName);
	
	configReader c;
	c.filePath = configPath;
	// Attempt to load user config
	c.load_config();
	
	// Initalize Logger
	this->log = new logger(c.logFilename, c.debugLevel);
	
	// Initalize Window
	this->mainWindow = new window(projectName);
	
	// Initalize Default Assets
	this->assets = new assetmanager(c.resourceDirectory);
	assets->add_mesh_asset("testcube.obj", "cube");
	assets->add_material_asset("testcube.mtl", "cube");
	assets->add_texture_asset("testbrick.sgi", "brick");
	
	// Check for user supplied assets
	
	
	// Initalize Scene
	activeScene = new scene();
}
 */
