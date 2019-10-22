//
//  scene.h
//  scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef scene_h
#define scene_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>

#include "sceneObject.h"

struct group {
	std::vector<sceneObject*> objects;
};

class scene {
	std::string name;
	int next_pid;
	sceneObject* mainCamera;
	std::vector<sceneObject*> objects;
	std::vector<group*> groups;
	
public:
	int get_next_pid(){return this->next_pid++;};
	void add_object_to_scene(sceneObject* object_to_add){
		object_to_add->pid = next_pid++;
		objects.push_back(object_to_add);
	}
	
	void draw_scene(){
		// Clear the frame buffer before drawing
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glPushMatrix();
		glDisable( GL_LIGHTING ); // Disable Lighting for now until implemented
		// Setup Main Camera
		mainCamera->execute();
		
		// Draw scene objects
		for (std::vector<sceneObject*>::iterator it = objects.begin(); it != objects.end(); it++){
			(*it)->execute();
		}

		glPopMatrix();
		
		// Setup UI rendering
		
		// Draw view objects
		
		glFlush();		// Makes all GL functions calls execute before it updates the display.
		if(true){
		//if(RenderMode == GL_RENDER){	// when you call glut draw functions they draw not to the screen, but to a buffer to
			glutSwapBuffers();			// display the the stuff you just drew you need to swap the buffer with the active
			// screen. When you are in select mode the buffer is not intended to be shown.
		}
	};
	
	
	
	scene(){
		this->name = "Untitled Scene";
		this->next_pid = 0;
		
		// Create Default Camera
		sceneObject *mainCamera = new sceneObject("Main Camera", get_next_pid());
		mainCamera->components["camera"] = new cameraComponent();
		mainCamera->transform.set_location(0, 0, -10);
		sceneObject *default_cube = new sceneObject("Cube", get_next_pid());
		meshComponent *mc = new meshComponent();
		default_cube->transform.set_location(2,2,-6);
		default_cube->components["mesh"] = mc;
		default_cube->components["meshRenderer"] = new meshRendererComponent(mc);
		
		this->mainCamera = mainCamera;
		this->add_object_to_scene(default_cube);
	}
};

#endif /* scene_h */
