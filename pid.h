#ifndef PID_H
#define PID_H

#include "controller.h"

class PID : public Controller
{
public:
    PID();
    ~PID();
};

#endif // PID_H
