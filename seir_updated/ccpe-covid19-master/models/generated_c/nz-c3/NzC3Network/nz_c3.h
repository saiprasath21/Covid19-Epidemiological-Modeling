#ifndef NZ_C3_H_
#define NZ_C3_H_

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

// nz-c3 Data Struct
typedef struct {
    
    // Declare Outputs
    double s;
    double e;
    double p;
    double iu;
    double ic;
    double ru;
    double rc;
    double d;
    double cases;
    double level;

    // Declare Daughter Automata
    Plant plant_data;
    Controller controller_data;
} NzC3;

// nz-c3 Initialisation function
void NzC3Init(NzC3* me);

// nz-c3 Execution function
void NzC3Run(NzC3* me);

#endif // NZ_C3_H_