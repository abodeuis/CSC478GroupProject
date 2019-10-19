#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <iostream>
#include <baseComponent.h>
#include "vec.h"

class transformComponent : public baseComponent
{
    private:
        vec3 location;
        vec3 rotation;
        vec3 scale;

        GLfloat x;
        GLfloat y;
        GLfloat z;

    public:
        void Execute() {
            std:: cout<< "Hello im the transform component";
        };

        void setlocation(GLfloat x,GLfloat y ,GLfloat z) {
            this->location.x = x;
            this->location.y = y;
            this->location.z = z;
        };

        void setlocale(vec3 vec) {
            this->location = vec;
        };

        vec3 getlocation() {
            return location;
        }

        void setrotation(GLfloat x,GLfloat y ,GLfloat z) {
            this->rotation.x = x;
            this->rotation.y = y;
            this->rotation.z = z;
        };

        void setrotation(vec3 vec) {
            this->rotation = vec;
        };

        vec3 getrotation() {
            return rotation;
        }

        void setscale(GLfloat x,GLfloat y ,GLfloat z) {
            this->scale.x = x;
            this->scale.y = y;
            this->scale.z = z;
        };

         void setscale(vec3 vec) {
            this->scale = vec;
        };

        vec3 getscale() {
            return scale;
        }
};

#endif // TRANSFORMCOMPONENT_H


// how to write a function
// type func_name(type2 var_ name, type3 var_name2)) {
//  content
//}
