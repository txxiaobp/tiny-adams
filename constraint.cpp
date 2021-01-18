#include "constraint.h"

#include <cassert>

int Constraint::globleConstraintCount = 0;

Constraint::Constraint(Solid &solidA, Solid &solidB, Point &pointA, Point &pointB)
    : solidA(solidA)
    , solidB(solidB)
    , pointA(pointA)
    , pointB(pointB)
    , constraintId(globleConstraintCount++)
{
    assert(solidA.containPoint(pointA));
    assert(solidB.containPoint(pointB));
}

int Constraint::getId() const
{
    return constraintId;

}
std::vector<int> Constraint::getSolidIds() const
{
    return std::vector<int>{solidA.getId(), solidB.getId()};
}

int Constraint::getFreedomReducedCount() const
{
    return freedomReducedCount;
}
