#include "constraint.h"

#include <cassert>

Constraint::Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB)
    : solidA(solidA)
    , solidB(solidB)
    , pointA(pointA)
    , pointB(pointB)
    , id(globleConstraintCount)
{
    assert(solidA.containPoint(pointA));
    assert(solidB.containPoint(pointB));
}

