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
	GLint texture_id;
	
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
	
	texture2D_t(){
		this->name = "Untitled Texture";
		this->texture_id = -1;
		this->width = -1;
		this->height = -1;
		this->lod = 0;
		this->texformat = -1;
		this->pixelformat = -1;
		this->pixeltype = -1;
		
		this->texels = NULL;
	}
	
	~texture2D_t(){
		if (this->texels != NULL){free(texels); this->texels = NULL;}
	}
};

#endif /* texture_h */
