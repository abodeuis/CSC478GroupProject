//
//  main.cpp
//  Scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "init.h"
#include "sceneObjectCreation.h"

extern logger *log_f;
extern assetmanager *assets;
extern scene *activeScene;
extern window *mainWindow;

int main(int argc, char * argv[]) {
	
	engine_init(argc, argv);
	
	//std::cout << assets->get_material_asset("cube")->to_string();
	//std::cout << assets->get_mesh_asset("cube")->to_string();
	
	std::cout << assets->get_allocated_size();
	
	glutMainLoop();                                             // Main event loop
	
    return 0;
}
