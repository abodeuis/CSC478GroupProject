#ifndef PARTICALECOMPONENT_H
#define PARTICALECOMPONENT_H

#include <baseComponent.h>

class particaleComponent : public baseComponent
{
    public:
         void Execute() {
            std::cout <<"hello im a material component";
         };

        material material;

};

#endif // PARTICALECOMPONENT_H
