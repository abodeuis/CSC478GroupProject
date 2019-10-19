#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <baseComponent.h>


class meshComponent : public baseComponent
{
    public:
         void Execute() {
            std::cout <<"hello im a mesh component";
         };

        material meshpointer;
};

#endif // MESHCOMPONENT_H
