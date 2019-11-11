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
#include <math.h>

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
			if((*it)->name == "cube"){
				(*it)->transform.rotate(0.25, 0.25, 0.25);
			}
			if((*it)->name == "bunny"){
				(*it)->transform.rotate(0, -0.25,0);
				meshRendererComponent *m = (meshRendererComponent*)(*it)->components["meshRenderer"];
				m->meshcolor.red = (sinf((*it)->transform.get_rotation().y / 20) + 1) /2;
				m->meshcolor.green = (cosf((*it)->transform.get_rotation().y / 20) + 1) /2;
				m->meshcolor.blue = (sinf(((*it)->transform.get_rotation().y+0.5) / 20) + 1) /2;
				if(m->meshcolor.red < 0.1){
					m->meshcolor.red = 0.1;
				}
				if(m->meshcolor.green < 0.1){
					m->meshcolor.green = 0.1;
				}
				if(m->meshcolor.blue < 0.1){
					m->meshcolor.blue = 0.1;
				}
			}
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
		default_cube->transform.set_location(1,-0.5,-3);
		default_cube->name = "cube";
		default_cube->components["mesh"] = mc;
		default_cube->components["meshRenderer"] = new meshRendererComponent(mc);
		
		sceneObject *sphere_1 =new sceneObject("Sphere", get_next_pid());
		meshComponent *s1mc = new meshComponent("sphere");
		sphere_1->transform.set_location(0, 0, -5);
		sphere_1->transform.set_rotation(0, 90, 0);
		sphere_1->name = "sphere";
		sphere_1->components["mesh"] = s1mc;
		sphere_1->components["meshRenderer"] = new meshRendererComponent(s1mc);
		
		sceneObject *box_1 =new sceneObject("box_1", get_next_pid());
		meshComponent *c1mc = new meshComponent();
		box_1->transform.set_location(-2, 1, -7);
		box_1->transform.set_rotation(0, 90, 0);
		box_1->name = "sphere";
		box_1->components["mesh"] = c1mc;
		meshRendererComponent *c1mrc = new meshRendererComponent(c1mc);
		c1mrc->polymode = GL_LINE;
		box_1->components["meshRenderer"] = c1mrc;
		
		sceneObject *box_2 =new sceneObject("box_2", get_next_pid());
		meshComponent *c2mc = new meshComponent("cube1");
		box_2->transform.set_location(0, 1, -7);
		box_2->transform.set_rotation(0, 0, 0);
		box_2->name = "sphere";
		box_2->components["mesh"] = c2mc;
		box_2->components["meshRenderer"] = new meshRendererComponent(c2mc);
		
		sceneObject *box_3 =new sceneObject("box_3", get_next_pid());
		meshComponent *c3mc = new meshComponent("cube2");
		box_3->transform.set_location(2, 1, -7);
		box_3->transform.set_rotation(0, 0, 0);
		box_3->name = "sphere";
		box_3->components["mesh"] = c3mc;
		box_3->components["meshRenderer"] = new meshRendererComponent(c3mc);
		
		sceneObject *bunny = new sceneObject("bunny1", get_next_pid());
		meshComponent *bmc = new meshComponent("bunny");
		bunny->transform.set_location(-1,-0.5,-3);
		bunny->transform.set_scale(0.25, 0.25, 0.25);
		bunny->name = "bunny";
		bunny->components["mesh"] = bmc;
		meshRendererComponent *bmrc = new meshRendererComponent(bmc);
		bmrc->polymode = GL_LINE;
		bmrc->mat = NULL;
		bmrc->enableColor = true;
		bmrc->meshcolor = color("grey");
		bunny->components["meshRenderer"] = bmrc;

		this->mainCamera = mainCamera;
		this->add_object_to_scene(default_cube);
		this->add_object_to_scene(sphere_1);
		this->add_object_to_scene(box_1);
		this->add_object_to_scene(box_2);
		this->add_object_to_scene(box_3);
		this->add_object_to_scene(bunny);
	}
};

#endif /* scene_h */
