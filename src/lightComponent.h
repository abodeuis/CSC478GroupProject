#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include <iostream>
#include "baseComponent.h"


class lightComponent : public baseComponent
{
    public:


        void Execute(){
            std::cout <<"hello im a light component";
        };

};

#endif // LIGHTCOMPONENT_H
