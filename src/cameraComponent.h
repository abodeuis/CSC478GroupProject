#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include <baseComponent.h>
#include <GL/gl.h>


class cameraComponent : public baseComponent
{
    public:
         void Execute() {
            std::cout <<"hello im a camera component";
         };

        GLfloat viewportHeight;
        GLfloat viewportWidth;
        int projectionMode; //2D
        double fieldOfView;
        double cullNear;
        double cullFar;
        material backgorund;



};

#endif // CAMERACOMPONENT_H
