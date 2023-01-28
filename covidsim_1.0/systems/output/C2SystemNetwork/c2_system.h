#ifndef C2_SYSTEM_H_
#define C2_SYSTEM_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Plant/plant.h"
#include "Controller/controller.h"

typedef int bool;
#define false 0
#define true 1

#include "config.h"

// c2_system Data Struct
typedef struct {
    
    // Declare Outputs
    double cases;
    double c_dot;
    double level;
    double total;
    double d;

    // Declare Daughter Automata
    Plant plant_data;
    Controller controller_data;
} C2System;

// c2_system Initialisation function
void C2SystemInit(C2System* me);

// c2_system Execution function
void C2SystemRun(C2System* me);

#endif // C2_SYSTEM_H_