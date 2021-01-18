#ifndef LINK_H
#define LINK_H

#include "solid.h"

class Link : public Solid
{
public:
    Link(double x = 0, double y = 0, double angle = 0);
    ~Link();
};

#endif // LINK_H
