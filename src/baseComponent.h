#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <iostream>
typedef struct material{
};

class baseComponent
{
    public:
       // virtual ~baseComponent();

        virtual void Execute() = 0;
        //baseComponent();
};

#endif // BASECOMPONENT_H
