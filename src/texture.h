//
//  texture.h
//  Filereader
//
//  Created by Albert Bode on 10/8/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef texture_h
#define texture_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <sstream>

class texture2D_t {
public:
	// texture name
	std::string name;
	
	GLint width;
	GLint height;
	GLint lod;
	GLint texformat;
	GLint pixelformat;
	GLint pixeltype;
	
	// Image pixel data
	unsigned *texels;
	
	std::string to_string(){
		std::stringstream output;
		return output.str();
	}
	
	~texture2D_t(){
		//if (texels) delete [] texels;
	}
};

#endif /* texture_h */
