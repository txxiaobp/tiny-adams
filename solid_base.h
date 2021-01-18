#ifndef SOLIDBASE_H
#define SOLIDBASE_H

#include "solid.h"
#include <vector>

class SolidBase
{
public:
    SolidBase();

    int getSolidCounts() const;

private:
    std::vector<Solid*> solidVec;
};

#endif // SOLIDBASE_H
