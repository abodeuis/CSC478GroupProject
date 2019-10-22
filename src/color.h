//
//  color.h
//  MergedSystem
//
//  Created by Albert Bode on 10/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef color_h
#define color_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <sstream>

#include "logger.h"
#include "vec.h"

extern logger *log;

class color{
	// Attributes
public:
	GLfloat red;          // Acceptable values [0.0f .. 1.0f]
	GLfloat green;        //
	GLfloat blue;         //
	GLfloat alpha;        //

	// Functions
private:
	void HEXtoRGB(const char *hex);	// Defined below
public:
	void set_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha=1.0f){
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}
	void set_color(vec3 rgb, GLfloat alpha=1.0f){
		this->red = rgb.x;
		this->green = rgb.y;
		this->blue = rgb.z;
		this->alpha = alpha;
	}
	void set_color(const char *color_or_hex, GLfloat alpha ); // Defined below
	
	// Default Constructor
	color(GLfloat red=1.0f, GLfloat green=1.0f, GLfloat blue=1.0f, GLfloat alpha=1.0f){
		this->set_color(red, green, blue, alpha);
	};
	
	color(vec3 rgb, GLfloat alpha=1.0f){
		this->set_color(rgb, alpha);
	}
	
	color(const char *color_or_hex, float alpha=1.0f){
		this->set_color(color_or_hex, alpha);
	};
};

#endif /* color_h */
