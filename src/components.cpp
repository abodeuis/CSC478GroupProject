//
//  components.cpp
//  Scene
//
//  Created by Albert Bode on 10/16/19.
//  Copyright © 2019 Albert Bode. All rights reserved.
//

/* ########## Index ########## */
// 1. execute() for each component
// 2. transformComponent
// 3.

#include "components.h"

void transformComponent::execute(){
	glTranslatef(this->transformVector.x, this->transformVector.y, this->transformVector.z);
	glRotatef(this->rotationVector.x, this->transformVector.x, this->transformVector.y, this->transformVector.z);
	glRotatef(this->rotationVector.y, this->transformVector.x, this->transformVector.y, this->transformVector.z);
	glRotatef(this->rotationVector.z, this->transformVector.x, this->transformVector.y, this->transformVector.z);
	glScalef(this->scaleVector.x, this->scaleVector.y, this->scaleVector.z);
}

void cameraComponent::execute(){
	// Default Background color
	glClearColor( backgroundcolor.red, backgroundcolor.green, backgroundcolor.blue, backgroundcolor.alpha );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if ( this->projectionMode == CC_PERSPECTIVE ){
		GLfloat aspect_ratio = 1.3333333;
		gluPerspective(this->fov, aspect_ratio, this->cullNear, this->cullFar);
	}
	else if (this->projectionMode == CC_ORTHO){
		glOrtho(this->viewportX, this->viewportWidth, this->viewportHeight, this->viewportY, -1, 1);
	}
	else {
		std::string log_msg = "Invalid projectionMode : ";
		log_msg += projectionMode;
		log->log_msg(LOG_MSG_ERROR, log_msg);
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//glPopMatrix();
}

void meshComponent::execute(){
	// Mesh itself will not do anything as just beacuse the object has a mesh,
	// doesn't nessicarrily mean it needs to be rendered.
}

void meshRendererComponent::execute(){
	glColor4f(this->meshcolor.red, this->meshcolor.green, this->meshcolor.blue, this->meshcolor.alpha);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	//glEnable( GL_TEXTURE_2D );
	//glBindTexture(GL_TEXTURE_2D, material->texels);
	
	glBegin( GL_TRIANGLES );
	for (std::vector<face_t>::iterator face = this->associated_mesh->m->shape->faces.begin(); face != this->associated_mesh->m->shape->faces.end(); face++ ){
		for (std::vector<index_t*>::iterator index = face->indices.begin(); index != face->indices.end(); index++){
			glNormal3f((*index)->xn, (*index)->yn, (*index)->zn);
			glTexCoord2f((*index)->u, (*index)->v);
			glVertex3f((*index)->x, (*index)->y, (*index)->z);
		}
	}
	glEnd();
	
	//glDisable( GL_TEXTURE_2D );
}

/*
void textMeshComponent::execute(){
	std::cout << "textMeshComponent is not implemented yet" << std::endl;
}

void lightComponent::execute(){
	std::cout << "lightComponent is not implemented yet" << std::endl;
}
 */

// Transform component functions
void transformComponent::translate(float x, float y, float z){
	this->transformVector.x += x;
	this->transformVector.y += y;
	this->transformVector.z += z;
}

void transformComponent::translate(vec3 vec){
	this->transformVector += vec;
}

void transformComponent::set_location(float x, float y, float z){
	this->transformVector.x = x;
	this->transformVector.y = y;
	this->transformVector.z = z;
}

void transformComponent::set_location(vec3 vec){
	this->transformVector = vec;
}

vec3 transformComponent::get_location(){
	return this->rotationVector;
}

void transformComponent::rotate(float x, float y, float z){
	this->rotationVector.x += x;
	this->rotationVector.y += y;
	this->rotationVector.z += z;
}

void transformComponent::rotate(vec3 vec){
	this->rotationVector += vec;
}

void transformComponent::set_rotation(float x, float y, float z){
	this->rotationVector.x = x;
	this->rotationVector.y = y;
	this->rotationVector.z = z;
}

void transformComponent::set_rotation(vec3 vec){
	this->rotationVector = vec;
}

vec3 transformComponent::get_rotation(){
	return this->rotationVector;
}

void transformComponent::scale(float x, float y, float z){
	this->scaleVector.x += x;
	this->scaleVector.y += y;
	this->scaleVector.z += z;
}

void transformComponent::scale(vec3 vec){
	this->scaleVector += vec;
}

void transformComponent::set_scale(float x, float y, float z){
	this->scaleVector.x = x;
	this->scaleVector.y = y;
	this->scaleVector.z = z;
}

void transformComponent::set_scale(vec3 vec){
	this->scaleVector = vec;
}

vec3 transformComponent::get_scale(){
	return this->scaleVector;
}
