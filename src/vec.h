//
//  vec.h
//  Filereader
//
//  Created by Albert Bode on 10/5/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

#ifndef vec_h
#define vec_h

typedef struct vec3 {
	GLfloat x,y,z;
	
	vec3(GLfloat x=0, GLfloat y=0, GLfloat z=0){
		this->x = x;
		this->y = y;
		this->z = z;
	}
}vec3;

typedef struct vec2 {
	GLfloat x,y;
	
	vec2(GLfloat x=0, GLfloat y=0){
		this->x = x;
		this->y = y;
	}
}vec2;

#endif /* vec_h */
