//
//  sceneObject.h
//  Scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef sceneObject_h
#define sceneObject_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <string>
#include <map>

#include "components.h"

class sceneObject {
	std::string name;
	
	bool selectable;					// If object is valid to select
	int tag;			// enum of possible tags probably
public:
	int pid;							// picking id
	transformComponent transform;
	std::map<std::string, baseComponent*> components;
	
	void add_component(baseComponent* component){
		
	}
	
public:
	// Functions
	void execute(){
		// Order of components; if any don't exist skip step
		// 0 : Any logic or update components
		// 1 : Load pid and setup matrix
		// 2 : Transform matrix to correct location
		// 3 : Any non-rendering componets, such as lights should be added
		// 4 : Render mesh of object
		// 5 : Reload the pre-draw matrix (final step)
		
		// 0 : Logic components
		
		
		// 1 :
		glLoadName(pid);
		
		glPushMatrix();

		
		if(components["camera"]){
			components["camera"]->execute();
		}
		
		// 2 : Translate
		transform.execute();
		
		// 3 : Non-physical geometry components
		/*
		if(lightComponent in components){
			lightComponent->execute();
		}
		 */
		
		
		// 4 : Physical geometry components
		if(components["meshRenderer"]){
			components["meshRenderer"]->execute();
		}
		glPopMatrix();
	};
	
	sceneObject(std::string name = "Untitled Object", int pid=0){
		this->name = name;
		this->pid = pid;
	}
};

#endif /* sceneObject_h */
