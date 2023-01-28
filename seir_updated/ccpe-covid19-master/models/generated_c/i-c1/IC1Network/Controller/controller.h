#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef int bool;
#define false 0
#define true 1

#include "config.h"

// Controller States
enum ControllerStates {
    CONTROLLER_PRE_PHASE0,
    CONTROLLER_PRE_PHASE1,
    CONTROLLER_PRE_PHASE2,
    CONTROLLER_PRE_PHASE3,
    CONTROLLER_PRE_PHASE4,
    CONTROLLER_PHASE3,
    CONTROLLER_PHASE2,
    CONTROLLER_PHASE1,
    CONTROLLER_PHASE0,
};

// Controller Data Struct
typedef struct {
    
    // Declare Inputs
    double ic;
    double c_dot;
    
    // Declare Outputs
    double r0;
    double r0c;
    double phase;
    
    // Declare Internal Variables
    double t;

    // State
    enum ControllerStates state;
} Controller;

// Controller Initialisation function
void ControllerInit(Controller* me);

// Controller Execution function
void ControllerRun(Controller* me);

#endif // CONTROLLER_H_