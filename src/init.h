//
//  init.h
//  Scene
//
//  Created by Albert Bode on 10/17/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef init_h
#define init_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "scene.h"
#include "window.h"

extern window *mainWindow;
extern scene *activeScene;
extern char *projectTitle;

//Keyboard callbacks
void keyboard( unsigned char key, int x, int y )
{
	// Process keys
	switch (key)
	{
		case 'q':
			// exit program
			exit (1);
			break;
	}
	glutPostRedisplay();
}


static void idle(void){
	glutPostRedisplay();
}

static void display(void){
	activeScene->draw_scene();
}

void engine_init(int argc, char * argv[]){
	activeScene = new scene();
	
	// Initialize window system
	glutInit(&argc, argv);                                      // Initializes glut library which provides the interface for drawing to the screen.
	
	// Create main window
	mainWindow = new window();
	
	// Display callback for main window
	glutDisplayFunc( display );

	// Other callbacks
	glutIdleFunc( idle );                           // Called when the program has no input.
	glutKeyboardFunc( keyboard );                        // Called when a key is pressed
	/*
	glutReshapeFunc( resize );						// Called when the window is resized.
	
	glutKeyboardUpFunc( keyup );					// Called when a key is released
	glutSpecialFunc( special_key );					// Called when a non-traditional key is pressed ex. (F1, shift, cntl)
	glutMouseFunc( mouse );                         // Called when mouse button input is detected
	glutMotionFunc( motion );                       // Called when the mouse moves and has button(s) pressed
	
	
	// Not used except for debugging, if you want to use one go ahead and implement it.
	glutEntryFunc( entry );							// Called when the mouse leaves or enters the screen
	
	glutVisibilityFunc( visable );					// Called when the screen becomes not visible or visible.
	glutPassiveMotionFunc( passivemotion );			// Called when the mouse moves but doesn't have any buttons pressed
	glutKeyboardUpFunc( keyup );					// Called when a key is released
	*/
}

#endif /* init_h */
