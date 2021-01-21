#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <unordered_set>

class Solid;

typedef enum
{
    DYNAMICS_RUNGE_KUTTA
}Dynamics_E;

class Dynamics
{
public:
    Dynamics(double timeStep, double timeDuration, Dynamics_E method = DYNAMICS_RUNGE_KUTTA);
    ~Dynamics();

    void addSolid(Solid &solid);
    void addSolid(int solidId);

    void calculate();

private:
    std::unordered_set<int> solidSet;
    double timeStep;
    double timeDuration;
    Dynamics_E method;
};

#endif // DYNAMICS_H
