#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <stdlib.h>
#include "cameraComponent.h"
#include "materialComponent.h"
#include "lightComponent.h"
#include "meshComponent.h"
#include "particaleComponent.h"
#include "transformComponent.h"

int main(int argc, const char * args[]) {

    // object of class created
    lightComponent l;
    cameraComponent c;
    materialComponent m;
    meshComponent e;
    particaleComponent p;
    transformComponent t;

    std::vector<baseComponent*> components; //array of classes that can do different things.

    components.push_back(&m); //adds to end of array; passing in reference of memory of the object created
    components.push_back(&p);
    components.push_back(&c); // -> =
    components.push_back(&e);
    components.push_back(&l);
    components.push_back(&t);

    for (std::vector<baseComponent*>::size_type i = 0; i != components.size();i++ ) {
        components[i]->Execute();
    }
return 0;
}
