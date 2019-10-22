//
//  vec.h
//  Filereader
//
//  Created by Albert Bode on 10/5/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef vec_h
#define vec_h

// Cross platform include statement for glut library
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef struct vec3 {
	GLfloat x,y,z;
	
	// Addition Operator
	friend vec3 operator+(const vec3& lhs, const vec3& rhs){
		return vec3((lhs.x+rhs.x),(lhs.y+rhs.y),(lhs.z+rhs.z));
	}
	
	// Subtraction Operator
	friend vec3 operator-(const vec3& lhs, const vec3& rhs){
		return vec3((lhs.x-rhs.x),(lhs.y-rhs.y),(lhs.z-rhs.z));
	}
	
	// Assignment Operator
	vec3& operator=(vec3 const &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	}
	
	// Addition Assignement Operator
	vec3& operator+=(vec3 const &v){
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}
	
	// Equality Operator
	friend bool operator==(const vec3& lhs, const vec3& rhs){
		return ((lhs.x == rhs.x)&&(lhs.y == rhs.y)&&(lhs.z == rhs.z));
	}
	
	// Inequality Operator
	friend bool operator!=(const vec3& lhs, const vec3& rhs){
		return !((lhs.x == rhs.x)&&(lhs.y == rhs.y)&&(lhs.z == rhs.z));
	}
	
	// String Operator
	friend std::ostream& operator<<(std::ostream& out, const vec3& v){
		return out << v.x << ", " << v.y << ", " << v.z;
	}
	
	// Default Constructor
	vec3(GLfloat x=0, GLfloat y=0, GLfloat z=0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	// Copy constructor
	vec3(vec3 const &v){
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
}vec3;

typedef struct vec2 {
	GLfloat x,y;
	
	// Addition Operator
	friend vec2 operator+(const vec2& lhs, const vec2& rhs){
		return vec2((lhs.x+rhs.x),(lhs.y+rhs.y));
	}
	
	// Subtraction Operator
	friend vec2 operator-(const vec2& lhs, const vec2& rhs){
		return vec2((lhs.x-rhs.x),(lhs.y-rhs.y));
	}
	
	// Assignment Operator
	vec2& operator=(vec2 const &v){
		this->x = v.x;
		this->y = v.y;
		return *this;
	}
	
	// Addition Assignement Operator
	vec2& operator+=(vec2 const &v){
		this->x += v.x;
		this->y += v.y;
		return *this;
	}
	
	// Equality Operator
	friend bool operator==(const vec2& lhs, const vec2& rhs){
		return ((lhs.x == rhs.x)&&(lhs.y == rhs.y));
	}
	
	// Inequality Operator
	friend bool operator!=(const vec2& lhs, const vec2& rhs){
		return !((lhs.x == rhs.x)&&(lhs.y == rhs.y));
	}
	
	// String Operator
	friend std::ostream& operator<<(std::ostream& out, const vec2& v){
		return out << v.x << ", " << v.y;
	}
	
	// Default Constructor
	vec2(GLfloat x=0, GLfloat y=0){
		this->x = x;
		this->y = y;
	}
	
	// Copy constructor
	vec2(vec2 const &v){
		this->x = v.x;
		this->y = v.y;
	}
}vec2;

#endif /* vec_h */
