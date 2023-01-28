#ifndef COVIDSIM_SYSTEM_H_
#define COVIDSIM_SYSTEM_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Plant/plant.h"

typedef int bool;
#define false 0
#define true 1

#include "config.h"

// covidsim_system Data Struct
typedef struct {
    
    // Declare Outputs
    double s;
    double e1;
    double e2;
    double p1;
    double p2;
    double i1;
    double i2;
    double l1;
    double l2;
    double r;
    double d;
    double prob;
    double cases;
    double c_dot;

    // Declare Daughter Automata
    Plant plant_data;
} CovidsimSystem;

// covidsim_system Initialisation function
void CovidsimSystemInit(CovidsimSystem* me);

// covidsim_system Execution function
void CovidsimSystemRun(CovidsimSystem* me);

#endif // COVIDSIM_SYSTEM_H_