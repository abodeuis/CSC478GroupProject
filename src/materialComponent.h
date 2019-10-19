#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include <baseComponent.h>

class materialComponent : public baseComponent
{
    public:
         void Execute() {
            std::cout <<"hello im a material component";
         };

        material materialpointer;

};

#endif // MATERIALCOMPONENT_H
