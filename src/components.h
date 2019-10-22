//
//  components.h
//  Scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef components_h
#define components_h

#include <iostream>
#include <vector>
#include <string>

#include "assetmanager.h"
#include "color.h"
#include "vec.h"

extern assetmanager *assets;

class baseComponent {
public:
	virtual void execute() = 0;
};

class transformComponent : baseComponent {
	// Attributes
private:
	vec3 transformVector;
	vec3 rotationVector;
	vec3 scaleVector;
	

	// Functions
public:
	void execute();
	
	// Setters and Getters
	// Translate functions
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void translate(vec3 vec);
	void set_location(GLfloat x, GLfloat y, GLfloat z);
	void set_location(vec3 vec);
	vec3 get_location();
	// Rotate functions
	void rotate(GLfloat x, GLfloat y, GLfloat z);
	void rotate(vec3 vec);
	void set_rotation(GLfloat x, GLfloat y, GLfloat z);
	void set_rotation(vec3 vec);
	vec3 get_rotation();
	// Scale functions
	void scale(GLfloat x, GLfloat y, GLfloat z);
	void scale(vec3 vec);
	void set_scale(GLfloat x, GLfloat y, GLfloat z);
	void set_scale(vec3 vec);
	vec3 get_scale();
	
	// Default Constructor
	transformComponent(GLfloat x=0, GLfloat y=0, GLfloat z=0){
		this->transformVector = x;
		this->transformVector = y;
		this->transformVector = z;
		this->rotationVector = vec3(0,0,0);
		this->scaleVector = vec3(1,1,1);
	}
	
	transformComponent(vec3 t, vec3 r=vec3(0,0,0), vec3 s=vec3(1,1,1)){
		this->transformVector = t;
		this->rotationVector = r;
		this->scaleVector = s;
	}
};

// Defintion of projectionModes for cameraComponent
#define CC_PERSPECTIVE 3
#define CC_ORTHO 2

class cameraComponent : public baseComponent {
	// Attributes
public:
	GLint projectionMode;		// Perspective (3D) : 3 or Orthographic (2D) : 2, anything else is invalid
	GLint targetViewport;
	GLfloat viewportX;
	GLfloat viewportY;
	GLfloat viewportHeight;
	GLfloat viewportWidth;
	GLdouble fov;				// Field of view [1.0 .. 360.0]
	GLdouble cullNear;			// Near culling plane distance [0 .. n]
	GLdouble cullFar;			// Far culling plan distance [n .. inf] Can not be smaller then cullNear
	color backgroundcolor;
	material *background;
	

	// Functions
public:
	void execute();			// Defined in cpp
	
	// Default constructor
	cameraComponent(){
		this->projectionMode = CC_PERSPECTIVE;
		this->viewportX = 0;
		this->viewportY = 0;
		this->viewportHeight = 1;
		this->viewportWidth = 1;
		this->fov = 60;
		this->cullNear = 0.01;
		this->cullFar = 1000;
		this->backgroundcolor = color("#222222");
	}
	
};

class meshComponent : public baseComponent {
	// Attributes
public:
	mesh *m;

	// Functions
public:
	void execute();			// Defined in cpp
	
	// Setters and Getters
	void set_mesh(std::string mesh_name){
		this->m = assets->get_mesh_asset("mesh_name");
	}
	
	std::string get_mesh(){
		return this->m->name;
	}
	
	// Default Constructor (Cube)
	meshComponent(std::string mesh_name="cube"){
		m = assets->get_mesh_asset(mesh_name);
	};
};

class meshRendererComponent : public baseComponent {
	// Attributes
public:
	meshComponent* associated_mesh;	 // The meshComponent that this is trying to render
	
	color meshcolor;
	material mat;
	bool enableLighting;

	// Functions
public:
	void execute();			// Defined in cpp
	
	meshRendererComponent(meshComponent* associated_mesh, bool lighting=true){
		this->associated_mesh = associated_mesh;
		this->enableLighting = lighting;
		this->meshcolor = color("Firebrick");
		this->mat = material();
	}
};

// No Implentation of these components yet, so left out.
/*
class textMeshComponent : public baseComponent {
	// Attributes
public:
	std::string text;
	GLfloat fontsize;
	GLfloat font;
	color color;
public:
	// Functions
	void execute();			// Defined in cpp
};

class lightComponent : public baseComponent {
	// Attributes
	GLint lighttype; // Spot, Directional, Point, Area
	GLfloat range;
	color color;
	GLint mode; // Realtime, mixed, baked
	GLfloat intensity;
	GLfloat indirectMultiplier;
	
public:
	// Functions
	void execute();			// Defined in cpp
	
	// Default Constructor
	lightComponent(){
		this->lighttype = 0; // Default should be point
		this->range = 10;
		this->mode = 0; // ? probaly not going to use
		this->intensity = 1;
		this->indirectMultiplier = 1;
	}
};
*/

#endif /* components_h */
