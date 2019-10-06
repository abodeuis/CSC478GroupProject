//
//  mesh.h
//  Mesh
//
//  Created by Albert Bode on 9/22/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <vector>
#include "vec.h"

typedef struct index_t {
	GLfloat x,y,z;			// Vertex coords
	GLfloat u,v;			// Texture coords
	GLfloat xn,yn,zn;		// Normal coords
	//color vc				// Vertex color
	
	index_t(GLfloat x=0, GLfloat y=0, GLfloat z=0, GLfloat u=0, GLfloat v=0){
		this->x = x;
		this->y = y;
		this->z = z;
		this->u = u;
		this->v = v;
		this->xn = 0;
		this->yn = 0;
		this->zn = 0;
	};
	
	index_t(vec3 vert, vec2 text=vec2()){
		this->x = vert.x;
		this->y = vert.y;
		this->z = vert.z;
		this->u = text.x;
		this->v = text.y;
		this->xn = 0;
		this->yn = 0;
		this->zn = 0;
	}
} index_t;

typedef struct {
	std::vector<index_t*> indices;
} point_t;

typedef struct {
	std::vector<index_t*> indices;
} line_t;

typedef struct {
	GLint smooth_group_id;			// Smoothing group
	GLint face_size;				// Number of indices in the face
	std::vector<index_t*> indices;		// Numerical indices of the face
} face_t;

typedef struct {
	std::vector<point_t> points;
	std::vector<line_t> lines;
	std::vector<face_t> faces;
} shape_t;

class mesh {
public:
	// Poliganal data
	shape_t *shape;

	// Attributes
	std::string name;
	
	
	std::string to_string(){
		std::string output = name;
		output += "\n";
		for (std::vector<point_t>::iterator p_it = this->shape->points.begin(); p_it != this->shape->points.end(); ++p_it){
			output += "Points: ";
			output += std::to_string(p_it->indices.size());
			output += "\n";
			for (std::vector<index_t*>::iterator i_it = p_it->indices.begin(); i_it != p_it->indices.end(); ++i_it){
				output += "\t";
				output += std::to_string((*i_it)->x);
				output += ", ";
				output += std::to_string((*i_it)->y);
				output += ", ";
				output += std::to_string((*i_it)->z);
				output += "\n";
			}
		}
		for (std::vector<line_t>::iterator l_it = this->shape->lines.begin(); l_it != this->shape->lines.end(); ++l_it){
			output += "Line: ";
			output += std::to_string(l_it->indices.size());
			output += "\n";
			for (std::vector<index_t*>::iterator i_it = l_it->indices.begin(); i_it != l_it->indices.end(); ++i_it){
				output += "\t";
				output += std::to_string((*i_it)->x);
				output += ", ";
				output += std::to_string((*i_it)->y);
				output += ", ";
				output += std::to_string((*i_it)->z);
				output += "\n";
			}
		}
		if (this->shape->faces.size() != 0){
		for (std::vector<face_t>::iterator f_it = this->shape->faces.begin() ; f_it != this->shape->faces.end(); ++f_it){
			output += "Face: ";
			output += std::to_string(f_it->indices.size());
			output += "\n";
			for (std::vector<index_t*>::iterator i_it = f_it->indices.begin(); i_it != f_it->indices.end(); ++i_it){
				output += "\t";
				output += std::to_string((*i_it)->x);
				output += ", ";
				output += std::to_string((*i_it)->y);
				output += ", ";
				output += std::to_string((*i_it)->z);
				output += "\n";
			}
		}
		}
		return output;
	};
	
	mesh(){
		this->name = "Untitled Mesh";
	}
};

#endif /* mesh_h */
