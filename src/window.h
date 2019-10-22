//
//  window.h
//  Scene
//
//  Created by Albert Bode on 10/17/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef window_h
#define window_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class window {
	const char *title;
	GLint winNum;
	GLint offsetX;
	GLint offsetY;
	GLint width;
	GLint height;
	
public:
	void init(){
		glutInitWindowSize(this->width,this->height);               // Window Size in pixels
		glutInitWindowPosition(this->offsetX,this->offsetY);        // Window Offset in pixels
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // Sets screen format
		
		winNum = glutCreateWindow(this->title);						// Create Main Window
	}
	
	void changeTitle(const char *newtitle){
		this->title = newtitle;
		glutSetWindowTitle(this->title);
	}
	
	window(const char *title="Untitled Window", GLint width=640, GLint height=480){
		this->title = title;
		this->offsetX = 10;
		this->offsetY = 10;
		this->width = width;
		this->height = height;
		
		this->init();
	}
};

#endif /* window_h */
