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
    CONTROLLER_PRE_LEVEL0,
    CONTROLLER_PRE_LEVEL4,
    CONTROLLER_LEVEL4,
    CONTROLLER_LEVEL3,
    CONTROLLER_LEVEL2,
    CONTROLLER_LEVEL1,
    CONTROLLER_LEVEL0,
};

// Controller Data Struct
typedef struct {
    
    // Declare Inputs
    double ic;
    double c_dot;
    
    // Declare Outputs
    double r0;
    double r0c;
    double level;
    double c_gen;
    double c_iso;
    double psi;
    double ll;
    
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