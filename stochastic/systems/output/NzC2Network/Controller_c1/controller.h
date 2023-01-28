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
    CONTROLLER_PRE_L_D,
    CONTROLLER_LD,
};

// Controller Data Struct
typedef struct {
    
    // Declare Outputs
    double r0;
    double r0c;
    double c;
    double level;
    
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