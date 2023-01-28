#ifndef NZ_C2_H_
#define NZ_C2_H_

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

// nz-c2 Data Struct
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
} NzC2;

// nz-c2 Initialisation function
void NzC2Init(NzC2* me);

// nz-c2 Execution function
void NzC2Run(NzC2* me);

#endif // NZ_C2_H_